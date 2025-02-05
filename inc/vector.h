/**
 * @file vector.h
 * This module contains the implementation and methods for
 * a vector data structure. A vector is basically a dynamically 
 * resizing array.
 * 
 * @author Gopala Krishnan
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

/* -- Struct declaration and types -- */

#define INITIAL_CAPACITY 10

/** @brief Structure defining a vector element */
typedef struct {
    void* data;
} vec_node_t;

/** @brief Structure representing the vector */
typedef struct {
    vec_node_t* vec;
    int size;
    int capacity;
} vec_t;

/* -- Function prototypes -- */

/**
 * @brief Initialize the vector
 * @param vec The vector to initialize
 */
int vec_init(vec_t* vec);

/**
 * @brief append an element to the end of the vector
 * @param vec The vector
 * @param data The data to push into the vector
 * @param size The size of the data
 * @return 0 on success, -1 on failure
 */
int vec_append(vec_t* vec, void* data, size_t size);

/**
 * @brief Get the element at the given index from 
 * the vector
 * @param vec The vector
 * @param index The index of the element to get
 * @return Pointer to the element at the given index, NULL if not found
 */
void* vec_get(vec_t* vec, int index);

/**
 * @brief Insert an element at the given index in the vector
 * @param vec The vector
 * @param index The index to insert the element
 * @param data The data to insert
 * @param size The size of the data
 * @return 0 on success, -1 on failure
 * @note the data is copied into the vector
 */
int vec_insert(vec_t* vec, int index, void* data, size_t size);

/**
 * @brief Set the element at the given index in the vector
 * @param vec The vector
 * @param index The index of the element to set
 * @param data The data to set
 * @param size The size of the data
 * @return 0 on success, -1 on failure
 * @note the data is copied into the vector
 */
int vec_set(vec_t* vec, int index, void* data, size_t size);

/**
 * @brief Delete the element at the given index from the vector
 * @param vec The vector
 * @param index The index of the element to delete
 * @return Pointer to the element that was deleted, NULL if not found
 * @note its responsibility of the caller to free the memory
 */
void* vec_remove(vec_t* vec, int index);

/**
 * @brief Destroy the vector
 * @param vec The vector to destroy
 */
void vec_destroy(vec_t* vec);


#endif