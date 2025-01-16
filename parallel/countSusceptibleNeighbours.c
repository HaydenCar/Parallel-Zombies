//
//This function counts the number of Susceptible neighbours that a Zombie
//could have. This number will be used to decide: Z -> D
//
#include <stdio.h>
#include "vars_defs_functions.h"


int countSusceptibleNeighbours(int row,
			       int col,
			       CELL **current){

  int i, j;

  #if DEBUG_LEVEL > 1
  printf("countSusceptibleNeighbours: Cell[%d][%d] is Zombie:\n", row, col);
  #endif
  
  int local_num_Susceptible_Neighbours = 0;
  
  //Check neighbours of the candidate cell
  for(i=row-1; i<=row+1; i++)
    for(j=col-1; j<=col+1; j++){
      
      //Don't include the candidate cell
      if(i != row || j != col){

        #if DEBUG_LEVEL > 1
	printf("countSusceptibleNeighbours: Neighbour[%d][%d]\n",(i+ROWS)%ROWS, (j+COLS)%COLS);
	#endif
	
	if(current[(i+ROWS)%ROWS][(j+COLS)%COLS].state == 'S')
	  local_num_Susceptible_Neighbours++;
	
	}
    }

  return local_num_Susceptible_Neighbours;

}
  
