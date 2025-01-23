
#include <linked_list.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

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

int main() {
   
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

    printf("Hurdle 1 passed\n");

    copy->x = 2;
    assert(some.x != 2 && copy->x == 2);

    list_t list_struct;
    list_t* list = &list_struct;
    init_list(list);

    insert_head(list, struct_node);
    assert(list->length == 1);
    assert(list->head == struct_node);
    assert(list->tail == struct_node);

    printf("Hurdle 2 passed\n");

    some_struct some2;
    some2.x = 3;
    some2.y = 5;
    some2.ptr = &a;
    node_t *struct_node2 = alloc_node(&some2, sizeof(some_struct));
    insert_head(list, struct_node2);
    assert(list->length == 2);
    assert(list->head == struct_node2);
    assert(list->tail == struct_node);

    printf("Hurdle 3 passed\n");

    some_struct some3;
    some3.x = 1;
    some3.y = 2;
    some3.ptr = &a;
    node_t *struct_node3 = alloc_node(&some3, sizeof(some_struct));
    insert_tail(list, struct_node3);
    assert(list->length == 3);
    assert(list->head == struct_node2);
    assert(list->tail == struct_node3);

    printf("Hurdle 4 passed\n");

    node_t *find_struct_node =
        find_node(list, check_some_struct, struct_node2->data);

    some_struct *find_struct = (some_struct *)find_struct_node->data;
    some_struct *struct2 = (some_struct *)struct_node2->data;
    assert(find_struct->x == struct2->x);
    assert(find_struct->ptr == struct2->ptr);
    assert(find_struct->y == struct2->y);
    assert(list->length == 3);
    assert(list->head == struct_node2);
    assert(list->tail == struct_node3);

    remove_node(list, find_struct_node);
    assert(list->length == 2);
    assert(list->head == struct_node);
    assert(list->tail == struct_node3);
    printf("Hurdle 5 passed!\n");

    insert_after(list, find_struct_node, struct_node3);
    assert(list->length == 3);
    assert(list->head == struct_node);
    assert(list->tail == find_struct_node);
    printf("Hurdle 6 passed!\n");

    node_t* tail = remove_tail(list);
    assert(tail == find_struct_node);
    assert(list->length == 2);
    assert(list->tail == struct_node3);
    assert(list->head ==  struct_node);
    printf("Hurdle 7 passed!\n");

    node_t* front = remove_head(list);
    assert(front == struct_node);
    assert(list->length == 1);
    assert(list->tail == struct_node3);
    assert(list->head == struct_node3);
    printf("Hurdle 8 passed!\n");

    insert_before(list, tail, struct_node3);
    insert_after(list, front, struct_node3);
    assert(list->length == 3);
    assert(list->tail == front);
    assert(list->head == tail);
    printf("Hurdle 9 passed!\n");

    return 0;
}