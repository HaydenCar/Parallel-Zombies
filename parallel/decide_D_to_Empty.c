//
// This function decides when a Dead cell becomes empty. This is based on a countdown variable.
// When the variables reaches zero, make the cell empty. If the counter isn't at
// zero, we decrement it.
//
#include <stdio.h>
#include <stdlib.h>
#include "vars_defs_functions.h"

void decide_D_to_Empty(int row,
                       int col,
                       unsigned long *ptr_to_numD,
                       CELL **current,
                       CELL **future)
{

  if (current[row][col].counter_D_to_Empty == 0)
  {

    // Change state to blank:
    future[row][col].state = ' ';

    current[row][col].stateChange = 'Y';

#if DEBUG_LEVEL > 1
    printf("decide_D_to_Empty: Cell marked as empty\n\n");
#endif

    (*ptr_to_numD)--;
  }
  else
  {
    // Decrement D->Empty counter in the CURRENT world because this cell won't be overwritten
    //  because stateChange remains as 'N'
    (current[row][col].counter_D_to_Empty)--;

#if DEBUG_LEVEL > 1
    printf("decide_D_to_Empty: State stays as R\n\n");
#endif
  }
}
