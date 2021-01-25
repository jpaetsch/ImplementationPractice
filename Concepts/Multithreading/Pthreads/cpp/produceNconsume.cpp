/*
Adapted from a school assignment - the question was a classic producer-consumer multithreading problem;
In this case it was a single producer thread and a dynamic number of consumer threads.

Program usage:  ./produceNconsume <consumer-thread-number> <optional-logfile-number>

A file can be passed in; see my test.txt / test2.txt as examples of how it should be formatted.
Otherwise, commandline input is read in until ctrl+d indicates end of user input.  'T' indicates work to be
executed by a consumer thread, 'S' indicates the producer should sleep for a certain time; these functions are
contained in Tands.cpp and simulate the passing of time as background computations are executed by the threads.

The program waits for the dynamic number of consumer threads to complete the queue of work and rejoin to end.
Tried to keep synchronization to a minimum within original specifications to keep it efficient and tried
to address potential edge cases, particularly with unexpected input.

The result of the program is a  printing to logfile which may have a given number by way of an optional
commandline argument (either produceNconsume.log or produceNconsume.<#>.log).  This logfile keeps a logical record 
of the threads' states / processes as time passes.  Threads specified by an id > 0 ask for work, receive it, work
on it, complete it, and keep cycling.  The producer thread with id = 0 provides work and sleeps.  In addition, the
actions are timestamped to show interleavings and a Queue limits the amount of work that can be held by the
producer.  Finally, a summary is produced with some timing data as well as a breakdown of how much work
each individual thread accomplished

In my testing, everything seemed to be working as expected/according to original specifications - serves as
a good example of my working knowledge of pthreads, mutexes, and multithreading concepts

Potential improvements for my code include:

1)  More built-in robustness and decomposition into multiple source files
2)  More input error checking
3)  Better handling when threads do not join or create properly
4)  Implementation where the logfile is always in perfect order
5)  Better timing/clock implementation
6)  Create more functions and particularly rethink the implementation of the consumer; very bloated
    and both sections have a lot of repeating code that could be reduced

*/


#include "produceNconsume.h"
using namespace std;

// Global variables declarations

// Shared data queue that will be accessed by all threads
queue<int> sharedQueue;
 // Max buffer size that will be allowed for said queue
long unsigned int MAX_BUFFER_SIZE;
// The following variables are used for error checking as well as exit conditions
int amountWorkReceived = 0;
int amountWorkFinished = 0;
int amountAsks = 0;
int amountReceives = 0;
int amountSleeps = 0;
bool noMore = false;
// File pointer that will eventually be shared by threads (will error check in main to ensure it has a proper value)
FILE *logfilePtr = NULL;
// Shared clocks to return the timing of each thread
struct timeval start, current;

// Mutex Locking and Conditions for Signalling
// Note that the queue mutex critical section is NOT atomic with printing output to the log console
// Therefore there may be some output lines out of order (similar to the example on eclass)
pthread_mutex_t queueMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t clockMutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t workAdded = PTHREAD_COND_INITIALIZER;
pthread_cond_t workRemoved = PTHREAD_COND_INITIALIZER;


// According to the documentation, fprintf is atomic, guaranteed that once the fprintf starts its entire 
// output will be sent before releasing however I wrapped in a mutex anyway to implement the clock timing so 
// that the clock entries are in order in the logfile


// Main (and both thread functions) is getting bloated; with more time (or had the assignment specified) 
// I would decompose into multiple functions or even multiple source files, however it is working at the moment
// and I don't want to break it :)
int main(int argc, char *argv[]) {
    int nthreads;
    int logfileno;
    string fileName;

    // Do value error checking for commandline input
    // Set up number of threads and filename
    if(argc == 3) { // Two arguments should be number of consumer threads and number for log file
        nthreads = to_int(argv[1]);
        fileName = "produceNconsume";
        if(nthreads > 0) {
            logfileno = to_int(argv[2]);
            if(logfileno > 0) {
                fileName += "." + to_string(logfileno) + ".log";
            } else if(logfileno == 0) {
                fileName += ".log";
            } else {
                fprintf(stderr, "Number for log file was not formatted properly\n");
                return(EXIT_FAILURE);
            }
        } else {
            fprintf(stderr, "Number of threads argument was not formatted properly\n");
            return(EXIT_FAILURE);
        }
    } else if(argc == 2) { // The one argument should be number of consumer threads
        nthreads = to_int(argv[1]);
        fileName = "produceNconsume.log";
        if(nthreads <= 0) {
            fprintf(stderr, "Number of threads argument was not formatted properly\n");
            return(EXIT_FAILURE);
        }
    } else if(argc == 1) { // Error as it at least needs number of consumer threads
        fprintf(stderr, "No arguments detected on program startup\n");
        return(EXIT_FAILURE);
    } else { // Error - too many arguments or some other behaviour that should not occur
        fprintf(stderr, "Too many arguments detected on program startup\n");
        return(EXIT_FAILURE);
    }

    // Set the max buffer size that will be used in the queue structure
    MAX_BUFFER_SIZE = 2 * nthreads;

    // Create the global log output file
    logfilePtr = fopen(fileName.c_str(), "w");
    if(logfilePtr == NULL) { // Should never happen; fatal error
        fprintf(stderr, "Unable to open %s file\n", fileName.c_str());
        return(EXIT_FAILURE);
    }

    // Create all the pthreads - producer has id = 0 and consumers have id > 0 [pass these values]
    // Fatal error if a single thread fails to be created
    // Note that I used a new int memory allocation and then delete it in the created threads as I was initially
    // getting concurrency issues (ie. the same threadID was passed as the startup order of threads isn't 
    // guaranteed)...
    // I initially had a bunch of type casting to take care of this problem but I think my current implementation
    // is cleaner
    pthread_t producerThread;
    pthread_t consumerThread[nthreads];

    gettimeofday(&start, NULL); // Start the clock

    int threadID = 0;
    if(pthread_create(&producerThread, NULL, producer_thread_function, new int(threadID))) {
        // Should never happen
        fprintf(stderr, "Error creating producer thread\n");
        return(EXIT_FAILURE);
    } else {
        threadID++;
    }
    for(int i = 0; i < nthreads; ++i) {
        if(pthread_create(&consumerThread[i], NULL, consumer_thread_function, new int(threadID))) {
            // Should never happen
            fprintf(stderr, "Error creating consumer thread %d\n", threadID);
            return(EXIT_FAILURE);
        } else {
            threadID++;
        }
    }

    // Wait for the pthreads to exit by using join before continuing with timing and final cleanup
    // If I have time build safeguards and take action after a join fails?
    threadID = 0;
    if(pthread_join(producerThread, NULL)) { // Should never happen
        fprintf(stderr, "Error with producer thread join (thread close issue)\n");
    } else {
        threadID++;
    }
    // Going to be used to catch thread return values ie. the individual transactions completed
    int transactionsReturn[nthreads] = {0}; 
    for(int i = 0; i < nthreads; ++i) {
        void *returnVal;
        if(pthread_join(consumerThread[i], &returnVal)) { // Should never happen
            fprintf(stderr, "Error with consumer thread %d join (thread close issue)\n", threadID);
        } else {
            transactionsReturn[i] = (intptr_t)returnVal;
            threadID++;
        }
    }

    gettimeofday(&current, NULL); // End the clock to get total time
    float finalTime = (current.tv_sec - start.tv_sec) + (current.tv_usec - start.tv_usec) / 1000000.0f;

    // At this point the work should be done and all children threads closed

    if(amountWorkFinished != amountWorkReceived) { // Should never happen, only checking just in case something went very wrong
        fprintf(stderr, "BIG ERROR: the amount of work consumed (%d) was not the same as the amount of work received (%d)\n", amountWorkFinished, amountWorkReceived);
    }

    fprintf(logfilePtr, "Summary:\n");
    fprintf(logfilePtr, "    Work        %d\n", amountWorkReceived);
    fprintf(logfilePtr, "    Ask         %d\n", amountAsks);
    fprintf(logfilePtr, "    Receive     %d\n", amountReceives);
    fprintf(logfilePtr, "    Complete    %d\n", amountWorkFinished);
    fprintf(logfilePtr, "    Sleep       %d\n", amountSleeps);
    for(int i = 0; i < nthreads; ++i) {
        fprintf(logfilePtr, "    Thread %d    %d\n", (i+1), transactionsReturn[i]);
    }
    fprintf(logfilePtr, "Transactions per second:  %.2f", (amountWorkFinished / finalTime));
    
    // Close the logfile - proper housekeeping
    fclose(logfilePtr);

    return(0);
}


// Function to convert a character array input to integer format
// Performs error checking for our commandline arguments and returns -1 to indicate an issue
int to_int(char strCheck[]) {

    char *ptrEnd;
    int returnInt;
    long testLong;
    errno = 0;

    testLong = strtol(strCheck, &ptrEnd, 10);

    if(strCheck == ptrEnd) {
        if(strCheck[0] == '\0') {
            fprintf(stderr, "String to number conversion error (blank line)\n");
        } else {
            fprintf(stderr, "String to number conversion error (not a number)\n");
        }
        return(-1);
    }
    if(testLong == LONG_MIN && errno == ERANGE) {
        fprintf(stderr, "String to number conversion error (underflow)\n");
        return(-1);
    }
    if(testLong == LONG_MAX && errno == ERANGE) {
        fprintf(stderr, "String to number conversion error (overflow)\n");
        return(-1);
    }
    if((testLong > INT_MAX) || (testLong < INT_MIN)) {
        fprintf(stderr, "String to number conversion error (too big for int conversion)\n");
        return(-1); 
    }
    if(errno != 0 && testLong == 0) {
        fprintf(stderr, "String to number conversion error (unknown)\n");
        return(-1);
    }
    if(errno == 0 && strCheck && *ptrEnd != 0) {
        fprintf(stderr, "String to number conversion error (not a cohesive number)\n");
        return(-1);
    }
    if(testLong < 0) {
        fprintf(stderr, "String to number conversion error (not positive)\n");
        return(-1);
    }

    // After checking ranges it is safe to cast to int
    returnInt = (int) testLong;
    return(returnInt);
}


// Producer Thread Function: 
// 1) Read the standard input until there's no more
// 2) Add to the queue if the read command is T<n> and the queue isn't full (otherwise wait)
// 3) Sleep if the read command is T<n>
// 4) Notify when the last of the input has been added to the queue
void *producer_thread_function(void *arg) {
    // Retrieve the passed producer thread id integer (should be 0)
    // and delete to avoid memory leak
    int producerThreadID = *(int*)arg;
    delete (int*)arg;

    // fprintf(logfilePtr, "Producer with id passed = %d\n", producerThreadID);

    string producerInput;
    char commandLetter;
    int n;
    int Q;

    // Keep track of timing
    float timeStamp;

    while(getline(cin, producerInput)) {
                
        // Assuming that the input is all good so not doing any error checking,
        // just stripping first character and using input after as the integer,
        // if I have more time I will check if n = -1 (indicates int conversion error) 
        // and add checks for unknown command letter... but will trust the input for now
        commandLetter = producerInput[0];
        producerInput.erase(0, 1);
        char *num = new char[producerInput.length() + 1];
        strcpy(num, producerInput.c_str());
        n = to_int(num);
        delete [] num;

        // Producer sleeps if S is read and pushes work (conditionally) if T is read
        if(commandLetter == 'S') {
            
            // Print clock and status of sleeping
            pthread_mutex_lock(&clockMutex);
            gettimeofday(&current, NULL);
            timeStamp = (current.tv_sec - start.tv_sec) + (current.tv_usec - start.tv_usec) / 1000000.0f;
            fprintf(logfilePtr, "%.3f ID= %d      Sleep         %d\n", timeStamp, producerThreadID, n); // LOGFILE
            pthread_mutex_unlock(&clockMutex);

            amountSleeps++;
            Sleep(n);
        } else if( commandLetter == 'T') {
            amountWorkReceived++;

            pthread_mutex_lock(&queueMutex); // Lock the queue
            if(!(sharedQueue.size() < MAX_BUFFER_SIZE)) { // The queue is full
                // Wait until a consumer signals that work has been removed
                pthread_cond_wait(&workRemoved, &queueMutex);
            }
            sharedQueue.push(n);
            Q = sharedQueue.size();
            
            // Signal that work was added in case any consumers were waiting on the empty queue
            pthread_cond_signal(&workAdded);
            pthread_mutex_unlock(&queueMutex); // Unlock the queue

            // Print clock and status of adding work
            pthread_mutex_lock(&clockMutex);
            gettimeofday(&current, NULL);
            timeStamp = (current.tv_sec - start.tv_sec) + (current.tv_usec - start.tv_usec) / 1000000.0f;
            fprintf(logfilePtr, "%.3f ID= %d Q= %d Work          %d\n", timeStamp, producerThreadID, Q, n); // LOGFILE
            pthread_mutex_unlock(&clockMutex);
        }
    }

    noMore = true; // Set global variable that tells consumers no more data is coming

    // Print clock and status of ending
    pthread_mutex_lock(&clockMutex);
    gettimeofday(&current, NULL);
    timeStamp = (current.tv_sec - start.tv_sec) + (current.tv_usec - start.tv_usec) / 1000000.0f;
    fprintf(logfilePtr, "%.3f ID= %d      End\n", timeStamp, producerThreadID); // LOGFILE
    pthread_mutex_unlock(&clockMutex);

    pthread_mutex_lock(&queueMutex);
    // Wake up all the conditionally waiting pthreads to kick them into the second state
    // I believe this needs to be locked to make sure no consumer is in the middle of the critical 
    // section, becoming conditionally waiting for more work forever
    pthread_cond_broadcast(&workAdded); 
    pthread_mutex_unlock(&queueMutex);
    // Producer exits (to be caught by pthread join)
    pthread_exit(NULL);
}


// Consumer Threads Function:
// 1) Check the queue to see if there's work to be done
// 2) Do the work (otherwise wait until producer indicates work is added)
// 3) If producer signals there is no more, go into final cleanup loop to make sure everything in the queue is consumed
void *consumer_thread_function(void *arg) {
    // Retrieve the passed consumer thread id integer (should be > 0)
    // and delete to avoid memory leak
    int consumerThreadID = *(int*)arg;
    delete (int*)arg;

    // fprintf(logfilePtr, "Consumer with id passed = %d\n", consumerThreadID);
    bool askForWork = true;
    int queueData = -1;
    int Q;

    int personalTransactions = 0;

    // Keeping timing of each thread status update
    float timeStamp;

    // While the producer indicates it is still receiving data, stay in the first state
    while(noMore == false) {
        queueData = -1;

        if(askForWork) {
            // Print clock and status of asking for work
            pthread_mutex_lock(&clockMutex);
            gettimeofday(&current, NULL);
            timeStamp = (current.tv_sec - start.tv_sec) + (current.tv_usec - start.tv_usec) / 1000000.0f;
            fprintf(logfilePtr, "%.3f ID= %d      Ask\n", timeStamp, consumerThreadID); // LOGFILE
            pthread_mutex_unlock(&clockMutex);

            amountAsks++;
            askForWork = false;
        }

        pthread_mutex_lock(&queueMutex); // Lock the queue
        if(sharedQueue.size() > 0) { // If the queue isn't empty
            queueData = sharedQueue.front();
            sharedQueue.pop();
            Q = sharedQueue.size(); // Transactions received and waiting to be consumed
            // Signal that work was removed in case the producer is waiting on the full queue
            pthread_cond_signal(&workRemoved);
        } else { // If the queue is empty
            // Wait until the producer signals that work has been added
            pthread_cond_wait(&workAdded, &queueMutex);
        }
        pthread_mutex_unlock(&queueMutex); // Unlock the queue

        // Process and 'work on' the retrieved data if it was received, remembering to enable this consumer
        // to print the ask for work message again
        if(queueData != -1) {
            // Print clock and status of receiving work
            pthread_mutex_lock(&clockMutex);
            gettimeofday(&current, NULL);
            timeStamp = (current.tv_sec - start.tv_sec) + (current.tv_usec - start.tv_usec) / 1000000.0f;
            fprintf(logfilePtr, "%.3f ID= %d Q= %d Receive       %d\n", timeStamp, consumerThreadID, Q, queueData); // LOGFILE
            pthread_mutex_unlock(&clockMutex);
            
            amountReceives++;
            Trans(queueData);
            personalTransactions++;

            // Print clock and status of completing work
            pthread_mutex_lock(&clockMutex);
            gettimeofday(&current, NULL);
            timeStamp = (current.tv_sec - start.tv_sec) + (current.tv_usec - start.tv_usec) / 1000000.0f;
            fprintf(logfilePtr, "%.3f ID= %d      Complete      %d\n", timeStamp, consumerThreadID, queueData); //LOGFILE
            pthread_mutex_unlock(&clockMutex);

            amountWorkFinished++;
            askForWork = true;
        }
    }

    // At this point the producer is not adding more work; just need to make sure all work is consumed
    // At the very most the threads need to run through the size of the buffer to ensure everything is gone
    // I initially had this as a while(true) loop but was concerned that then if even one consumer thread got caught
    // in an infinite loop everything would hang... this way it runs through the most times that will ever be necessary
    // and guarantees it will re-join although there is definitely a more elegant solution out there
    for(long unsigned int i = 0; i < MAX_BUFFER_SIZE; ++i) {
        int finalData = -1;

        if(askForWork) {
            // Print clock and status of asking for work
            pthread_mutex_lock(&clockMutex);
            gettimeofday(&current, NULL);
            timeStamp = (current.tv_sec - start.tv_sec) + (current.tv_usec - start.tv_usec) / 1000000.0f;
            fprintf(logfilePtr, "%.3f ID= %d      Ask\n", timeStamp, consumerThreadID); // LOGFILE
            pthread_mutex_unlock(&clockMutex);

            amountAsks++;
            askForWork = false;
        }

        pthread_mutex_lock(&queueMutex);
        if(sharedQueue.size() != 0) {
            finalData = sharedQueue.front();
            sharedQueue.pop();
            Q = sharedQueue.size();
        }
        pthread_mutex_unlock(&queueMutex);

        if(finalData != -1) { // If data was received, work on it
            // Print clock and status of receiving work
            pthread_mutex_lock(&clockMutex);
            gettimeofday(&current, NULL);
            timeStamp = (current.tv_sec - start.tv_sec) + (current.tv_usec - start.tv_usec) / 1000000.0f;
            fprintf(logfilePtr, "%.3f ID= %d Q= %d Receive       %d\n", timeStamp, consumerThreadID, Q, finalData); // LOGFILE
            pthread_mutex_unlock(&clockMutex);

            amountReceives++;
            Trans(finalData);
            personalTransactions++;
            
            // Print clock and status of completing work
            pthread_mutex_lock(&clockMutex);
            gettimeofday(&current, NULL);
            timeStamp = (current.tv_sec - start.tv_sec) + (current.tv_usec - start.tv_usec) / 1000000.0f;
            fprintf(logfilePtr, "%.3f ID= %d      Complete      %d\n", timeStamp, consumerThreadID, finalData); //LOGFILE
            pthread_mutex_unlock(&clockMutex);

            amountWorkFinished++;
            askForWork = true;
        } else { // Otherwise there is nothing left; return value of this thread's contribution
            return (void *) (intptr_t)personalTransactions;
        }
    }
    // If it runs through the maximum number of times; return value of this thread's contribution
    return (void *) (intptr_t)personalTransactions;

}