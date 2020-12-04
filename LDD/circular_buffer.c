typedef struct 
{
    uint8_t * const buf;
    int head;
    int tail;
    const int len;
} cbuf_t;

int cb_push_discard(cbuf_t *cb, uint8_t data)
{
    int next = (cb->head + 1)%cb->len; 
    if (next == cb->tail) return -1;
    cb->head = next;
    cb->buf[cb->head] = data;
    return 0; 
}

int cb_push_overwrite(cbuf_t *cb, uint8_t data)
{
    cb->head = (cb->head + 1)%cb->len; 
    if (cb->head == cb->tail) cb->tail = (ct->tail + 1)%cb->len;
    cb->buf[cb->head] = data;
    return 0; 
}

int cb_pop(cbuf_t *c, uint8_t *data)
{
    if (cb->head == cb->tail) return -1;
    *data = cb->buf[cb->tail]; 
    cb->tail = (cb->tail + 1)%cb->len;
    return 0; 
}

