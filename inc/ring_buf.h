/**
 * @file ring_buf.h
 * This module contains the implementation and methods for 
 * the ring buffer data structure A.K.A Circular queue
 * 
 * @author Gopala Krishnan
 */

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
} ring_buf_t;
/** @} */