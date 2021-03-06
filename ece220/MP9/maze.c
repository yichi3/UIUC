#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/*
  Introduction Paragraph
  In this file, I write four functions.
      First one is called createMaze, which can first read values of rows and columns
      from input file and the maze board from the file. Then, the function will initialize
      the maze->cells.

      Second function is called destroyMaze, which is used to free spaces for maze that
      created from previous function. This is necessary because we need to prevent memory leak
      when we create a dynamic variable.

      Third function is called printMaze, which can print the game board and therefore tell the
      user the correct path to win the maze.

      Last function is the heart of this file. It is called solveMazeManhattanDFS. This function
      will do recursion to get the correct path to win the maze. In my algorithm, I will first check
      left paths and then right, up and down.
*/

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    FILE * mfile;                     // open a file to read the content in maze(123).txt
    maze_t * maze = (maze_t *)malloc(sizeof(maze_t));     // allocate space for maze
    mfile = fopen(fileName, "r");
    char junk;                   // store the newline of each line in txt file
    fscanf(mfile, "%d%d%c", &maze->width, &maze->height, &junk);   // read width, height from file
    maze->cells = (char **)malloc(sizeof(char *) * maze->height);    // allocate space for every row of cells
    int i, j;                                             // row and column counters
    for (i = 0; i < maze->height; i++)
        maze->cells[i] = (char *)malloc(sizeof(char) * maze->width);   // allocate space for each cell in row
    for (i = 0; i < maze->height; i++){
        for (j = 0; j < maze->width; j++){
            fscanf(mfile, "%c", &maze->cells[i][j]);                          // geet character from file
            if (maze->cells[i][j] == START){                           // check START and END
                maze->startColumn = j;                                 // initialize position for START and END
                maze->startRow = i;
            }
            if (maze->cells[i][j] == END){
                maze->endColumn = j;
                maze->endRow = i;
            }
        }
        fscanf(mfile, "%c", &junk);                     // get rid of the newlice character at the end of each row
    }
    fclose(mfile);
    return maze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
    int i;
    for (i = 0; i < maze->height; i++)          // first free each row in the cells
        free(maze->cells[i]);
    free(maze->cells);                          // then free the rows of the cells
    free(maze);                                 // at last, free the maze
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    int i, j;
    for (i = 0; i < maze->height; i++){
        for (j = 0; j < maze->width; j++){
            printf("%c", maze->cells[i][j]);
        }
        printf("\n");
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */
int solveMazeManhattanDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
    // first, we need to write the base case
    int m_row = maze->height;
    int m_col = maze->width;
    int endRow = maze->endRow;
    int endColumn = maze->endColumn;
    if ((row == endRow && col == endColumn + 1)||
        (row == endRow && col == endColumn - 1)||
        (col == endColumn && row == endRow + 1)||
        (col == endColumn && row == endRow - 1))
        return 1;
    // second, we need to do recursion function
    // first do left step
    if (col > 1 && maze->cells[row][col - 1] == EMPTY){             // if empty, go to this spot
        maze->cells[row][col - 1] = PATH;                           // set new step
        if(solveMazeManhattanDFS(maze, col - 1, row) == 1)
            return 1;
        maze->cells[row][col - 1] = VISITED;                        // do backtrack
    }
    // right
    if (col < m_col - 1 && maze->cells[row][col + 1] == EMPTY){
        maze->cells[row][col + 1] = PATH;
        if(solveMazeManhattanDFS(maze, col + 1, row) == 1)
            return 1;
        maze->cells[row][col + 1] = VISITED;
    }
    // up
    if (row > 1 && maze->cells[row - 1][col] == EMPTY){
        maze->cells[row - 1][col] = PATH;
        if(solveMazeManhattanDFS(maze, col, row - 1) == 1)
            return 1;
        maze->cells[row - 1][col] = VISITED;
    }
    // down
    if (row < m_row && maze->cells[row + 1][col] == EMPTY){
        maze->cells[row + 1][col] = PATH;
        if(solveMazeManhattanDFS(maze, col, row + 1) == 1)
            return 1;
        maze->cells[row + 1][col] = VISITED;
    }
    return 0;
}
