#include <hmap.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

/** @brief Node element for the hashmap */
typedef struct {
    char* key;
    void* data;
} hmap_node_t;


static size_t hash_func(char* key) {
    return strlen(key) % BUCKET_SIZE;
}

static bool match(void* tmp, void* key_void) {
    hmap_node_t* list_data = (hmap_node_t*) tmp;
    char* key = (char*) key_void;
    if (!strcmp(list_data->key, key)) {
        return true;
    }
    return false;
}

int hmap_put(hmap_t* hmap, char* key, void* data, size_t size) {
    assert(hmap != NULL && key != NULL && data != NULL);
    
    /* Allocate memory for data and copy it over */
    void* new_data = malloc(size);
    node_t* ll_node = NULL;
    if (new_data == NULL)
        goto mem_error;

    memcpy(new_data, data, size); 

    size_t index = hash_func(key);
    node_t* node = find_node(&hmap->table[index], match, key);
    if (node != NULL) {
        /* update the hnode */
        hmap_node_t* hnode = (hmap_node_t*)node->data;
        /* Free the old one */
        free(hnode->data);
        /* Assign the new one */
        hnode->data = data;
        
    } else {
        /* Create new hnode */
        hmap_node_t hnode;
        hnode.data = new_data;
        hnode.key = key;
        
        /* Create linkedList node and insert to the appropriate place */
        ll_node = alloc_node(&hnode, sizeof(hmap_node_t));
        if (ll_node == NULL)
            goto mem_error;
        insert_tail(&hmap->table[index], ll_node);
    }

    return 0;

mem_error:
    if (new_data != NULL) {
        free(new_data);
    }
    if (ll_node != NULL) {
        free(ll_node);
    }
    return -1;
}

void* hmap_get(hmap_t* hmap, char* key) {
    assert(hmap != NULL && key != NULL);
    size_t index = hash_func(key);
    node_t* node = find_node(&hmap->table[index], match, key);
    if (node == NULL)
        return NULL;

    hmap_node_t* hnode = node->data;
    return hnode->data;
}

void hmap_remove(hmap_t* hmap, char* key) {
    assert(hmap != NULL && key != NULL);
    size_t index = hash_func(key);
    node_t* node = find_node(&hmap->table[index], match, key);
    if (node == NULL)
        return;
    
    /* Remove node from list */
    remove_node(&hmap->table[index], node);
    hmap_node_t* hnode = node->data;
    free(hnode->data);
    free_node(node);
}

void hmap_destroy(hmap_t* hmap) {
    assert(hmap != NULL);
    for (int i = 0; i < BUCKET_SIZE; i++) {
        free_list(&hmap->table[i]);
    }
}

