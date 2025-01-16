//
// child threads code
// loops through each day with each thread having designated work
// each thread is only allowed to modify resources if no other thread is currently accessing them
//
#include <stdio.h>
#include "vars_defs_functions.h"
#include "pthread.h"

pthread_mutex_t mymutex;
pthread_cond_t cond_var;
int counter = 0;

void *child(void *rank)
{
    long my_rank = (long)rank; /* Use long in case of 64-bit system */
    long long my_n = ROWS / thread_count;
    long long my_first_i = my_n * my_rank;
    long long my_last_i_plus = (my_rank == thread_count - 1) ? ROWS : my_first_i + my_n;

    printf("Running from child thread %ld\n", my_rank);
    int day;
    for (day = 1; day <= TOTAL_DAYS; day++)
    {
        // for early exit incase S = 0 and days are still left
        if (numS == 0)
        {
            pthread_mutex_lock(&mymutex);
            counter++;
            if (counter == thread_count)
            {
                pthread_cond_broadcast(&cond_var);
            }
            pthread_mutex_unlock(&mymutex);
            break;
        }

        // each thread checks the state of each row/col they are assigned and decides
        // what function to call
        for (int row = my_first_i; row < my_last_i_plus; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                switch (current[row][col].state)
                {

                case 'S':
                {
                    int num_Zombie_Neighbours = countZombieNeighbours(row, col, current);
                    pthread_mutex_lock(&mymutex);
                    decide_S_to_ZorR(row, col, num_Zombie_Neighbours, &numS, &numZ, &numR, current, future);
                    if (current[row][col].stateChange == 'N')
                    {
                        decide_S_to_D(row, col, &numS, &numD, current, future);
                    }
                    pthread_mutex_unlock(&mymutex);
                    break;
                }

                case 'Z':
                {
                    int num_Susceptible_Neighbours = countSusceptibleNeighbours(row, col, current);
                    pthread_mutex_lock(&mymutex);
                    if (num_Susceptible_Neighbours >= NUM_S_TO_DEFEAT_Z)
                    {
                        decide_Z_to_D(row, col, num_Susceptible_Neighbours, &numZ, &numD, current, future);
                    }
                    pthread_mutex_unlock(&mymutex);
                    break;
                }

                case 'R':
                {
                    pthread_mutex_lock(&mymutex);
                    decide_R_to_Z(row, col, &numR, &numZ, current, future);
                    pthread_mutex_unlock(&mymutex);
                    break;
                }

                case 'D':
                {
                    pthread_mutex_lock(&mymutex);
                    decide_D_to_Empty(row, col, &numD, current, future);
                    pthread_mutex_unlock(&mymutex);
                    break;
                }
                }
            }
        }

        // Barrier
        pthread_mutex_lock(&mymutex);
        counter++;
        // the last arriving thread copies the future world to current
        if (counter == thread_count)
        {
            counter = 0;
            // Overwrite current with future for changed cells
            for (int i = 0; i < ROWS; i++)
            {
                for (int j = 0; j < COLS; j++)
                {
                    if (current[i][j].stateChange == 'Y')
                    {
                        current[i][j] = future[i][j];
                    }
                }
            }

            outputDaySZRD(fp_daySZRD, day, numS, numZ, numR, numD);
            pthread_cond_broadcast(&cond_var);
        }
        else
        {
            while (pthread_cond_wait(&cond_var, &mymutex) != 0)
                ;
        }
        pthread_mutex_unlock(&mymutex);

        // printf("Day %d finished running from child thread %ld\n", day, my_rank);
    }

    outputDaySZRD(fp_daySZRD, day, numS, numZ, numR, numD);

    return NULL;
}