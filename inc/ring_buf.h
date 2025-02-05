/**
 * @file ring_buf.h
 * This module contains the implementation and methods for 
 * the ring buffer data structure A.K.A Circular queue
 * 
 * @author Gopala Krishnan
 */

#ifndef RING_BUF_H
#define RING_BUF_H

#include <stdlib.h>
#include <string.h>

/* -- Struct declaration and types -- */

/** @defgroup ring_buf Definitions
 *  @{
 */
#define BUFSIZE 1000

/** @brief Struct representing a ring buffer element */
typedef struct {
    void* data;
} buf_node_t;

/** @brief Struct representing a ring buffer */
typedef struct {
    buf_node_t buf[BUFSIZE];
    int write_idx;
    int read_idx;
} ring_buf_t;
/** @} */

/* -- Function prototypes -- */

/**
 * @brief Initialize the ring buffer
 * @param buf The ring buffer
 */
void buf_init(ring_buf_t* buf);

/** 
 * @brief Enqueue data into the ring buffer
 * @param buf The ring buffer
 * @param data The data to be enqueued, this is a pointer to the actual data
 * @param size The size of the data
 * @note The data is copied into the ring buffer
 * @return 0 on success, -1 on failure
 */
int buf_enqueue(ring_buf_t* buf, void* data, size_t size);

/**
 * @brief Dequeue data from the ring buffer
 * @param buf The ring buffer
 * @return The data dequeued, NULL if the buffer is empty
 * @note The data is pointer to the actual data, which needs to be freed by the caller
 */
void* buf_dequeue(ring_buf_t* buf);

/**
 * @brief Destroy the ring buffer
 * @param buf The ring buffer
 * @note Frees the memory allocated for the data in the buffer
 */
void buf_destroy(ring_buf_t* buf);

#endif