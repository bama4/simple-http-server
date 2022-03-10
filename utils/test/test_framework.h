#ifndef TEST_FRAMEWORK_H_
#define TEST_FRAMEWORK_H_

#include <stdio.h>

#define SUCCESS 0
#define FAIL -1

// Asserts
#define ASSERT(expr)                                                           \
    if (!(expr)) {                                                             \
        printf("ASSERT failed on line %d\n", __LINE__);                        \
        return FAIL;                                                           \
    }

#define ASSERT_FALSE(expr)                                                     \
    if ((expr)) {                                                              \
        printf("ASSERT_FALSE failed on line %d\n", __LINE__);                  \
        return FAIL;                                                           \
    }

#define ASSERT_IS_NULL(var)                                                    \
    if (var != NULL) {                                                         \
        printf("ASSERT_IS_NULL failed on line %d\n", __LINE__);                \
        return FAIL;                                                           \
    }

#define ASSERT_NOT_NULL(var)                                                   \
    if (var == NULL) {                                                         \
        printf("ASSERT_NOT_NULL failed on line %d\n", __LINE__);               \
        return FAIL;                                                           \
    }

#define ASSERT_EQUAL(var1, var2)                                               \
    if (var1 != var2) {                                                        \
        printf("ASSERT_EQUAL failed on line %d\n", __LINE__);                  \
        return FAIL;                                                           \
    }

#define ASSERT_NOT_EQUAL(var1, var2)                                           \
    if (var1 == var2) {                                                        \
        printf("ASSERT_NOT_EQUAL failed on line %d\n", __LINE__);              \
        return FAIL;                                                           \
    }

#define ASSERT_ABOVE_ZERO(var1)                                                \
    if (var1 <= 0) {                                                           \
        printf("ASSERT_ABOVE_ZERO failed on line %d\n", __LINE__);             \
        return FAIL;                                                           \
    }

#endif /*TEST_FRAMEWORK_H_*/
