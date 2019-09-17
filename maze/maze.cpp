/*
 maze.cpp
 
 Author: Josie Jitzel Alvarez
 
 Short description of this file:
 
 -Performs BFS
 -Prints out shortest path in maze
 --prints out error messages if:
 *there is an invalid maze
 *no path found
 
 */

#include <iostream>
#include "mazeio.hpp"
#include "queue.hpp"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);
//Prototypes for my functions:

//Checks if location has already been visited
bool isVisited(bool** visited, Location location);
/*Following Functions check if NWSE neighbor
 locations are valid (not out of bounds)*/
bool isNorthValid (int row);
bool isWestValid (int col);
bool isSouthValid (int row, int max_row);
bool isEastValid (int col, int max_col);
/*Backtracks from finish location and marks shortest path
 until it reaches the start location*/
void backtrack (Location** pred, char** maze,
                Location current, Location start);


// main function to read, solve maze, and print result
int main() {
    int rows, cols, result;
    char** mymaze;
    
    mymaze = read_maze(&rows, &cols);
    
    if (mymaze == NULL) {
        cout << "Error, input format incorrect" << endl;
        return 1;
    }
    
    
    result = maze_search (mymaze, rows, cols);
    
    
    // examine value returned by maze_search and print appropriate output
    if (result == 1) { // path found!
        print_maze(mymaze, rows, cols);
    }
    else if (result == 0) { // no path :(
        cout << "No path could be found!" << endl;
    }
    else { // result == -1
        cout << "Invalid maze." << endl;
    }
    
    // ADD CODE HERE to delete all memory
    // that read_maze allocated
    
    
    for (int i = 0; i < rows; i++)
    {
        delete [] mymaze [i];
    }
    delete []  mymaze;
    
    return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if invalid maze (not exactly one S and one F)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 *************************************************/
int maze_search(char** maze, int rows, int cols) {
    
    Queue q (rows*cols); //object for Queue class
    
    int s =0;  //start counter
    int f = 0; //finish counter
    int start_locR = -1;
    int start_locC = -1;
    int fin_locR = -1;
    int fin_locC = -1;
    
    //finds start and finish locations & how many of them there are
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (maze [i][j] == 'S')
            {
                s++;
                start_locR= i;
                start_locC = j;
                
            }
            else if (maze [i][j] == 'F')
            {
                f++;
                fin_locR = i;
                fin_locC = j;
            }
        }
    }
    
    if ( s!= 1 || f != 1)
    {
        return -1;
    }
    
    Location start_loc;
    
    start_loc.row = start_locR;
    start_loc.col = start_locC;
    
    q.add_to_back(start_loc);
    
    //2d array for visited initalized to false
    bool** visited = new bool*[rows];
    for(int i = 0; i < rows; i++)
    {
        visited [i] = new bool[cols];
        
        for (int j=0; j < cols; j++)
        {
            visited [i][j] = false;
        }
    }
    
    //predecessor 2d array
    Location** predecessor = new Location*[rows];
    for (int p = 0; p < rows; p++)
    {
        predecessor[p] = new Location [cols];
    }
    
    while (q.is_empty() == false)
    {
        Location curr = q.remove_from_front();
        
        //starts running backtrack function once final location is reached
        if(curr.row == fin_locR && curr.col == fin_locC)
        {
            backtrack (predecessor, maze, curr, start_loc);
            
            //delete the visited array
            for (int i = 0; i < rows; i++)
            {
                delete [] visited [i];
            }
            delete []  visited;
            
            //delete the predecessor array
            for (int i = 0; i < rows; i++)
            {
                delete [] predecessor [i];
            }
            delete []  predecessor;
            
            return 1;
            
        }
        
        if (isNorthValid( curr.row-1) == true)
        {
            Location north_loc;
            north_loc.row = curr.row-1;
            north_loc.col = curr.col;
            
            /* updates predecessor & visited array if North neighbor
             isn't a wall & hasn't been visited yet */
            if (maze[north_loc.row][north_loc.col] != '#' &&
                !(isVisited (visited, north_loc)) )
            {
                predecessor[north_loc.row][north_loc.col] = curr;
                visited [north_loc.row][north_loc.col] = true;
                
                q.add_to_back(north_loc);
            }
        }
        
        //same as above, but for West neighbor
        if (isWestValid(curr.col-1) == true)
        {
            Location west_loc;
            west_loc.row = curr.row;
            west_loc.col = curr.col-1;
            
            if (maze[west_loc.row][west_loc.col] != '#' &&
                !(isVisited (visited, west_loc)) )
            {
                
                predecessor [west_loc.row][west_loc.col] = curr;
                visited [west_loc.row][west_loc.col] = true;
                
                q.add_to_back(west_loc);
            }
        }
        
        //same as above, but for South neighbor
        if (isSouthValid((curr.row+1), rows) == true)
        {
            Location south_loc;
            south_loc.row = curr.row+1;
            south_loc.col = curr.col;
            
            if (maze[south_loc.row][south_loc.col] != '#' &&
                !(isVisited (visited, south_loc)) )
            {
                
                predecessor [south_loc.row][south_loc.col] = curr;
                visited [south_loc.row][south_loc.col] = true;
                
                q.add_to_back(south_loc);
            }
        }
        
        //same as above, but for East neighbor
        if (isEastValid( (curr.col+1), cols) == true)
        {
            Location east_loc;
            east_loc.row = curr.row;
            east_loc.col = curr.col+1;
            
            if (maze[east_loc.row][east_loc.col] != '#' &&
                !(isVisited (visited, east_loc)) )
            {
                
                predecessor [east_loc.row][east_loc.col] = curr;
                visited [east_loc.row][east_loc.col] = true;
                
                q.add_to_back(east_loc);
            }
        }
        
    }
    
    return 0;
}

bool isVisited(bool** visited, Location location)
{
    return visited[location.row][location.col];
}

bool isNorthValid (int row)
{
    return (row >=0);
}
bool isWestValid (int col)
{
    return (col >= 0);
}
bool isSouthValid (int row, int max_row)
{
    return (row < max_row);
}
bool isEastValid (int col, int max_col)
{
    return (col < max_col);
}
void backtrack (Location** pred, char** maze,
                Location current, Location start)
{
    /*initializes the previous location to be the predecessor
     of the finish cell*/
    Location previous_loc = pred[current.row][current.col];
    
    while (!(previous_loc.row == start.row &&
             previous_loc.col == start.col) )
    {
        maze [previous_loc.row][previous_loc.col] = '*';
        previous_loc = pred [previous_loc.row][previous_loc.col];
        
    }
    
}
