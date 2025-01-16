//
// This function decides whether a Zombie gets defeated by Susceptibles.
// This is based on there being a defined minimum number Susceptible neighbours
// of a Zombie. This number is defined in our vars_defs_functions.h header file
//

#include <stdio.h>
#include <stdlib.h>
#include "vars_defs_functions.h"

void decide_Z_to_D(int row,
                   int col,
                   int num_Susceptible_Neighbours,
                   unsigned long *ptr_to_numZ,
                   unsigned long *ptr_to_numD,
                   CELL **current,
                   CELL **future)
{

  float chance;

  // Generate a random "chance" between 0.0 and 1.0
  chance = (float)rand() / (float)RAND_MAX;

#if DEBUG_LEVEL > 1
  printf("decide_Z_to_D: chance = %f\n", chance);
#endif

  if (chance <= PROB_Z_TO_D)
  {
    // Change state to D:
    future[row][col].state = 'D';

    current[row][col].stateChange = 'Y';

#if DEBUG_LEVEL > 1
    printf("decide_Z_to_D: Z -> D\n\n");
#endif

    (*ptr_to_numD)++;
    (*ptr_to_numZ)--;
  }
}
