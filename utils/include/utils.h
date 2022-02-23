#ifndef UTILS_H_
#define UTILS_H_
#include <stdio.h>

// Define debug print
#define DEBUG_PRINT(msg)
#ifdef DEBUG
#define DEBUG_PRINT(msg, ...) printf(msg)
#endif

#endif /*UTILS_H_*/