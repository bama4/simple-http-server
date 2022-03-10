#ifndef UTILS_H_
#define UTILS_H_
#include <stdio.h>

// Define debug print
#ifdef DEBUG
#define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif

/* The max number of threads for the entire program */
#define MAX_NUM_THREADS 8

typedef struct Program_State {
    int total_num_threads;
} Program_State_t;

/*
  @brief Keeps track of the state of the main thread program
 */
static Program_State_t ProgramState = {0};

#endif /*UTILS_H_*/