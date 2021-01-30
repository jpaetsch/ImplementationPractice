#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include "IO.h"
#include "timer.h"
#include "math.h"

void *thread_matrix_multiply(void* rank);
void free_allocated_memory();

#endif