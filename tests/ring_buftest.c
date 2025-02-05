#include <stdio.h>
#include <assert.h>
#include <ring_buf.h>

// Test for initializing the ring buffer
void test_buf_init() {
    ring_buf_t buf;
    buf_init(&buf);
    assert(buf.write_idx == 0);
    assert(buf.read_idx == 0);
    printf("test_buf_init passed\n");
    buf_destroy(&buf);
}

// Test for enqueuing data into the ring buffer
void test_buf_enqueue() {
    ring_buf_t buf;
    buf_init(&buf);
    int data = 42;
    int result = buf_enqueue(&buf, &data, sizeof(data));
    assert(result == 0);
    assert(*(int*)buf.buf[buf.write_idx - 1].data == data);
    printf("test_buf_enqueue passed\n");
    buf_destroy(&buf);

}

// Test for dequeuing data from the ring buffer
void test_buf_dequeue() {
    ring_buf_t buf;
    buf_init(&buf);
    int data = 42;
    buf_enqueue(&buf, &data, sizeof(data));
    int* dequeued_data = (int*)buf_dequeue(&buf);
    assert(dequeued_data != NULL);
    assert(*dequeued_data == data);
    printf("test_buf_dequeue passed\n");
    buf_destroy(&buf);

}

// Test for checking if the ring buffer is empty
void test_buf_is_empty() {
    ring_buf_t buf;
    buf_init(&buf);
    assert(buf.read_idx == buf.write_idx);
    int data = 42;
    buf_enqueue(&buf, &data, sizeof(data));
    buf_dequeue(&buf);
    assert(buf.read_idx == buf.write_idx);
    printf("test_buf_is_empty passed\n");
    buf_destroy(&buf);
}

// Test for checking if the ring buffer is full
void test_buf_is_full() {
    ring_buf_t buf;
    buf_init(&buf);
    int data = 42;
    for (int i = 0; i < BUFSIZE - 1; i++) {
        assert(buf_enqueue(&buf, &data, sizeof(data)) != -1);
    }
    int result = buf_enqueue(&buf, &data, sizeof(data));
    assert(result == -1);
    printf("test_buf_is_full passed\n");
    buf_destroy(&buf);
}

int main() {
    test_buf_init();
    test_buf_enqueue();
    test_buf_dequeue();
    test_buf_is_empty();
    test_buf_is_full();
    printf("All tests passed\n");
    return 0;
}