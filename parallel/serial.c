#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vars_defs_functions.h"
#include "timer.h"


int main(){

  double start, finish, elapsed;

  GET_TIME(start);

  //The quantity of S, Z, R, D could be large numbers: make them long ints
  unsigned long numS = 0;
  unsigned long numZ = 0;
  unsigned long numR = 0;
  unsigned long numD = 0;

  
  int day = 0; //Current day
  int i, j, row, col; //Variables for for-loops
  int num_Zombie_Neighbours, num_Susceptible_Neighbours;
  
  //Avoid possibility of stack overflow by dynamically declaring memory for the
  //current and future worlds. We need to 'free' this memory at the end of main()
  CELL **current;
  CELL **future;
 
  current = (CELL**)malloc(ROWS*sizeof(CELL*));
  future = (CELL**)malloc(ROWS*sizeof(CELL*));
  
  for(i=0; i<ROWS; i++){
    current[i] = (CELL*)malloc(COLS*sizeof(CELL));
    future[i] = (CELL*)malloc(COLS*sizeof(CELL));
  }

  //File handle for daySZRD.dat
  FILE *fp_daySZRD;

  //Open daySZRD.dat for writing. We will need to close it at the end of main()
  fp_daySZRD = fopen("data/daySZRD.dat", "w");

  //Generate random seed so that we get different random numbers
  //each time the program is run
  srand((unsigned int)time(NULL));
  
  initialiseWorld(current, future, &numS, &numZ);

  //Output numerical data to a single file
  outputDaySZRD(fp_daySZRD, day, numS, numZ, numR, numD);

  //In this function, we create a separate file for each day,
  //indexed by the day. Then, we write the 2-dim world to that file.
  outputWorld(day, current);

  //We can control the level of printing to the console, using the
  //DEBUG_LEVEL macro definition (defined in vars_defs_functions.h)
  //Note how we always name the function running the printf() statement
  #if DEBUG_LEVEL > 1
  printf("main: numS = %ld, numI = %ld\n\n", numS, numI);
  #endif


  ///////////////////////////////////////////////////////////////////////////////
  // DAY LOOP
  //////////////////////////////////////////////////////////////////////////////

  for(day=1; day <= TOTAL_DAYS; day++){

    for(row=0; row<ROWS; row++)
      for(col=0; col<COLS; col++){

	//Check the State of the candidate cell, and act accordingly
	switch(current[row][col].state){

	case 'S':
	  num_Zombie_Neighbours = countZombieNeighbours(row, col, current);

	  #if DEBUG_LEVEL > 1
	  printf("main: Cell[%d][%d]: ", row, col);
	  printf("main: Num of Zombie Neighbours = %d\n", num_Zombie_Neighbours);
	  #endif

	  decide_S_to_ZorR(row, col, num_Zombie_Neighbours,	\
			   &numS, &numZ, &numR,			\
			   current, future);
	  

	  //If Susceptible wasn't bitten in decide_S_to_ZorR()
	  // => could possibly die naturally instead
	  if(current[row][col].stateChange == 'N'){

	    #if DEBUG_LEVEL > 1
	    printf("main: Susceptible wasn't bitten");
	    #endif
	    
	    decide_S_to_D(row, col, &numS, &numD, current, future);
	  }
	  
	  break;

	  
	case 'Z':
 	  #if DEBUG_LEVEL > 1
	  printf("main: Cell[%d][%d] is Zombie\n", row, col);
	  #endif

	  //A Zombie might be defeated provided there are sufficient
	  //number of Susceptible neighbours to do so, and then based
	  //on a defined probability
	  num_Susceptible_Neighbours = countSusceptibleNeighbours(row, col, current);

	  #if DEBUG_LEVEL > 1
	  printf("main: Cell[%d][%d]: ", row, col);
	  printf("main: Num of Susceptible Neighbours = %d\n", num_Susceptible_Neighbours);
	  #endif
	  
	  if(num_Susceptible_Neighbours >= NUM_S_TO_DEFEAT_Z)
	    decide_Z_to_D(row, col, num_Susceptible_Neighbours,	\
			  &numZ, &numD,				\
			  current, future);

	  break;

	  
	case 'R':
	  #if DEBUG_LEVEL > 1
	  printf("main: Cell[%d][%d] is Removed\n", row, col);
	  #endif

	  decide_R_to_Z(row, col, &numR, &numZ, current, future);
	  break;

	  
	case 'D':
	  #if DEBUG_LEVEL > 1
	  printf("main: Cell[%d][%d] is Dead\n", row, col);
	  #endif
    
	  decide_D_to_Empty(row, col, &numD, current, future);
	  break;
	  
	}
      }
    
	
    //Overwrite the current with the future, but only
    //overwrite the cells that have changed for efficiency
    for(i=0; i<ROWS; i++)
      for(j=0; j<COLS; j++)
	if(current[i][j].stateChange == 'Y')
	  current[i][j] = future[i][j];

    //Output numerical data to the daySZRD.dat file for the
    //day just completed.
    outputDaySZRD(fp_daySZRD, day, numS, numZ, numR, numD);

    //To save disk space, we can control how often world is
    //output to a file. Useful if the world is large.
    if(day%WORLD_OUTPUT_INTERVAL == 0)
      outputWorld(day, current);
    
  }
  ///////////////////////////////////////////////////////////////////////////////
  // END OF DAY LOOP
  //////////////////////////////////////////////////////////////////////////////

  //Close our daySZRD.dat file
  fclose(fp_daySZRD);

  //Free memory which was allocated with malloc()
  free(current);
  free(future);

  //Calculate the duration of our program and output to console
  GET_TIME(finish);
  elapsed = finish - start;
  printf("main: Time taken = %lf seconds\n", elapsed);
  
  return 0;
}
