//
// This function makes the decision as to whether a Susceptible is bitten and
// then changes it into a Zombie or Removed. This is based on the number of Zombie
// neighbours:
//  If there are 1 - 5 Zombie neighbours, do S -> Z with defined probability
//  If there are 6 or more Zombie neighbours, do S -> R, with defined probability
//
#include <stdio.h>
#include <stdlib.h>
#include "vars_defs_functions.h"

void decide_S_to_ZorR(int row,
                      int col,
                      int num_Zombie_Neighbours,
                      unsigned long *ptr_to_numS,
                      unsigned long *ptr_to_numZ,
                      unsigned long *ptr_to_numR,
                      CELL **current,
                      CELL **future)
{

        float chance;

        switch (num_Zombie_Neighbours)
        {

        case 0:
                // No Zombie neighbours => do nothing!

#if DEBUG_LEVEL > 1
                printf("decide_S_to_ZorR: State stays as S\n\n");
#endif

                break;

        case 1:
                // Generate a random "chance" between 0.0 and 1.0
                chance = (float)rand() / (float)RAND_MAX;

#if DEBUG_LEVEL > 1
                printf("decide_S_to_ZorR: chance = %f\n", chance);
                printf("decide_S_to_ZorR: PROB_S_TO_Z_1 = %f\n", PROB_S_TO_Z_1);
#endif

                if (chance <= PROB_S_TO_ZorR_1)
                {
                        // Cell will change state. Either:
                        //   S -> Z or S -> R

                        if (num_Zombie_Neighbours < MIN_NUM_ZOMBIE_TO_SAVAGE_S)
                        {
                                // num_Zombie_Neighbours is BELOW minimum needed
                                // to savage a Susceptible. So, here: S -> Z

                                future[row][col].state = 'Z';

#if DEBUG_LEVEL > 1
                                printf("decide_S_to_ZorR: S -> Z\n\n");
#endif

                                // Increase numZ, decrease numS
                                (*ptr_to_numZ)++;
                                (*ptr_to_numS)--;
                        }
                        else
                        {
                                // num_Zombie_Neighbours is at or above minimum
                                // needed to savage a Susceptible. In this case,
                                // it will be considered to be savaged, and:
                                //   S -> R instead of S -> Z.

                                future[row][col].state = 'R';

#if DEBUG_LEVEL > 1
                                printf("decide_S_to_ZorR: S -> R\n\n");
#endif

                                // Increase numR, decrease numS
                                (*ptr_to_numR)++;
                                (*ptr_to_numS)--;
                        }
                        // Mark Cell has having changed State
                        current[row][col].stateChange = 'Y';
                }
                else
                {
#if DEBUG_LEVEL > 1
                        printf("decide_S_to_ZorR: State stays as S\n\n");
#endif
                }

                break;

        case 2:
                // Generate a random "chance" between 0.0 and 1.0
                chance = (float)rand() / (float)RAND_MAX;

#if DEBUG_LEVEL > 1
                printf("decide_S_to_ZorR: chance = %f\n", chance);
                printf("decide_S_to_ZorR: PROB_S_TO_Z_2 = %f\n", PROB_S_TO_Z_2);
#endif

                if (chance <= PROB_S_TO_ZorR_2)
                {
                        // Cell will change state. Either:
                        // S -> Z or S -> R

                        if (num_Zombie_Neighbours < MIN_NUM_ZOMBIE_TO_SAVAGE_S)
                        {
                                // num_Zombie_Neighbours is BELOW minimum needed
                                // to savage a Susceptible. So, here: S -> Z

                                future[row][col].state = 'Z';

#if DEBUG_LEVEL > 1
                                printf("decide_S_to_ZorR: S -> Z\n\n");
#endif

                                // Increase numZ, decrease numS
                                (*ptr_to_numZ)++;
                                (*ptr_to_numS)--;
                        }
                        else
                        {
                                // num_Zombie_Neighbours is at or above minimum
                                // needed to savage a Susceptible. In this case,
                                // it will be considered to be savaged, and:
                                //   S -> R instead of S -> Z.

                                future[row][col].state = 'R';

#if DEBUG_LEVEL > 1
                                printf("decide_S_to_ZorR: S -> R\n\n");
#endif

                                // Increase numR, decrease numS
                                (*ptr_to_numR)++;
                                (*ptr_to_numS)--;
                        }
                        // Mark Cell has having changed State
                        current[row][col].stateChange = 'Y';
                }
                else
                {
#if DEBUG_LEVEL > 1
                        printf("decide_S_to_ZorR: State stays as S\n\n");
#endif
                }

                break;

        case 3:

                // Generate a random "chance" between 0.0 and 1.0
                chance = (float)rand() / (float)RAND_MAX;

#if DEBUG_LEVEL > 1
                printf("decide_S_to_ZorR: chance = %f\n", chance);
                printf("decide_S_to_ZorR: PROB_S_TO_Z_3 = %f\n", PROB_S_TO_Z_3);
#endif

                if (chance <= PROB_S_TO_ZorR_3)
                {
                        // Cell will change state. Either:
                        // S -> Z or S -> R

                        if (num_Zombie_Neighbours < MIN_NUM_ZOMBIE_TO_SAVAGE_S)
                        {
                                // num_Zombie_Neighbours is BELOW minimum needed
                                // to savage a Susceptible. So, here: S -> Z

                                future[row][col].state = 'Z';

#if DEBUG_LEVEL > 1
                                printf("decide_S_to_ZorR: S -> Z\n\n");
#endif

                                // Increase numZ, decrease numS
                                (*ptr_to_numZ)++;
                                (*ptr_to_numS)--;
                        }
                        else
                        {
                                // num_Zombie_Neighbours is at or above minimum
                                // needed to savage a Susceptible. In this case,
                                // it will be considered to be savaged, and:
                                //   S -> R instead of S -> Z.

                                future[row][col].state = 'R';

#if DEBUG_LEVEL > 1
                                printf("decide_S_to_ZorR: S -> R\n\n");
#endif

                                // Increase numR, decrease numS
                                (*ptr_to_numR)++;
                                (*ptr_to_numS)--;
                        }
                        // Mark Cell has having changed State
                        current[row][col].stateChange = 'Y';
                }
                else
                {
#if DEBUG_LEVEL > 1
                        printf("decide_S_to_ZorR: State stays as S\n\n");
#endif
                }

                break;

        case 4:
                // Generate a random "chance" between 0.0 and 1.0
                chance = (float)rand() / (float)RAND_MAX;

#if DEBUG_LEVEL > 1
                printf("decide_S_to_ZorR: chance = %f\n", chance);
                printf("decide_S_to_ZorR: PROB_S_TO_Z_4 = %f\n", PROB_S_TO_Z_4);
#endif

                if (chance <= PROB_S_TO_ZorR_4)
                {
                        // Cell will change state. Either:
                        // S -> Z or S -> R

                        if (num_Zombie_Neighbours < MIN_NUM_ZOMBIE_TO_SAVAGE_S)
                        {
                                // num_Zombie_Neighbours is BELOW minimum needed
                                // to savage a Susceptible. So, here: S -> Z

                                future[row][col].state = 'Z';

#if DEBUG_LEVEL > 1
                                printf("decide_S_to_ZorR: S -> Z\n\n");
#endif

                                // Increase numZ, decrease numS
                                (*ptr_to_numZ)++;
                                (*ptr_to_numS)--;
                        }
                        else
                        {
                                // num_Zombie_Neighbours is at or above minimum
                                // needed to savage a Susceptible. In this case,
                                // it will be considered to be savaged, and:
                                //   S -> R instead of S -> Z.

                                future[row][col].state = 'R';

#if DEBUG_LEVEL > 1
                                printf("decide_S_to_ZorR: S -> R\n\n");
#endif

                                // Increase numR, decrease numS
                                (*ptr_to_numR)++;
                                (*ptr_to_numS)--;
                        }
                        // Mark Cell has having changed State
                        current[row][col].stateChange = 'Y';
                }
                else
                {
#if DEBUG_LEVEL > 1
                        printf("decide_S_to_ZorR: State stays as S\n\n");
#endif
                }

                break;

        case 5:
                // Generate a random "chance" between 0.0 and 1.0
                chance = (float)rand() / (float)RAND_MAX;

#if DEBUG_LEVEL > 1
                printf("decide_S_to_ZorR: chance = %f\n", chance);
                printf("decide_S_to_ZorR: PROB_S_TO_Z_5 = %f\n", PROB_S_TO_Z_5);
#endif

                if (chance <= PROB_S_TO_ZorR_5)
                {
                        // Cell will change state. Either:
                        // S -> Z or S -> R

                        if (num_Zombie_Neighbours < MIN_NUM_ZOMBIE_TO_SAVAGE_S)
                        {
                                // num_Zombie_Neighbours is BELOW minimum needed
                                // to savage a Susceptible. So, here: S -> Z

                                future[row][col].state = 'Z';

#if DEBUG_LEVEL > 1
                                printf("decide_S_to_ZorR: S -> Z\n\n");
#endif

                                // Increase numZ, decrease numS
                                (*ptr_to_numZ)++;
                                (*ptr_to_numS)--;
                        }
                        else
                        {
                                // num_Zombie_Neighbours is at or above minimum
                                // needed to savage a Susceptible. In this case,
                                // it will be considered to be savaged, and:
                                //   S -> R instead of S -> Z.

                                future[row][col].state = 'R';

#if DEBUG_LEVEL > 1
                                printf("decide_S_to_ZorR: S -> R\n\n");
#endif

                                // Increase numR, decrease numS
                                (*ptr_to_numR)++;
                                (*ptr_to_numS)--;
                        }
                        // Mark Cell has having changed State
                        current[row][col].stateChange = 'Y';
                }
                else
                {
#if DEBUG_LEVEL > 1
                        printf("decide_S_to_ZorR: State stays as S\n\n");
#endif
                }

                break;

        case 6:
                // Generate a random "chance" between 0.0 and 1.0
                chance = (float)rand() / (float)RAND_MAX;

#if DEBUG_LEVEL > 1
                printf("decide_S_to_ZorR: chance = %f\n", chance);
                printf("decide_S_to_ZorR: PROB_S_TO_Z_6 = %f\n", PROB_S_TO_Z_6);
#endif

                if (chance <= PROB_S_TO_ZorR_6)
                {
                        // Cell will change state. Either:
                        // S -> Z or S -> R

                        if (num_Zombie_Neighbours < MIN_NUM_ZOMBIE_TO_SAVAGE_S)
                        {
                                // num_Zombie_Neighbours is BELOW minimum needed
                                // to savage a Susceptible. So, here: S -> Z

                                future[row][col].state = 'Z';

#if DEBUG_LEVEL > 1
                                printf("decide_S_to_ZorR: S -> Z\n\n");
#endif

                                // Increase numZ, decrease numS
                                (*ptr_to_numZ)++;
                                (*ptr_to_numS)--;
                        }
                        else
                        {
                                // num_Zombie_Neighbours is at or above minimum
                                // needed to savage a Susceptible. In this case,
                                // it will be considered to be savaged, and:
                                //   S -> R instead of S -> Z.

                                future[row][col].state = 'R';

#if DEBUG_LEVEL > 1
                                printf("decide_S_to_ZorR: S -> R\n\n");
#endif

                                // Increase numR, decrease numS
                                (*ptr_to_numR)++;
                                (*ptr_to_numS)--;
                        }
                        // Mark Cell has having changed State
                        current[row][col].stateChange = 'Y';
                }
                else
                {
#if DEBUG_LEVEL > 1
                        printf("decide_S_to_ZorR: State stays as S\n\n");
#endif
                }

                break;

        case 7:
                // Generate a random "chance" between 0.0 and 1.0
                chance = (float)rand() / (float)RAND_MAX;

#if DEBUG_LEVEL > 1
                printf("decide_S_to_ZorR: chance = %f\n", chance);
                printf("decide_S_to_ZorR: PROB_S_TO_Z_7 = %f\n", PROB_S_TO_Z_7);
#endif

                if (chance <= PROB_S_TO_ZorR_7)
                {
                        // Cell will change state. Either:
                        // S -> Z or S -> R

                        if (num_Zombie_Neighbours < MIN_NUM_ZOMBIE_TO_SAVAGE_S)
                        {
                                // num_Zombie_Neighbours is BELOW minimum needed
                                // to savage a Susceptible. So, here: S -> Z

                                future[row][col].state = 'Z';

#if DEBUG_LEVEL > 1
                                printf("decide_S_to_ZorR: S -> Z\n\n");
#endif

                                // Increase numZ, decrease numS
                                (*ptr_to_numZ)++;
                                (*ptr_to_numS)--;
                        }
                        else
                        {
                                // num_Zombie_Neighbours is at or above minimum
                                // needed to savage a Susceptible. In this case,
                                // it will be considered to be savaged, and:
                                //   S -> R instead of S -> Z.

                                future[row][col].state = 'R';

#if DEBUG_LEVEL > 1
                                printf("decide_S_to_ZorR: S -> R\n\n");
#endif

                                // Increase numR, decrease numS
                                (*ptr_to_numR)++;
                                (*ptr_to_numS)--;
                        }
                        // Mark Cell has having changed State
                        current[row][col].stateChange = 'Y';
                }
                else
                {
#if DEBUG_LEVEL > 1
                        printf("decide_S_to_ZorR: State stays as S\n\n");
#endif
                }

                break;

        case 8:
                // Generate a random "chance" between 0.0 and 1.0
                chance = (float)rand() / (float)RAND_MAX;

#if DEBUG_LEVEL > 1
                printf("decide_S_to_ZorR: chance = %f\n", chance);
                printf("decide_S_to_ZorR: PROB_S_TO_Z_8 = %f\n", PROB_S_TO_Z_8);
#endif

                if (chance <= PROB_S_TO_ZorR_8)
                {
                        // Cell will change state. Either:
                        // S -> Z or S -> R

                        if (num_Zombie_Neighbours < MIN_NUM_ZOMBIE_TO_SAVAGE_S)
                        {
                                // num_Zombie_Neighbours is BELOW minimum needed
                                // to savage a Susceptible. So, here: S -> Z

                                future[row][col].state = 'Z';

#if DEBUG_LEVEL > 1
                                printf("decide_S_to_ZorR: S -> Z\n\n");
#endif

                                // Increase numZ, decrease numS
                                (*ptr_to_numZ)++;
                                (*ptr_to_numS)--;
                        }
                        else
                        {
                                // num_Zombie_Neighbours is at or above minimum
                                // needed to savage a Susceptible. In this case,
                                // it will be considered to be savaged, and:
                                //   S -> R instead of S -> Z.

                                future[row][col].state = 'R';

#if DEBUG_LEVEL > 1
                                printf("decide_S_to_ZorR: S -> R\n\n");
#endif

                                // Increase numR, decrease numS
                                (*ptr_to_numR)++;
                                (*ptr_to_numS)--;
                        }
                        // Mark Cell has having changed State
                        current[row][col].stateChange = 'Y';
                }
                else
                {
#if DEBUG_LEVEL > 1
                        printf("decide_S_to_ZorR: State stays as S\n\n");
#endif
                }

                break;
        }
}
