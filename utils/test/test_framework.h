#ifndef
#define TEST_FRAMEWORK_H_

#define SUCCESS 0
#define FAIL -1
#define ASSERT(expr) if(!(expr)) return FAIL
#define ASSERT_IS_NONE(var) if(var != NULL) return FAIL

#endif /*TEST_FRAMEWORK_H_*/
