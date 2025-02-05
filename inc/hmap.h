/**
 * @file hmap.h
 * This file contains implementation of a hash-map using linked-list
 * the hashmap uses a simple hash function based on modulo and uses linkedlist
 * for chaining
 * 
 * @author Gopala Krishnan
 */

#ifndef HMAP_H
#define HMAP_H

#include <linked_list.h>


/* -- Struct declarations --- */


/** @defgroup HMAP Definitions
 *  @{
 */

#define BUCKET_SIZE 10000

typedef struct {
    list_t table[BUCKET_SIZE];
} hmap_t;

/**
 * @brief Method that inserts a element into the hashmap with the given key
 * @param[in] hmap Hashmap where the element needs to be inserted
 * @param[in] key key for the element
 * @param[in] data to enter for the element
 * @param[in] size size of the data provided in bytes
 * @return 0 on success -1 on failure
 */
int hmap_put(hmap_t* hmap, char* key, void* data, size_t size);

/**
 * @brief Method that inserts a element into the hashmap with the given key
 * @param[in] hmap Hashmap from where element needs to be retrieved
 * @param[in] key key for the element
 */
void* hmap_get(hmap_t* hmap, char* key);

/**
 * @brief Method that removes the element from hashmap with the given key
 * This will also free the resources associated with the element
 * @param[in] hmap Hashmap from where element needs to be deleted
 * @param[in] key key for the element
 */
void hmap_remove(hmap_t* hmap, char* key);

/**
 * @brief Method that frees the memory allocated for the hashmap
 * @param[in] hmap hashmap to free
 */
void hmap_destroy(hmap_t* hmap);

/**
 * @}
 */

#endif