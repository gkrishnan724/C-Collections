#include <linked_list.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

node_t* alloc_node(void* data, size_t size) {
    node_t* node = NULL;
    void* node_data = malloc(size);
    if (node_data == NULL) {
        goto mem_error;
    }
    node = malloc(sizeof(node_t));
    if (node == NULL) {
        goto mem_error;
    }
    memcpy(node_data, data, size);
    node->data = node_data;
    node->next = NULL;
    node->prev = NULL;
    return node;

mem_error:
    if (node_data != NULL) {
        free(node_data);
    }
    if (node != NULL) {
        free(node);
    }
    return NULL;
}

void free_node(node_t* node) {
    free(node->data);
    free(node);
}

void init_list(list_t* list) {
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
}

void insert_head(list_t* list, node_t* node) {
    assert(list != NULL && node != NULL);
    if (list->length == 0) {
        list->head = node;
        list->tail = node;
    } else {
        assert(list->head != NULL);
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
    list->length += 1;
}

void insert_tail(list_t* list, node_t* node) {
    assert(list != NULL && node != NULL);
    if (list->length == 0) {
        list->head = node;
        list->tail = node;
    } else {
        assert(list->tail != NULL);
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
    list->length += 1;
}

void insert_after(list_t* list, node_t* node, node_t* ref_node) {
    assert(list != NULL && node != NULL && ref_node != NULL);
    if (ref_node == list->tail) {
        insert_tail(list, node);
    } else {
        node->next = ref_node->next;
        node->prev = ref_node;
        if (node->next != NULL) {
            node->next->prev = NULL;
        }
        ref_node->next = node;
        list->length += 1;
    }
}

void insert_before(list_t* list, node_t* node, node_t* ref_node) {
    assert(list != NULL && node != NULL && ref_node != NULL);
    if (ref_node == list->head) {
        insert_head(list, node);
    } else {
        if (ref_node->prev != NULL) {
            ref_node->prev->next = node;
        }
        node->prev = ref_node->prev;
        node->next = ref_node;
        list->length += 1;
    }
}

node_t* remove_head(list_t* list) {
    assert(list != NULL);
    if (list->length == 0) {
        return NULL;
    }
    node_t* node = list->head;
    list->head = list->head->next;
    if (list->head != NULL) {
        assert(list->length > 1);
        list->head->prev = NULL;
    } else {
        // Means length has become zero
        assert(list->length == 1);
        list->tail = NULL;
    }
    node->next = NULL;
    node->prev = NULL;
    list->length -= 1;

    return node;
}

node_t* remove_tail(list_t* list) {
    assert(list != NULL);
    if (list->length == 0) {
        return NULL;
    }

    node_t* node = list->tail;
    list->tail = list->tail->prev;
    if (list->tail != NULL) {
        assert(list->length > 1);
        list->tail->next = NULL;
    } else {
        // Means length has become zero
        assert(list->length == 1);
        list->head = NULL; 
    }
    node->next = NULL;
    node->prev = NULL;
    list->length -= 1;
    return node;
}   

void remove_node(list_t* list, node_t* node) {
    assert(list != NULL && node != NULL);
    if (node == list->head) {
        remove_head(list);
    } else if (node == list->tail) {
        remove_tail(list);
    } else {
        node->next->prev = node->prev;
        node->prev->next = node->next;
        node->next = NULL;
        node->prev = NULL;
        list->length -= 1;
    }
}

node_t* find_node(list_t* list, Predicate predicateFn, void* search_data) {
    assert(list != NULL && predicateFn != NULL && search_data != NULL);
    if (list->length == 0) {
        return NULL;
    }
    node_t* iter = list->head;
    while(iter != NULL) {
        if (predicateFn(iter->data, search_data)) {
            return iter;
        }
        iter = iter->next;
    }
    return NULL;
}

void print_list(list_t* list, PrintFn printfn) {
    if (list == NULL || list->length == 0)
        return;
    
    node_t* iter = list->head;
    while (iter != NULL) {
        printfn(iter->data);
        printf("->");
    }
    printf("\n");
}

