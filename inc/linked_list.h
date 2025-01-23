/**
 * @file linked_list.h
 * 
 * This module represents a generic doubly linked-list data-structure.
 * A linked list is a chain of nodes linked together to form a collection.
 * Each node contains a pointer to the actual data associated with it. 
 * 
 * @author Gopala Krishnan
 */
#include <stdlib.h>
#include <stdbool.h>

/** @defgroup Linked list Definitions
 *  @{
 */

/* ------ Types Declaration ------- */
/** @brief Struct representing a list node */
typedef struct node_t {
    struct node_t* next;
    struct node_t* prev;
    void* data;
} node_t;

/** @brief Struct representing a doubly linked-list */
typedef struct {
    node_t* head;
    node_t* tail;
    size_t length;
} list_t;

typedef bool (*Predicate)(void *, void *);
typedef void (*PrintFn)(void*);


/* ---- Methods ------ */

/** 
 * @brief Method that allocates a node object with the data provided. 
 * @param[in] data Pointer to the data from which a node will be created.
 * A copy of the data is created inside the node.
 * @param[in] size size of the data that the pointer points to.
 * @return pointer to the node object that was created, NULL on failure
 * 
*/
node_t* alloc_node(void* data, size_t size);

/**
 * @brief Method that frees the memory for the node pointer
 */
void free_node(node_t* node);

/**
 * @brief Method that initializes a list
 * @param[in] list to initialize
 */
void init_list(list_t* list);

/**
 * @brief Inserts a node at the head of the list
 * @param[in] list where node needs to be inserted
 * @param[in] node node to insert to the head of the list
 */
void insert_head(list_t* list, node_t* node);

/**
 * @brief Inserts a node at the tail of the list
 * @param[in] list where node needs to be insert
 * @param[in] node node to insert to the tail of the list
 */
void insert_tail(list_t* list, node_t* node);

/**
 * @brief Inserts a Element after a reference node in the list
 * @param[in] list where node needs to be insert
 * @param[in] node node to insert in the list
 * @param[in] ref_node reference node after which the current node needs to be inserted
 */
void insert_after(list_t* list, node_t* node, node_t* ref_node);
/**
 * @brief Inserts a Element before  a reference node in the list
 * @param[in] list where node needs to be insert
 * @param[in] node node to insert in the list
 * @param[in] ref_node reference node before which the current node needs to be inserted
 */
void insert_before(list_t* list, node_t* node, node_t* ref_node);

/**
 * @brief Remove node from the head of the list
 * @param[in] list List from which element needs to be removed
 * @return node that was removed, null if doesnt exist
 */
node_t* remove_head(list_t* list);

/**
 * @brief Remove node from the tail of the list
 * @param[in] list List from which element needs to be removed
 * @return node that was removed, null if doesnt exist
 */
node_t* remove_tail(list_t* list);

/**
 * @brief Remove node from the list
 * @param[in] list list from where the node needs to be removed.
 * @param[in] node node to remove from the list
 */
void remove_node(list_t* list, node_t* node);

/**
 * @brief Method that finds a node according to given predicate function
 * @param[in] list linked list from where need to find the data
 * @param[in] predicateFn Function which will be used to verify if the correct node is found
 * @param[in] search_data data that needs to be searched for
 * @return pointer to the node if exists else NULL
 */
node_t* find_node(list_t* list, Predicate predicateFn, void* search_data);


/**
 * @brief Method that prints the elements of the list
 * @param[in] list linked list from which elements needs to be printed
 * @param[in] PrintFn function that prints an element of the node
 */
void print_list(list_t* list, PrintFn printfn);

/** 
 *  @}
 */