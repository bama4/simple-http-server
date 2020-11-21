#ifndef TEST_FRAMEWORK_H_
#define TEST_FRAMEWORK_H_

#define SUCCESS 0
#define FAIL -1

#define ASSERT(expr)                                                           \
    if (!(expr))                                                               \
        return __LINE__;

#define ASSERT_IS_NONE(var)                                                    \
    if (var != NULL)                                                           \
        return __LINE__;

#endif /*TEST_FRAMEWORK_H_*/
