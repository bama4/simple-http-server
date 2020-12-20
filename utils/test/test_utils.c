#include "test_framework.h"

extern int test_linked_list();
extern int test_queue();
extern int test_vector();

int main() {
    // Run all utils tests
    int result = SUCCESS;

    printf("Running tests for utils library\n");

    // Run all linked list tests
    result &= test_linked_list();

    // Run all queue tests
    result &= test_queue();

    // Run all vector tests
    result &= test_vector();
    result &= test_hashmap();

    return result;
}
