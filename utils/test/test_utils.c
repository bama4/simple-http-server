#include "test_framework.h"

int main() {
    int result = SUCCESS;
    printf("Running tests for utils library\n");

    result &= test_vector();

    return result;
}
