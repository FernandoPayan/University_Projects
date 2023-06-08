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
        int startPos = rand() % numCells;

        // Generate a random number in the range 0-3 representing directions
        int direction = rand() % 4;

        // If the 2nd cell (the neighbor) is invalid because the first cell
        // is at the edge of the maze in that direction, go the opposite direction

        // If we cannot go left, we change direction to go right. Checks if the starting position is on the left side and if the direction is left.
        if (startPos % numColumns == 0 && direction == 0)
        {
            cout << "Direction " << direction << " is not valid for " << startPos << ". Changing direction to right " << endl;
            direction = 2;
        }
        // If we cannot go down, we change direction to go up. Checks if the starting position is in the last row and if the direction is down.
        else if ((startPos >= (numCells - numColumns) && startPos <= (numCells - 1)) && direction == 1)
        {
            cout << "Direction " << direction << " is not valid for " << startPos << ". Changing direction to up " << endl;
            direction = 3;
        }

        // If we cannot go right, we change direction to go left. Checks if the starting position is in the right side and if the direction is right.
        else if (((startPos + 1) % numColumns) == 0 && direction == 2)
        {
            cout << "Direction " << direction << " is not valid for " << startPos << ". Changing direction to left " << endl;
            direction = 0;
        }

        // If we cannot go up, we change direction to go down. Checks if the starting position is in the first row and if the direction is up.
        else if ((startPos >= 0 && startPos <= (numColumns - 1)) && direction == 3)
        {
            cout << "Direction " << direction << " is not valid for " << startPos << ". Changing direction to down " << endl;
            direction = 1;
        }

        // Neighbor is valid, so we compute the number for the second cell given the valid direction.
        cout << "Direction is " << direction << endl;

        // Determine whether to knock the wall and if so, which wall to knock down.
        switch (direction)
        {
        case 0: // Left
        cout << " Case 0 for " << startPos << endl;
            if (mySet.find(startPos) != mySet.find(startPos - 1))
            {
                cout << "Removing " << (startPos + 1) << "'s east wall. The cell to the right of it is " << startPos << endl;

                // Remove the wall between the startPos and the cell to it's left (startPos - 1)
                mazeWalls[startPos - 1].east = false;

                // Union the two cells together
                mazeComplete = mySet.doUnion(startPos, startPos - 1);
            }
            //cout << "The number left of " << startPos << " is: " << (startPos - 1) << endl;
            break;
        case 1: // Down
        cout << " Case 1 for " << startPos << endl;
        cout << "Value below is " << startPos + numColumns << endl;
        cout << "Working for the cell below: " << mySet.find(startPos + numColumns) << endl;
        cout << "Does find work for startPos? " << mySet.find(startPos) << endl; // THIS IS WHERE IT IS CRASHING
        
            if ( mySet.find(startPos) != mySet.find (startPos + numColumns) )
            {
                cout << "Removing " << startPos << "'s south wall. The cell below it is " << startPos + numColumns << endl;

                // Remove the south wall between the startPos and the cell below it (startPos + numColumns) 
                mazeWalls[startPos].south = false;

                // Union the two cells
                mazeComplete = mySet.doUnion(startPos, (startPos + numColumns) );
            }

            //cout << "The number below " << startPos << " is: " << (startPos + numColumns) << endl;
            break;
        case 2: // Right
        cout << " Case 2 for " << startPos << endl;
            if ( mySet.find(startPos) != mySet.find (startPos + 1) )
            {
                cout << "Removing " << startPos << "'s east wall. The cell to the right of it is " << (startPos + 1) << endl;

                // Remove the south wall between the startPos and the cell above it (startPos + 1) 
                mazeWalls[startPos].east = false;

                // Union the two cells
                mazeComplete = mySet.doUnion(startPos, (startPos + 1) );
            }

            //cout << "The number right of " << startPos << " is: " << (startPos + 1) << endl;
            break;
        case 3: // Up
        cout << " Case 3 for " << startPos << endl;
        if ( mySet.find(startPos) != mySet.find (startPos - numColumns) )// is this right? FIXED
            {
                cout << "Removing the wall above " << startPos << ", which is " << (startPos - numColumns) << "'s south wall" << endl;

                // Remove the south wall between the startPos and the cell above it (startPos + numColumns) 
                mazeWalls[startPos - numColumns].south = false;

                // Union the two cells
                mazeComplete = mySet.doUnion(startPos, startPos - numColumns);
            }
            //cout << "The number above " << startPos << " is: " << (startPos - numColumns) << endl;
            break;
        default:
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