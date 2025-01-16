#include <stdio.h>
#include "vars_defs_functions.h"

int countZombieNeighbours(int row,
                          int col,
                          CELL **current)
{

  int i, j;

#if DEBUG_LEVEL > 1
  printf("countZombieNeighbours: Cell[%d][%d] is Susceptible:\n", row, col);
#endif

  int local_num_Zombie_Neighbours = 0;

  // Check neighbours of the candidate cell
  for (i = row - 1; i <= row + 1; i++)
    for (j = col - 1; j <= col + 1; j++)
    {

      // Don't include the candidate cell
      if (i != row || j != col)
      {

#if DEBUG_LEVEL > 1
        printf("countZombieNeighbours: Neighbour[%d][%d]\n", (i + ROWS) % ROWS, (j + COLS) % COLS);
#endif

        if (current[(i + ROWS) % ROWS][(j + COLS) % COLS].state == 'Z')
          local_num_Zombie_Neighbours++;
      }
    }

  return local_num_Zombie_Neighbours;
}
