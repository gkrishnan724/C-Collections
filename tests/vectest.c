#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector.h>

void test_vec_append() {
    vec_t vec;
    vec_init(&vec);

    int data1 = 42;
    int data2 = 84;
    int data3 = 126;

    assert(vec_append(&vec, &data1, sizeof(data1)) == 0);
    assert(vec_append(&vec, &data2, sizeof(data2)) == 0);
    assert(vec_append(&vec, &data3, sizeof(data3)) == 0);

    assert(*(int*)vec_get(&vec, 0) == data1);
    assert(*(int*)vec_get(&vec, 1) == data2);
    assert(*(int*)vec_get(&vec, 2) == data3);

    printf("test_vec_append passed\n");

    vec_destroy(&vec);
}

void test_vec_set() {
    vec_t vec;
    vec_init(&vec);

    int data1 = 42;
    int data2 = 84;

    vec_append(&vec, &data1, sizeof(data1));
    assert(vec_set(&vec, 0, &data2, sizeof(data2)) == 0);

    assert(*(int*)vec_get(&vec, 0) == data2);

    printf("test_vec_set passed\n");

    vec_destroy(&vec);
}

void test_vec_remove() {
    vec_t vec;
    vec_init(&vec);

    int data1 = 42;
    int data2 = 84;

    vec_append(&vec, &data1, sizeof(data1));
    vec_append(&vec, &data2, sizeof(data2));

    int* deleted_data = (int*)vec_remove(&vec, 0);
    assert(deleted_data != NULL);
    assert(*deleted_data == data1);
    free(deleted_data);

    assert(*(int*)vec_get(&vec, 0) == data2);

    printf("test_vec_remove passed\n");

    vec_destroy(&vec);
}

void test_vec_insert() {
    vec_t vec;
    vec_init(&vec);

    int data1 = 42;
    int data2 = 84;
    int data3 = 23;
    vec_append(&vec, &data1, sizeof(data1));
    vec_append(&vec, &data2, sizeof(data2));

    assert(vec_insert(&vec, 1, &data3, sizeof(data3)) == 0);

    assert(*(int*)vec_get(&vec, 0) == data1);
    assert(*(int*)vec_get(&vec, 1) == data3);
    assert(*(int*)vec_get(&vec, 2) == data2);

    printf("test_vec_insert passed\n");

    vec_destroy(&vec);
}

int main() {
    test_vec_append();
    test_vec_set();
    test_vec_remove();
    test_vec_insert();
    return 0;
}