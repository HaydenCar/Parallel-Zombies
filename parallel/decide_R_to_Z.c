//
// This function decides if R -> Z. This is based on a countdown variable.
// When the variables reaches zero, we do R -> Z. If the counter isn't at
// zero, we decrement it.
//
#include <stdio.h>
#include <stdlib.h>
#include "vars_defs_functions.h"

void decide_R_to_Z(int row,
                   int col,
                   unsigned long *ptr_to_numR,
                   unsigned long *ptr_to_numZ,
                   CELL **current,
                   CELL **future)
{

  if (current[row][col].counter_R_to_Z == 0)
  {

    // Change state back to Z:
    future[row][col].state = 'Z';

    current[row][col].stateChange = 'Y';

#if DEBUG_LEVEL > 1
    printf("decide_R_to_Z: R -> Z\n\n");
#endif

    (*ptr_to_numZ)++;
    (*ptr_to_numR)--;
  }
  else
  {
    // Decrement R->Z counter in the CURRENT world because this cell won't be overwritten
    //  because stateChange remains as 'N'
    (current[row][col].counter_R_to_Z)--;

#if DEBUG_LEVEL > 1
    printf("decide_R_to_Z: State stays as R\n\n");
#endif
  }
}
