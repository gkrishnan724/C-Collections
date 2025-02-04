#include <stdio.h>
#include <stdlib.h>

#define TESTS_DIR "bin/tests"

// List of test binaries to run
const char *test_binaries[] = {
    "lltest",
    "hmaptest",
    "ring_buftest",
    NULL // Marks the end of the list
};

int main() {
    printf("Running specified tests:\n\n");

    for (int i = 0; test_binaries[i] != NULL; i++) {
        // Construct the full path of the test binary
        char path[512];
        snprintf(path, sizeof(path), "%s/%s", TESTS_DIR, test_binaries[i]);

        printf("Executing: %s\n", path);
        int ret = system(path); // Execute the binary

        if (ret != 0) {
            printf("Error running test!!!!\n\n");
            return EXIT_FAILURE;
        } else {
            printf("Test %s finished with status: %d\n\n", test_binaries[i], WEXITSTATUS(ret));
        }
    }

    printf("All specified tests finished.\n");
    return EXIT_SUCCESS;
}
