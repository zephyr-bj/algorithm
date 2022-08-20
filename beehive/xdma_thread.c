/*
struct xdma_user_obj {
        unsigned long magic;    /* structure ID for sanity checks */
        struct xdma_dev *xdev;  /* parent device */
        char name[16];          /* name of this object */
        int version;            /* version of this object */

        struct xdma_kthread *cmplthp;
        /* completion status thread list for the queue */
        struct list_head cmplthp_list;
        /* pending work thread list */
        /* cpu attached to intr_work */
        unsigned int intr_work_cpu;

        spinlock_t lock;                /* protects concurrent access */
        int (*xobj_poll_proc)(struct xdma_user_obj*);
        int (*xobj_flag_proc)(struct xdma_user_obj*);
        // you can add any elements you want
};
*/
  
#include <linux/kthread.h>    // kthread_should_stop
                              // kthread_create_on_node
                              // kthread_bind
                              // kthread_stop
#include <linux/sched.h>      // schedule               // kernel/sched/core.c
                              // wake_up_process
// spin_lock_irqsave

/**
 * @struct - xdma_kthread
 * @brief       xdma thread book keeping parameters
 */
struct xdma_kthread {
        /**  thread lock*/
        spinlock_t lock;
        /**  name of the thread */
        char name[16];
        /**  cpu number for which the thread associated with */
        unsigned short cpu;
        /**  thread id */
        unsigned short id;
        /**  thread sleep timeout value */
        unsigned int timeout;
        /**  flags for thread */
        unsigned long flag;
        /**  thread wait queue */
        wait_queue_head_t waitq;
        /* flag to indicate scheduling of thread */
        unsigned int schedule;
        /**  kernel task structure associated with thread*/
        struct task_struct *task;
        /**  thread work list count */
        unsigned int work_cnt;
        /**  thread work list count */
        struct list_head work_list;
        /**  thread initialization handler */
        int (*finit)(struct xdma_kthread *);
        /**  thread pending handler */
        int (*fpending)(struct list_head *);
        /**  thread peocessing handler */
        int (*fproc)(struct list_head *);
        /**  thread done handler */
        int (*fdone)(struct xdma_kthread *);
};

static struct xdma_kthread *cs_threads;
static unsigned int thread_cnt;

static int xdma_thread_cmpl_status_pend(struct list_head *work_item)
{
        struct xdma_user_obj *xobj = list_entry(work_item, struct xdma_user_obj,
                cmplthp_list);
        int pend = 0;
        pend = xobj->xobj_flag_proc(xobj);

        return pend;
}

static int xdma_thread_cmpl_status_proc(struct list_head *work_item)
{
        struct xdma_user_obj *xobj = list_entry(work_item, struct xdma_user_obj, 
                                                cmplthp_list);
        xobj->xobj_poll_proc(xobj);
        return 0;
}

static inline int xthread_work_pending(struct xdma_kthread *thp)
{
        struct list_head *work_item, *next;

        /* any work items assigned to this thread? */
        if (list_empty(&thp->work_list))
                return 0;

        /* any work item has pending work to do? */
        list_for_each_safe(work_item, next, &thp->work_list) {
                if (thp->fpending && thp->fpending(work_item))
                        return 1;
        }
        return 0;
}

static inline void xthread_reschedule(struct xdma_kthread *thp)
{
        if (thp->timeout) {
                wait_event_interruptible_timeout(thp->waitq, thp->schedule,
                                              msecs_to_jiffies(thp->timeout));
        } else {
                wait_event_interruptible(thp->waitq, thp->schedule);
        }
}

/**
 * kthread_should_stop - should this kthread return now?
 *
 * When someone calls kthread_stop() on your kthread, it will be woken
 * and this will return true.  You should then return, and your return
 * value will be passed through to kthread_stop().
 */
//bool kthread_should_stop(void)

static int xthread_main(void *data)
{
        struct xdma_kthread *thp = (struct xdma_kthread *)data;
        disallow_signal(SIGPIPE);
        if (thp->finit)
                thp->finit(thp);
        while (!kthread_should_stop()) {
                struct list_head *work_item, *next;
                /* any work to do? */
                spin_lock(&(thp)->lock);
                if (!xthread_work_pending(thp)) {
                      spin_unlock(&(thp)->lock);
                      xthread_reschedule(thp);
                      spin_lock(&(thp)->lock);
                }
                thp->schedule = 0;
                if (thp->work_cnt) {
                        /* do work */
                        list_for_each_safe(work_item, next, &thp->work_list) {
                                thp->fproc(work_item);
                        }
                }
                spin_unlock(&(thp)->lock);
                schedule();
        }
        if (thp->fdone)
                thp->fdone(thp);
        return 0;
}

int xdma_kthread_start(struct xdma_kthread *thp, char *name, int id)
{
        int len;
        int node;

        if (thp->task) {
                return -EINVAL;
        }
        len = snprintf(thp->name, sizeof(thp->name), "%s%d", name, id);
        if (len < 0) {
                return -EINVAL;
        }

        thp->id = id;

        spin_lock_init(&thp->lock);
        INIT_LIST_HEAD(&thp->work_list);
        init_waitqueue_head(&thp->waitq);

        node = cpu_to_node(thp->cpu);

        thp->task = kthread_create_on_node(xthread_main, (void *)thp,
                                        node, "%s", thp->name);
        if (IS_ERR(thp->task)) {
                thp->task = NULL;
                return -EFAULT;
        }

        kthread_bind(thp->task, thp->cpu);

        wake_up_process(thp->task);
        return 0;
}


int xdma_kthread_stop(struct xdma_kthread *thp)
{
        int rv;

        if (!thp->task) {
                return 0;
        }

        thp->schedule = 1;
        rv = kthread_stop(thp->task);
        if (rv < 0) {
                return rv;
        }

        thp->task = NULL;
        return 0;
}


void xdma_thread_remove_work(struct xdma_user_obj *xobj)
{
        struct xdma_kthread *cmpl_thread;
        unsigned long flags;

        spin_lock_irqsave(&xobj->lock, flags);
        cmpl_thread = xobj->cmplthp;
        xobj->cmplthp = NULL;
        spin_unlock_irqrestore(&xobj->lock, flags);

        if (cmpl_thread) {
                lock_thread(cmpl_thread);
                list_del(&xobj->cmplthp_list);
                cmpl_thread->work_cnt--;
                unlock_thread(cmpl_thread);
        }
}

void xdma_thread_add_work(struct xdma_user_obj *xobj)
{
        struct xdma_kthread *thp = cs_threads;
        unsigned int v = 0;
        int i, idx = thread_cnt;
        unsigned long flags;

        /* Polled mode only */
        for (i = 0; i < thread_cnt; i++, thp++) {
                spin_lock(&(thp)->lock);
                if (idx == thread_cnt) {
                        v = thp->work_cnt;
                        idx = i;
                } else if (!thp->work_cnt) {
                        idx = i;
                        spin_unlock(&(thp)->lock);
                        break;
                } else if (thp->work_cnt < v)
                        idx = i;
                spin_unlock(&(thp)->lock);
        }

        thp = cs_threads + idx;
        spin_lock(&(thp)->lock);
        list_add_tail(&xobj->cmplthp_list, &thp->work_list);
        xobj->intr_work_cpu = idx;
        thp->work_cnt++;
        spin_unlock(&(thp)->lock);

        spin_lock_irqsave(&xobj->lock, flags);
        xobj->cmplthp = thp;
        spin_unlock_irqrestore(&xobj->lock, flags);
}


int xdma_threads_create(unsigned int num_threads)
{
        struct xdma_kthread *thp;
        int rv;
        int cpu;

        if (thread_cnt) {
                return 0;
        }

        cs_threads = kzalloc(num_threads * sizeof(struct xdma_kthread),
                                        GFP_KERNEL);
        if (!cs_threads) {
                return -ENOMEM;
        }

        /* N dma writeback monitoring threads */
        thp = cs_threads;
        for_each_online_cpu(cpu) {
                thp->cpu = cpu;
                thp->timeout = 0;
                thp->fproc = xdma_thread_cmpl_status_proc;
                thp->fpending = xdma_thread_cmpl_status_pend;
                rv = xdma_kthread_start(thp, "cmpl_status_th", thread_cnt);
                if (rv < 0)
                        goto cleanup_threads;

                thread_cnt++;
                if (thread_cnt == num_threads)
                        break;
                thp++;
        }

        return 0;

cleanup_threads:
        kfree(cs_threads);
        cs_threads = NULL;
        thread_cnt = 0;

        return rv;
}

void xdma_threads_destroy(void)
{
        int i;
        struct xdma_kthread *thp;

        if (!thread_cnt)
                return;

        /* N dma writeback monitoring threads */
        thp = cs_threads;
        for (i = 0; i < thread_cnt; i++, thp++)
                if (thp->fproc)
                        xdma_kthread_stop(thp);

        kfree(cs_threads);
        cs_threads = NULL;
        thread_cnt = 0;
}


// int rv = xdma_threads_create(xdev->h2c_channel_max + xdev->c2h_channel_max);
// calls kthread_create_on_node starts kernel thread as "xthread_main", num_threads times

// xdma_thread_add_work(engine);
// calls list_add_tail(&engine->cmplthp_list, &thp->work_list);
//        engine->intr_work_cpu = idx;
//        thp->work_cnt++;

