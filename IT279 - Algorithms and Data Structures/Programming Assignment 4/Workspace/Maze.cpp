// Implementation of Maze class
// By Mary Elaine Califf and Fernando Payan

#include "Maze.h"
#include "DisjointSet.h"
using namespace std;

Maze::Maze(int rows, int cols)
{
    numRows = rows;
    numColumns = cols;
    int numCells = rows * cols;
    mazeWalls = new CellWalls[numCells];
    mazeWalls[numCells - 1].east = false;
}

Maze &Maze::operator=(const Maze &rhs)
{
    if (this != &rhs)
    {
        delete[] mazeWalls;
        this->copy(rhs);
    }
    return *this;
}

void Maze::generateMaze()
{
    int numCells = numRows * numColumns;
    DisjointSet mySet(numCells);
    bool mazeComplete = false;

    while (!mazeComplete) // Keep iterating through the maze until it is completed
    {
        // Generate a random number in the range 0 to number of cells - 1 for the starting position.
        int position = rand() % numCells;

        // Generate a random number in the range 0-3 representing directions
        int direction = rand() % 4;

        // If the 2nd cell (the neighbor) is invalid because the first cell
        // is at the edge of the maze in that direction, go the opposite direction

        // If we cannot go left, we change direction to go right. Checks if the starting position is on the left side and if the direction is left.
        if (position % numColumns == 0 && direction == 0)
            direction = 2;
        // If we cannot go down, we change direction to go up. Checks if the starting position is in the last row and if the direction is down.
        else if ((position >= (numCells - numColumns) && position <= (numCells - 1)) && direction == 1)
            direction = 3;

        // If we cannot go right, we change direction to go left. Checks if the starting position is in the right side and if the direction is right.
        else if (((position + 1) % numColumns) == 0 && direction == 2)
            direction = 0;

        // If we cannot go up, we change direction to go down. Checks if the starting position is in the first row and if the direction is up.
        else if ((position >= 0 && position <= (numColumns - 1)) && direction == 3)
            direction = 1;

        // Determine whether to knock the wall and if so, which wall to knock down.
        switch (direction)
        {
        case 0: // Left
            if (mySet.find(position) != mySet.find(position - 1))
            {
                // Remove the wall between the position and the cell to it's left (position - 1)
                mazeWalls[position - 1].east = false;

                // Union the two cells together
                mazeComplete = mySet.doUnion(position, position - 1);
            }
            break;

        case 1: // Down
            if ( mySet.find(position) != mySet.find (position + numColumns) )
            {
                // Remove the south wall between the position and the cell below it (position + numColumns) 
                mazeWalls[position].south = false;

                // Union the two cells
                mazeComplete = mySet.doUnion(position, (position + numColumns) );
            }
            break;

        case 2: // Right
            if ( mySet.find(position) != mySet.find (position + 1) )
            {
                // Remove the south wall between the position and the cell above it (position + 1) 
                mazeWalls[position].east = false;

                // Union the two cells
                mazeComplete = mySet.doUnion(position, (position + 1) );
            }
            break;

        case 3: // Up
        if ( mySet.find(position) != mySet.find (position - numColumns) )// is this right? FIXED
            {
                // Remove the south wall between the position and the cell above it (position + numColumns) 
                mazeWalls[position - numColumns].south = false;

                // Union the two cells
                mazeComplete = mySet.doUnion(position, position - numColumns);
            }
            break;
        }
    }
}

void Maze::print(ostream &outputStream)
{
    // print the top row of walls
    for (int i = 0; i < numColumns; i++)
        outputStream << " _";
    outputStream << '\n';
    for (int i = 0; i < numRows; i++)
    {
        int cellbase = i * numColumns;
        // print west wall (except at entrance)
        if (i == 0)
            outputStream << ' ';
        else
            outputStream << '|';
        for (int j = 0; j < numColumns; j++)
        {
            if (mazeWalls[cellbase + j].south)
                outputStream << '_';
            else
                outputStream << ' ';
            if (mazeWalls[cellbase + j].east)
                outputStream << '|';
            else
                outputStream << ' ';
        }
        outputStream << '\n';
    }
}

void Maze::copy(const Maze &orig)
{
    this->numRows = orig.numRows;
    this->numColumns = orig.numColumns;
    int numCells = numRows * numColumns;
    mazeWalls = new CellWalls[numCells];
    for (int i = 0; i < numCells; i++)
    {
        this->mazeWalls[i] = orig.mazeWalls[i];
    }
}
