#ifndef UTILS_H_
#define UTILS_H_
#include <stdio.h>

// Define debug print
#ifdef DEBUG
#define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif

#endif /*UTILS_H_*/