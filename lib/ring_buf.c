#include <ring_buf.h>
#include <assert.h>
#include <stdlib.h>

void buf_init(ring_buf_t* buf) {
    assert(buf != NULL);
    buf->write_idx = 0;
    buf->read_idx = 0;
}

int buf_enqueue(ring_buf_t* buf, void* data, size_t size) {
    assert(buf != NULL && data != NULL);
    int next_write_idx = (buf->write_idx + 1) % BUFSIZE;
    if (next_write_idx == buf->read_idx) {
        // Queue full
        return -1;
    }
    void* new_data = malloc(size);
    if (new_data == NULL) {
        // Memory allocation failed
        return -1;
    }
    memcpy(new_data, data, size);
    buf->buf[buf->write_idx].data = new_data;
    buf->write_idx = next_write_idx;
    return 0;
}

void* buf_dequeue(ring_buf_t* buf) {
    assert(buf != NULL);
    if (buf->read_idx == buf->write_idx) {
        // Queue empty
        return NULL;
    }
    void* data = buf->buf[buf->read_idx].data;
    buf->read_idx = (buf->read_idx + 1) % BUFSIZE;
    return data;
}

void buf_destroy(ring_buf_t* buf) {
    assert(buf != NULL);
    while (buf->read_idx != buf->write_idx) {
        free(buf->buf[buf->read_idx].data);
        buf->read_idx = (buf->read_idx + 1) % BUFSIZE;
    }
}