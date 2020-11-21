#ifndef TEST_FRAMEWORK_H_
#define TEST_FRAMEWORK_H_

#define SUCCESS 0

#ifdef TEST_NO_LINES_

#define ASSERT(expr)                                                           \
    if (!(expr))                                                               \
        return -1;

#define ASSERT_IS_NONE(var)                                                    \
    if (var != NULL)                                                           \
        return -1;

#else /*TEST_NO_LINES_*/

#define ASSERT(expr)                                                           \
    if (!(expr))                                                               \
        return __LINE__;

#define ASSERT_IS_NONE(var)                                                    \
    if (var != NULL)                                                           \
        return __LINE__;

#endif /*TEST_NO_LINES_*/

#endif /*TEST_FRAMEWORK_H_*/
