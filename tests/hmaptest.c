#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <hmap.h> // Assuming hmap.h is in the same directory

// A simple structure to test with custom data types
typedef struct {
    int id;
    char name[50];
} custom_data_t;

// Function prototypes for test cases
void test_hmap_put_get();
void test_hmap_remove();
void test_hmap_collision();

int main() {
    test_hmap_put_get();
    test_hmap_remove();
    test_hmap_collision();
    return 0;
}

void test_hmap_put_get() {
    printf("Running test_hmap_put_get...\n");

    hmap_t hmap;
    memset(&hmap, 0, sizeof(hmap));

    // Insert and retrieve basic data
    char *key1 = "key1";
    int value1 = 42;

    if (hmap_put(&hmap, key1, &value1, sizeof(value1)) != 0) {
        printf("[FAIL] Failed to insert key1\n");
        return;
    }

    int *retrieved_value = (int *)hmap_get(&hmap, key1);
    if (retrieved_value && *retrieved_value == value1) {
        printf("[PASS] Retrieved value matches inserted value\n");
    } else {
        printf("[FAIL] Retrieved value does not match inserted value\n");
    }

    hmap_destroy(&hmap);
}

void test_hmap_remove() {
    printf("Running test_hmap_remove...\n");

    hmap_t hmap;
    memset(&hmap, 0, sizeof(hmap));

    char *key1 = "key1";
    int value1 = 42;

    hmap_put(&hmap, key1, &value1, sizeof(value1));

    hmap_remove(&hmap, key1);
    if (hmap_get(&hmap, key1) == NULL) {
        printf("[PASS] Successfully deleted key1\n");
    } else {
        printf("[FAIL] Failed to delete key1\n");
    }
    hmap_destroy(&hmap);

}

void test_hmap_collision() {
    printf("Running test_hmap_collision...\n");

    hmap_t hmap;
    memset(&hmap, 0, sizeof(hmap));

    // Using keys that are likely to collide based on hash function (e.g., same hash mod bucket size)
    char *key1 = "key1";
    char *key2 = "key2";
    int value1 = 42;
    int value2 = 99;

    hmap_put(&hmap, key1, &value1, sizeof(value1));
    hmap_put(&hmap, key2, &value2, sizeof(value2));

    int *retrieved_value1 = (int *)hmap_get(&hmap, key1);
    int *retrieved_value2 = (int *)hmap_get(&hmap, key2);

    if (retrieved_value1 && *retrieved_value1 == value1) {
        printf("[PASS] Retrieved value for key1 matches inserted value\n");
    } else {
        printf("[FAIL] Retrieved value for key1 does not match inserted value\n");
    }

    if (retrieved_value2 && *retrieved_value2 == value2) {
        printf("[PASS] Retrieved value for key2 matches inserted value\n");
    } else {
        printf("[FAIL] Retrieved value for key2 does not match inserted value\n");
    }
    hmap_destroy(&hmap);
}
