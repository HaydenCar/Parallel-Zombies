#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vars_defs_functions.h"
#include "timer.h"
#include "pthread.h"

// The quantity of S, Z, R, D could be large numbers: make them long ints
unsigned long numS = 0;
unsigned long numZ = 0;
unsigned long numR = 0;
unsigned long numD = 0;

// Avoid possibility of stack overflow by dynamically declaring memory for the
// current and future worlds. We need to 'free' this memory at the end of main()
CELL **current;
CELL **future;

// File handle for daySZRD.dat
FILE *fp_daySZRD;

// Neighours
int num_Zombie_Neighbours = 0, num_Susceptible_Neighbours = 0;

long thread;
pthread_mutex_t mymutex;
pthread_cond_t cond_var;

int main()
{
    pthread_t *thread_handles;
    pthread_mutex_init(&mymutex, NULL);
    pthread_cond_init(&cond_var, NULL);
    thread_handles = malloc(thread_count * sizeof(pthread_t));

    double start, finish, elapsed;

    GET_TIME(start);

    int day = 0; // Current day
    int i = 0;   // Variables for for-loops

    current = (CELL **)malloc(ROWS * sizeof(CELL *));
    future = (CELL **)malloc(ROWS * sizeof(CELL *));

    for (i = 0; i < ROWS; i++)
    {
        current[i] = (CELL *)malloc(COLS * sizeof(CELL));
        future[i] = (CELL *)malloc(COLS * sizeof(CELL));
        if (current[i] == NULL || future[i] == NULL)
        {
            printf("Memory allocation failed at row %d\n", i);
            return 1; // TRYING TO FIND WHY ROWS AND COLS IS NOT WHAT I DEFINED
        }
    }

    // Open daySZRD.dat for writing. We will need to close it at the end of main()
    fp_daySZRD = fopen("data/daySZRD.dat", "w");

    // Generate random seed so that we get different random numbers
    // each time the program is run
    srand((unsigned int)time(NULL));

    initialiseWorld(current, future, &numS, &numZ);

    // Output numerical data to a single file
    outputDaySZRD(fp_daySZRD, day, numS, numZ, numR, numD);

    // In this function, we create a separate file for each day,
    // indexed by the day. Then, we write the 2-dim world to that file.
    // outputWorld(day, current);

// We can control the level of printing to the console, using the
// DEBUG_LEVEL macro definition (defined in vars_defs_functions.h)
// Note how we always name the function running the printf() statement
#if DEBUG_LEVEL > 1
    printf("main: numS = %ld, numI = %ld\n\n", numS, numI);
#endif

    ///////////////////////////////////////////////////////////////////////////////
    // DAY LOOP
    //////////////////////////////////////////////////////////////////////////////

    printf("ROWS: %d, COLS: %d\n", ROWS, COLS);
    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_create(&thread_handles[thread], NULL, &child, (void *)thread);
    }

    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_join(thread_handles[thread], NULL);
    }

    ///////////////////////////////////////////////////////////////////////////////
    // END OF DAY LOOP
    //////////////////////////////////////////////////////////////////////////////

    // Destroy mutex lock
    pthread_mutex_destroy(&mymutex);
    pthread_cond_destroy(&cond_var);
    // Close our daySZRD.dat file
    fclose(fp_daySZRD);

    // Free memory which was allocated with malloc()
    free(current);
    free(future);

    // Calculate the duration of our program and output to console
    GET_TIME(finish);
    elapsed = finish - start;
    printf("main: Time taken = %lf seconds\n", elapsed);

    return 0;
}
