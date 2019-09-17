/*
 mazeio.cpp
 
 Author: Josie Jitzel Alvarez
 
 Short description of this file:
 ensures that the right input
 is recieved to
 create the maze and prints out the maze
 
 */

#include <iostream>
#include "mazeio.hpp"

using namespace std;

/*************************************************
 * read_maze:
 * Read the maze from cin into a dynamically allocated array.
 *
 * Return the pointer to that array.
 * Return NULL (a special address) if there is a problem,
 * such as integers for the size not found.
 *
 * We also pass in two pointers to integers. Fill
 * the integers pointed to by these arguments
 * with the number of rows and columns
 * read (the first two input values).
 *
 *************************************************/
char** read_maze(int* rows, int* cols) {
    cin >> *rows >> *cols;
    
    /*returns NULL if incorrect type is inputted or
     no rows/cols are entered*/
    if ( cin.fail() )
    {
        return NULL;
    }
    
    /*dynamically allocated 2d array for the maze
     initialized to whatever char the user inputs
     so long as it's a: S, F, #, or . */
    char** maze = new char*[*rows];
    
    for (int i =0; i < *rows; i++)
    {
        
        maze[i] = new char [*cols];
        
        for (int k = 0; k < *cols; k++)
        {
            cin >> maze [i][k];
            if ((maze[i][k] != '.'&& maze[i][k] != '#' &&
                 maze[i][k] != 'S'&& maze [i][k] != 'F'))
            {
                return NULL;
            }
        }
        
    }
    
    return maze;
}

/*************************************************
 * Print the maze contents to the screen in the
 * same format as the input (rows and columns, then
 * the maze character grid).
 *************************************************/
void print_maze(char** maze, int rows, int cols) {
    
    cout << rows << " " << cols << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j=0; j < cols; j++)
        {
            cout << maze [i][j];
        }
        cout << endl;
    }
    
}

