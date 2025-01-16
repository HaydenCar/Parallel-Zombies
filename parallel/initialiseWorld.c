#include <stdio.h>
#include <stdlib.h>
#include "vars_defs_functions.h"

void initialiseWorld(CELL **current,
                     CELL **future,
                     unsigned long *ptr_to_numS,
                     unsigned long *ptr_to_numZ)
{

  // Parameters used for 'for-loops' and initial location of "patient zero"
  //- the first Zombie. These are unsigned because they are always positive.
  unsigned int i, j, randRow, randCol;

  for (i = 0; i < ROWS; i++)
    for (j = 0; j < COLS; j++)
    {

      // Set state of current cell to S, and increment the number of S.
      // Reminder: We use a char for the state because it is more space-efficient
      // than an int
      current[i][j].state = 'S';
      current[i][j].stateChange = 'N';
      (*ptr_to_numS)++;

      // The following two properties are different for each cell but they don't change
      // once they set at the start of the simulation:

      // Each cell has time as a random number, between MIN_TIME_I_TO_Z and MAX_TIME_I_TO_Z,
      // that it spends as I before becoming Z:
      current[i][j].counter_I_to_Z = rand() % (MAX_TIME_I_TO_Z - MIN_TIME_I_TO_Z + 1) + MIN_TIME_I_TO_Z;

      // Each cell has time as a random number, between MIN_TIME_R_TO_Z and MAX_TIME_R_TO_Z,
      // in the case of an S having been savaged and becoming R, before it becomes a Z:
      current[i][j].counter_R_to_Z = rand() % (MAX_TIME_R_TO_Z - MIN_TIME_R_TO_Z + 1) + MIN_TIME_R_TO_Z;

      // Each cell has set time for it to become empty in the case that it is Dead, D:
      current[i][j].counter_D_to_Empty = TIME_D_TO_EMPTY;

      // Copy all current cells to future cells so that both worlds are identical initially
      future[i][j] = current[i][j];
    }

  // Generate a random integer row and column for the location of "patient zero": the first Zombie
  randRow = rand() % ROWS;
  randCol = rand() % COLS;

  // Set the random cell to be "patient zero", and adjust number of S and Z:
  current[randRow][randCol].state = 'Z';
  future[randRow][randCol] = current[randRow][randCol];
  (*ptr_to_numS)--;
  (*ptr_to_numZ)++;

// Fine grained debug statement: only print if DEBUG_LEVEL > 1
#if DEBUG_LEVEL > 3
  printf("InitialiseWorld: numS = %ld, numZ = %ld\n\n", *ptr_to_numS, *ptr_to_numZ);
#endif
}
