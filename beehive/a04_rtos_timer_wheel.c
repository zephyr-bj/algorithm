/** Basic assumptions & hooks **/
/* platform.h */
#pragma once
#include <stdint.h>
#include <stdbool.h>

/* hardware timer */
uint64_t hw_timer_now(void);
void hw_timer_set_compare(uint64_t deadline);
void hw_timer_stop(void);

/* interrupt control */
unsigned long irq_save(void);
void irq_restore(unsigned long flags);

/* scheduler / IPC */
void wake_timer_task(void);

/** Timer object **/

/* timer.h */
#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef void (*timer_cb_t)(void *arg);

struct rtos_timer {
    uint64_t expiry;
    uint64_t period;     /* 0 = one-shot, shows number of repeats */
    timer_cb_t cb;
    void *arg;

    bool active;
    uint32_t gen;        /* protects stop/restart races */

    struct rtos_timer *next;
};

/** Timer wheel layout (L0 + L1) **/

/* timer_wheel.h */
//#pragma once
//#include "timer.h"

#define LVL0_BITS 8      /* 256 slots, 1 tick resolution */
#define LVL1_BITS 6      /* 64 slots, 256 tick resolution */

#define LVL0_SIZE (1 << LVL0_BITS)
#define LVL1_SIZE (1 << LVL1_BITS)

struct timer_wheel {
    uint64_t current;
    struct rtos_timer *lvl0[LVL0_SIZE];
    struct rtos_timer *lvl1[LVL1_SIZE];
};

extern struct timer_wheel g_tw;

/** Wheel initialization **/

/* timer_wheel.c */
//#include "timer_wheel.h"
//#include <string.h>

struct timer_wheel g_tw;

void timer_wheel_init(void)
{
    memset(&g_tw, 0, sizeof(g_tw));
    g_tw.current = hw_timer_now();
}

/** Enqueue a timer into the wheel **/

static void list_add(struct rtos_timer **head,
                     struct rtos_timer *t)
{
    t->next = *head;
    *head = t;
}

static void wheel_enqueue(struct rtos_timer *t)
{
    uint64_t delta = t->expiry - g_tw.current;

    if (delta < LVL0_SIZE) {
        uint32_t idx = t->expiry & (LVL0_SIZE - 1);
        list_add(&g_tw.lvl0[idx], t);
    } else {
        uint32_t idx = (t->expiry >> LVL0_BITS) & (LVL1_SIZE - 1);
        list_add(&g_tw.lvl1[idx], t);
    }
}

/** Programming the next hardware deadline **/
static uint64_t find_next_expiry(void)
{
    for (uint32_t i = 0; i < LVL0_SIZE; i++) {
        if (g_tw.lvl0[i])
            return (g_tw.current & ~(LVL0_SIZE - 1)) + i;
    }
    return UINT64_MAX;
}
static void program_next_deadline(void)
{
    uint64_t next = find_next_expiry();
    if (next == UINT64_MAX)
        hw_timer_stop();
    else
        hw_timer_set_compare(next);
}

/** Start / stop timers **/
void timer_start(struct rtos_timer *t, uint64_t delay)
{
    unsigned long flags = irq_save();

    t->gen++;
    t->expiry = hw_timer_now() + delay;
    t->active = true;

    wheel_enqueue(t);
    program_next_deadline();

    irq_restore(flags);
}

void timer_stop(struct rtos_timer *t)
{
    unsigned long flags = irq_save();
    t->active = false;
    t->gen++;
    irq_restore(flags);
}

/** Expired timer queue (deferred execution) **/
/* timer_expire.c */
static struct rtos_timer *expire_head;
static struct rtos_timer *expire_tail;

static void expire_enqueue(struct rtos_timer *t)
{
    t->next = NULL;
    if (!expire_tail)
        expire_head = t;
    else
        expire_tail->next = t;
    expire_tail = t;
}

/** Cascading L1 → L0 **/
static void cascade_lvl1(void)
{
    uint32_t idx = (g_tw.current >> LVL0_BITS) & (LVL1_SIZE - 1);
    struct rtos_timer *t = g_tw.lvl1[idx];
    g_tw.lvl1[idx] = NULL;

    while (t) {
        struct rtos_timer *next = t->next;
        wheel_enqueue(t);
        t = next;
    }
}

/** Timer ISR **/
void timer_isr(void)
{
    uint64_t now = hw_timer_now();
    g_tw.current = now;
/* At any moment:
 * lvl0 contains timers expiring in [now, now + 255]
 * lvl1 contains timers expiring in [now + 256, now + 256×64]
 * This invariant must hold before checking for expirations.
 * If it doesn’t, timers simply become invisible. */
  
    if ((now & (LVL0_SIZE - 1)) == 0)
        cascade_lvl1();

    uint32_t idx = now & (LVL0_SIZE - 1);
    struct rtos_timer *t = g_tw.lvl0[idx];
    g_tw.lvl0[idx] = NULL;

    while (t) {
        struct rtos_timer *next = t->next;

        if (t->active) {
            t->active = false;
            expire_enqueue(t);
        }

        t = next;
    }

    program_next_deadline();
    wake_timer_task();
}

/** Timer task (callback execution) **/
void timer_task(void)
{
    while (1) {
        struct rtos_timer *t;

        unsigned long flags = irq_save();
        t = expire_head;
        if (t) {
            expire_head = t->next;
            if (!expire_head)
                expire_tail = NULL;
        }
        irq_restore(flags);

        if (!t) {
            /* block until woken */
            continue;
        }

        uint32_t gen = t->gen;
        t->cb(t->arg);

        if (t->period && t->active == false) {
            t->expiry += t->period;
            t->active = true;
            timer_start(t, t->period);
        }
    }
}
