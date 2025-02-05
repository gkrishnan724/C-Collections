#include <vector.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int vec_init(vec_t* vec) {
    assert(vec != NULL);
    vec->vec = malloc(INITIAL_CAPACITY * sizeof(vec_node_t));
    if (vec->vec == NULL) {
        return -1;
    }
    vec->size = 0;
    vec->capacity = INITIAL_CAPACITY;
    return 0;
}

int vec_append(vec_t* vec, void* data, size_t size) {
    assert(vec != NULL && data != NULL);
    if (vec->size == vec->capacity) {
        int new_capacity = vec->capacity * 2;
        vec_node_t* new_vector = realloc(vec->vec, new_capacity * sizeof(vec_node_t));
        if (new_vector == NULL) {
            return -1;
        }
        vec->vec = new_vector;
        vec->capacity = new_capacity;      
    }
    vec->vec[vec->size].data = malloc(size);
    if (vec->vec[vec->size].data == NULL) {
        return -1;
    }
    memcpy(vec->vec[vec->size].data, data, size);
    vec->size++;
    return 0;
}

void* vec_get(vec_t* vec, int index) {
    assert(vec != NULL);
    if (index < 0 || index >= vec->size) {
        return NULL;
    }
    return vec->vec[index].data;
}

int vec_insert(vec_t* vec, int index, void* data, size_t size) {
    assert(vec != NULL && data != NULL);
    if (index < 0 || index >= vec->size) {
        return -1;
    }
    if (vec->size == vec->capacity) {
        int new_capacity = vec->capacity * 2;
        vec_node_t* new_vector = realloc(vec->vec, new_capacity * sizeof(vec_node_t));
        if (new_vector == NULL) {
            return -1;
        }
        vec->vec = new_vector;
        vec->capacity = new_capacity;      
    }
    for (int i = vec->size; i > index; i--) {
        vec->vec[i] = vec->vec[i - 1];
    }
    vec->vec[index].data = malloc(size);
    if (vec->vec[index].data == NULL) {
        return -1;
    }
    memcpy(vec->vec[index].data, data, size);
    vec->size++;
    return 0;
}

int vec_set(vec_t* vec, int index, void* data, size_t size) {
    assert(vec != NULL && data != NULL);
    if (index < 0 || index >= vec->size) {
        return -1;
    }
    void* new_data = malloc(size);
    if (new_data == NULL) {
        return -1;
    }
    free(vec->vec[index].data);
    vec->vec[index].data = new_data;
    memcpy(vec->vec[index].data, data, size);
    return 0;
}

void* vec_remove(vec_t* vec, int index) {
    assert(vec != NULL);
    if (index < 0 || index >= vec->size) {
        return NULL;
    }
    void* data = vec->vec[index].data;
    for (int i = index; i < vec->size - 1; i++) {
        vec->vec[i] = vec->vec[i + 1];
    }
    vec->size--;
    return data;
}

void vec_destroy(vec_t* vec) {
    assert(vec != NULL);
    for (int i = 0; i < vec->size; i++) {
        free(vec->vec[i].data);
    }
    free(vec->vec);
    vec->size = 0;
    vec->capacity = 0;
}