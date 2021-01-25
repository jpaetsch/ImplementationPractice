// Header file for the single prodcon

#ifndef PRODUCENCONSUME_H
#define PRODUCENCONSUMECON_H

// Includes
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <climits>
#include <string>
#include <pthread.h>
#include <queue>
#include <cstring>
#include <sys/time.h>

// Functions in prodcon.cpp
int to_int(char strCheck[]);
void *producer_thread_function(void *producerThreadID);
void *consumer_thread_function(void *consumerThreadID);

// Functions in tands.cpp
void Trans(int n);
void Sleep(int n);

#endif