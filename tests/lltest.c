#include <assert.h>
#include <stdio.h>
#include "linked_list.h"

typedef struct {
    int x;
    short y;
    int *ptr;
} some_struct;

bool check_some_struct(void *list_elm, void *search_item) {
    some_struct *list_struct = (some_struct *)list_elm;
    some_struct *search_struct = (some_struct *)search_item;

    return (list_struct->ptr == search_struct->ptr) &&
           (list_struct->x == search_struct->x) &&
           (list_struct->y == search_struct->y);
}

void test_alloc_node() {
    some_struct some;
    int a = 1;
    some.x = 1;
    some.y = 2;
    some.ptr = &a;
    node_t *struct_node = alloc_node(&some, sizeof(some_struct));
    // Check if data allocated properly
    some_struct *copy = (some_struct *)struct_node->data;
    assert(copy->x == 1);
    assert(copy->y == 2);
    assert(copy->ptr == some.ptr);

    printf("test_alloc_node passed\n");

    copy->x = 2;
    assert(some.x != 2 && copy->x == 2);
}

void test_init_list() {
    list_t list_struct;
    list_t* list = &list_struct;
    init_list(list);
    assert(list->head == NULL);
    assert(list->tail == NULL);
    assert(list->length == 0);

    printf("test_init_list passed\n");
}

void test_insert_head() {
    list_t list_struct;
    list_t* list = &list_struct;
    init_list(list);

    some_struct some;
    int a = 1;
    some.x = 1;
    some.y = 2;
    some.ptr = &a;
    node_t *struct_node = alloc_node(&some, sizeof(some_struct));

    insert_head(list, struct_node);
    assert(list->head == struct_node);
    assert(list->tail == struct_node);
    assert(list->length == 1);

    printf("test_insert_head passed\n");
}

void test_insert_tail() {
    list_t list_struct;
    list_t* list = &list_struct;
    init_list(list);

    some_struct some1, some2;
    int a1 = 1, a2 = 2;
    some1.x = 1;
    some1.y = 2;
    some1.ptr = &a1;
    some2.x = 3;
    some2.y = 4;
    some2.ptr = &a2;
    node_t *struct_node1 = alloc_node(&some1, sizeof(some_struct));
    node_t *struct_node2 = alloc_node(&some2, sizeof(some_struct));

    insert_head(list, struct_node1);
    insert_tail(list, struct_node2);
    assert(list->head == struct_node1);
    assert(list->tail == struct_node2);
    assert(list->length == 2);

    printf("test_insert_tail passed\n");
}

void test_remove_node() {
    list_t list_struct;
    list_t* list = &list_struct;
    init_list(list);

    some_struct some1, some2, some3;
    int a1 = 1, a2 = 2, a3 = 3;
    some1.x = 1;
    some1.y = 2;
    some1.ptr = &a1;
    some2.x = 3;
    some2.y = 4;
    some2.ptr = &a2;
    some3.x = 5;
    some3.y = 6;
    some3.ptr = &a3;
    node_t *struct_node1 = alloc_node(&some1, sizeof(some_struct));
    node_t *struct_node2 = alloc_node(&some2, sizeof(some_struct));
    node_t *struct_node3 = alloc_node(&some3, sizeof(some_struct));

    insert_head(list, struct_node1);
    insert_tail(list, struct_node2);
    insert_tail(list, struct_node3);

    remove_node(list, struct_node2);
    assert(list->length == 2);
    assert(list->head == struct_node1);
    assert(list->tail == struct_node3);

    printf("test_remove_node passed\n");
}

void test_insert_after() {
    list_t list_struct;
    list_t* list = &list_struct;
    init_list(list);

    some_struct some1, some2, some3;
    int a1 = 1, a2 = 2, a3 = 3;
    some1.x = 1;
    some1.y = 2;
    some1.ptr = &a1;
    some2.x = 3;
    some2.y = 4;
    some2.ptr = &a2;
    some3.x = 5;
    some3.y = 6;
    some3.ptr = &a3;
    node_t *struct_node1 = alloc_node(&some1, sizeof(some_struct));
    node_t *struct_node2 = alloc_node(&some2, sizeof(some_struct));
    node_t *struct_node3 = alloc_node(&some3, sizeof(some_struct));

    insert_head(list, struct_node1);
    insert_tail(list, struct_node2);
    insert_after(list, struct_node1, struct_node3);

    assert(list->length == 3);
    assert(list->head == struct_node1);
    assert(list->tail == struct_node2);

    printf("test_insert_after passed\n");
}

void test_remove_tail() {
    list_t list_struct;
    list_t* list = &list_struct;
    init_list(list);

    some_struct some1, some2, some3;
    int a1 = 1, a2 = 2, a3 = 3;
    some1.x = 1;
    some1.y = 2;
    some1.ptr = &a1;
    some2.x = 3;
    some2.y = 4;
    some2.ptr = &a2;
    some3.x = 5;
    some3.y = 6;
    some3.ptr = &a3;
    node_t *struct_node1 = alloc_node(&some1, sizeof(some_struct));
    node_t *struct_node2 = alloc_node(&some2, sizeof(some_struct));
    node_t *struct_node3 = alloc_node(&some3, sizeof(some_struct));

    insert_head(list, struct_node1);
    insert_tail(list, struct_node2);
    insert_tail(list, struct_node3);

    node_t* tail = remove_tail(list);
    assert(tail == struct_node3);
    assert(list->length == 2);
    assert(list->tail == struct_node2);
    assert(list->head == struct_node1);

    printf("test_remove_tail passed\n");
}

void test_remove_head() {
    list_t list_struct;
    list_t* list = &list_struct;
    init_list(list);

    some_struct some1, some2, some3;
    int a1 = 1, a2 = 2, a3 = 3;
    some1.x = 1;
    some1.y = 2;
    some1.ptr = &a1;
    some2.x = 3;
    some2.y = 4;
    some2.ptr = &a2;
    some3.x = 5;
    some3.y = 6;
    some3.ptr = &a3;
    node_t *struct_node1 = alloc_node(&some1, sizeof(some_struct));
    node_t *struct_node2 = alloc_node(&some2, sizeof(some_struct));
    node_t *struct_node3 = alloc_node(&some3, sizeof(some_struct));

    insert_head(list, struct_node1);
    insert_tail(list, struct_node2);
    insert_tail(list, struct_node3);

    node_t* front = remove_head(list);
    assert(front == struct_node1);
    assert(list->length == 2);
    assert(list->tail == struct_node3);
    assert(list->head == struct_node2);

    printf("test_remove_head passed\n");
}

void test_insert_before_and_after() {
    list_t list_struct;
    list_t* list = &list_struct;
    init_list(list);

    some_struct some1, some2, some3;
    int a1 = 1, a2 = 2, a3 = 3;
    some1.x = 1;
    some1.y = 2;
    some1.ptr = &a1;
    some2.x = 3;
    some2.y = 4;
    some2.ptr = &a2;
    some3.x = 5;
    some3.y = 6;
    some3.ptr = &a3;
    node_t *struct_node1 = alloc_node(&some1, sizeof(some_struct));
    node_t *struct_node2 = alloc_node(&some2, sizeof(some_struct));
    node_t *struct_node3 = alloc_node(&some3, sizeof(some_struct));

    insert_head(list, struct_node1);
    insert_tail(list, struct_node2);
    insert_tail(list, struct_node3);

    node_t* tail = remove_tail(list);
    node_t* front = remove_head(list);

    insert_before(list, tail, struct_node2);
    insert_after(list, front, struct_node2);
    assert(list->length == 3);
    assert(list->tail == front);
    assert(list->head == tail);

    printf("test_insert_before_and_after passed\n");
}

int main() {
    test_alloc_node();
    test_init_list();
    test_insert_head();
    test_insert_tail();
    test_remove_node();
    test_insert_after();
    test_remove_tail();
    test_remove_head();
    test_insert_before_and_after();
    return 0;
}