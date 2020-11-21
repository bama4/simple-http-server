#ifndef TEST_FRAMEWORK_H_
#define TEST_FRAMEWORK_H_

#include <stdio.h>

#define SUCCESS 0
#define FAIL -1

#ifdef TEST_NO_PRINT_

#define ASSERT(expr)                                                           \
    if (!(expr))                                                               \
        return FAIL;

#define ASSERT_IS_NONE(var)                                                    \
    if (var != NULL)                                                           \
        return FAIL;

#else /*TEST_NO_PRINT*/

#define ASSERT(expr)                                                           \
    if (!(expr)) {                                                             \
        printf("Assert failed on line %d\n", __LINE__);                        \
        return FAIL;                                                           \
    }

#define ASSERT_IS_NONE(var)                                                    \
    if (var != NULL) {                                                         \
        printf("Assert failed on line %d\n", __LINE__);                        \
        return FAIL;                                                           \
    }

#endif /*TEST_NO_PRINT*/

#endif /*TEST_FRAMEWORK_H_*/
