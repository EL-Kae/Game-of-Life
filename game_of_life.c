/* Project Hw1 by Leonardo Kaestner CS3393
   This C program simulates John Conway's game of life. This program
   will take in an input file and simulate the game based on this file.
   I created a 2D array in the heap that is suppose to represent the world. 
   This world will copy the input file. Afterwards I created another 
   temporary world in the heap and copy the actual world into it. A for
   loop will iterate through the temp world and count up all its neighbors. 
   Changes are done in the actual world not int the temp world. Likewise 
   counting is done in the temp world not the actual world. This is done to 
   produce accurate results because changing the values in the array while also 
   counting its neighbors would alter the results.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 

//Global Variables
long ROWS;
long COLUMNS;
long GENERATIONS;

//Forward Declarations
void destroy_world(int ** arr);
void print_world(int ** arr, int age);

//Goes row by row and frees up memory
void destroy_world(int ** arr)
{
  for(int index = 0; index < ROWS; index++)
    {
      free(arr[index]);
    }
  free(arr);
}

//Prints the world
void print_world(int ** arr, int age)
{
  printf("Generation %d:", age);
  for(int index = 0; index < ROWS; index++)
    {
      for(int jndex = 0; jndex < COLUMNS; jndex++)
	{
	  if(arr[index][jndex] == 1)
	    printf("*");
	  else if(arr[index][jndex] == 0)
	    printf(" ");
	}
      printf("\n");
    }
  printf("================================\n");
}

int main(int argc, char* argv[])
{
  FILE *firstGenFile;
  const char *filename;
  char cell;
  int currentAge = 0;
  
  //Reads in the second argument and sets it to ROWS.
  if(argc > 1)
    {
      char *arg1;
      ROWS = strtol(argv[1], &arg1, 10);
      ROWS += 2;
    }
  else
    {
      ROWS = 12;
    }
  
  //Reads in the third argument and sets it to COLUMNS.
  if(argc > 2)
    {
      char *arg2;
      COLUMNS = strtol(argv[2], &arg2, 10);
      COLUMNS += 2;
    }
  else
    {
      COLUMNS = 12;
    }

  //Reads in the fourth argument and sets it to filename.
  if(argc > 3)
    {
      filename = argv[3];
    }
  else
    {
      filename = "life.txt";
    }
  
  //Reads in the fifth argument and sets it to GENERATIONS.
  if(argc > 4)
    {
      char *arg4;
      GENERATIONS = strtol(argv[4], &arg4, 10);
    }
  else
    {
      GENERATIONS = 10;
    }
 
  //Opens file and checks if there is a file.
  firstGenFile = fopen(filename, "r");
  if(firstGenFile == NULL)
    {
      printf("File not found\n");
      exit(1);
    }
  
  //creates the two by two array or world in the heap.
  int ** world = (int **) malloc(sizeof(int *)*ROWS);
  for(int index = 0; index < ROWS; index++)
    {
      world[index] = (int *)malloc(COLUMNS * sizeof(int));
    }
  
  //makes the world empty :'(
  for(int index = 0; index < ROWS; index++)
    {
      for(int jndex = 0; jndex < COLUMNS; jndex++)
	{
	  world[index][jndex] = 0;
	}
    }
  
  int fileHeight = 0;
  int fileLength = 0;
  int fileLengthTemp = 0;
  
  //adds 1's or 0's to the 2D array based on the incoming text file.
  //Also checks if the user's args for rows and columns are big enough.
  int rowIndex = 1;
  int colIndex = 1;
  while((cell = fgetc(firstGenFile)) != EOF)
    {
      if(cell == '\n')
	{
	  rowIndex++;
	  colIndex = 1;
	  fileHeight++;
	  
	  if(fileLength < fileLengthTemp)
	    {
	      fileLength = fileLengthTemp;
	    }
	  
	  fileLengthTemp = 0;
	  
	}

      else if(cell != ' ')
	{
	  world[rowIndex][colIndex] = 1;
	  colIndex++;
	  fileLengthTemp++;
	}
      
      else if(cell == ' ')
	{
	  world[rowIndex][colIndex] = 0;
	  colIndex++;
	  fileLengthTemp++;
	}
    }
  
  fileHeight++;
  
  if(ROWS < fileHeight)
    {
      printf(
      "The number of rows you indicated is too small for this file.\n");
      exit(1);
    }
  else if(COLUMNS < fileLength)
    {
      printf(
      "The number of columns you indicated is too small for this file.\n");
      exit(1);
    }
  
  //Prints the initial world.
  print_world(world,currentAge);

  //Closes the file.
  fclose(firstGenFile);
  
  //Creates a copy of the 2D array already in the heap.
  int ** tempWorld = (int **) malloc(sizeof(int *)*ROWS);
  for(int index = 0; index < ROWS; index++)
    {
      tempWorld[index] = (int *)malloc(COLUMNS * sizeof(int));
    }
  
  for(currentAge = 1; currentAge <= GENERATIONS; currentAge++)
    {
  
      for(int index = 0; index < ROWS; index++)
	{
	  for(int jndex = 0; jndex < COLUMNS; jndex++)
	    {
	      tempWorld[index][jndex] = world[index][jndex];
	    }
	}
 
      //Counts the number of neighbors each cell has.
      int numOfNeighbors = 0;
      for(int index = 1; index < ROWS - 1; index++)
	{
	  for(int jndex = 1; jndex < COLUMNS - 1; jndex++)
	    {
	      numOfNeighbors = 0;
	      numOfNeighbors = tempWorld[index-1][jndex-1] +
		               tempWorld[index-1][jndex] +
		               tempWorld[index-1][jndex+1] +
		               tempWorld[index][jndex+1] +
		               tempWorld[index+1][jndex+1] +
		               tempWorld[index+1][jndex] +
		               tempWorld[index+1][jndex-1] +
		               tempWorld[index][jndex-1];
	      
	      //Applies the four basic rules of Conway's Game of life.
	      if(tempWorld[index][jndex] == 1 && numOfNeighbors < 2) 
		{
		  world[index][jndex] = 0;
		}
	 
	      if(tempWorld[index][jndex] == 1 && (numOfNeighbors == 2 
	      || numOfNeighbors == 3))
		{
		  world[index][jndex] = 1;
		}

	      if(tempWorld[index][jndex] == 1 && numOfNeighbors > 3) 
		{
		  world[index][jndex] = 0;
		}
	 
	      if(tempWorld[index][jndex] == 0 && numOfNeighbors == 3)
		{
		  world[index][jndex] = 1;
		}
	    }
	}

      //Print the new world.
      print_world(world,currentAge);
    }

  //Destroys both worlds.
  destroy_world(tempWorld);
  destroy_world(world);
  
  return 0;
}
