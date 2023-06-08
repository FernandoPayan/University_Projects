// Graph implementation file
// By Fernando Payan

#include "Graph.h"
#include "DisjointSet.h"
#include <sstream>
#include <algorithm>
#include <queue>
#include <stack>
Graph::Graph()
{
    // Set variables to default values
    matrixSize = 0;
    int numEdges = 0;
}

/**
    @param input - The input file's name
    @return True if successful; false if the input file could not be opened
*/
bool Graph::readGraph(string input)
{
    // Creates the ifstream object using the param as the name for the file
    inputFile.open(input);

    if (inputFile.is_open())
    {
        // Stores the contents of the line
        string word;

        // Saves the name of the file
        fileName = input;

        // Clears the contents of the following vectors
        adjacencyMatrix.clear();
        vertices.clear();

        // Read the first line, which stores the number of vertices
        inputFile >> matrixSize;

        // Add all of the vertices and store them into our vertices vector
        for (int i = 0; i < matrixSize; i++)
        {
            // Get the next word in the file
            inputFile >> word;

            // Add the word to the end of the vector
            vertices.push_back(word);

            // Create the adjacency matrix size
            adjacencyMatrix.push_back(vector<int>(matrixSize, 0));
        }

        // Get the number of edges we will be working with
        inputFile >> numEdges;

        // Add the edges + their weights to the matrix
        for (int j = 0; j < numEdges; j++)
        {
            // Get the next word in the file and get the row # that the vertex is at
            inputFile >> word;
            int row = distance(vertices.begin(), find(vertices.begin(), vertices.end(), word));

            // Get the next word in the file and get the column # that the airport is at
            inputFile >> word;
            int column = distance(vertices.begin(), find(vertices.begin(), vertices.end(), word));

            // Get the next word in the file and get the weight of the edge
            int weight = 0;
            inputFile >> weight;

            // Add the weight to the adjacency matrix
            adjacencyMatrix[row][column] = weight;
        }

        // Close the input file
        inputFile.close();

        // Unable to find the file; return false.
        return true;
    }
    return false;
}

void Graph::printGraph()
{
    // String for each line in the file
    string line;

    for (int i = 0; i < adjacencyMatrix.size(); i++)
    {
        for (int j = 0; j < adjacencyMatrix.size(); j++)
        {
            if (adjacencyMatrix[i][j] >= 0)
            {
                cout << "| " << adjacencyMatrix[i][j];
            }
        }
        cout << "\n";
    }
}

void Graph::computeTopologicalSort()
{
    // An array of in-degrees for each vertex
    int inDegreeArray[matrixSize];

    // Holds vertex indicies. Keeps track of what we can put into the list
    queue<int> theQueue;

    // Vector that holds ordering of our values
    vector<int> ordering;

    // Set up the in-degree array from the graph
    for (int i = 0; i < matrixSize; i++)
    {
        // Keeps track of the in degree for a vertex
        int inDegree = 0;

        // Iterates through each row to calculate the in degree
        for (int j = 0; j < matrixSize; j++)
            if (adjacencyMatrix[j][i] > 0)
                inDegree++;

        inDegreeArray[i] = inDegree;
    }

    // Add any vertices with in-degree zero to the queue
    for (int j = 0; j < matrixSize; j++)
    {
        if (inDegreeArray[j] == 0)
            theQueue.push(j);
    }

    // Checks if a topological sort is possible
    if (!theQueue.empty())
    {
        cout << "Topological Sort:\n";

        // While the queue is not empty
        while (!theQueue.empty())
        {
            // Remove first vertex
            int curVertex = theQueue.front();
            theQueue.pop();

            // Add the vertex to our ordering
            ordering.push_back(curVertex);

            // Go through each edge from that vertex
            for (int i = 0; i < matrixSize; i++)
            {
                // Reduce the in-degree for the vertex the edge goes to
                if (adjacencyMatrix[curVertex][i] > 0)
                {
                    inDegreeArray[i]--;

                    // If the in-degree for that vertex is 0, put it in the queue
                    if (inDegreeArray[i] == 0)
                        theQueue.push(i);
                }
            }
        }

        // Print the ordering of our topological sort
        for (int i = 0; i < ordering.size(); i++)
        {
            int pos = ordering[i];
            if (pos != ordering.size() - 1)
                cout << vertices[pos] << " --> ";
            else
                cout << vertices[pos] << "\n";
        }
    }
    else // If a topological sort is not possible
        cout << "This graph cannot be topologically sorted.\n";
}

void Graph::computeShortestPaths(string nodeName)
{
    // Starting Vertex
    int initialVertex = distance(vertices.begin(), find(vertices.begin(), vertices.end(), nodeName));

    // Priority Queue
    priority_queue<Edge, vector<Edge>, sortQueue> priorityQueue;

    // Cost array which keeps track of the Path, Cost, and if the Vertex is found (True if 1, False if 0)
    int costArray[matrixSize][4];

    // Initial State
    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (i == initialVertex) // Mark the Path, Cost, and Found values for the starting vertex
            {
                // The Vertex
                costArray[i][0] = i;

                // The Path
                costArray[i][1] = -1;

                // The Cost
                costArray[i][2] = -1;

                // Is Found
                costArray[i][3] = 1;

                break;
            }
            else if (j != 0) // Setting the default values of the Path, Cost, and Found to 0.
                costArray[i][j] = -3;
            else // The label for the vertices
                costArray[i][j] = i;
        }
    }

    // Go through the row of the vertex and check for edges to add to the priority queue
    for (int i = 0; i < matrixSize; i++)
    {
        // If an edge exists, we push it to the queue
        if (adjacencyMatrix[initialVertex][i] > 0)
        {
            // Create an Edge object that stores the From, To, and Cost of the edge.
            Edge theEdge(initialVertex, i, adjacencyMatrix[initialVertex][i]);

            // Add the edge to the priority queue
            priorityQueue.push(theEdge);
        }
    }

    // Continue through until we reach out stop conditions
    while (!priorityQueue.empty())
    {
        // If we found all of the vertices, break the while loop
        if (foundNodes(costArray))
            break;

        // Otherwise, we need to handle the minimum item from the Priority Queue

        // If our vertex is not marked as found, update the cost array
        if (costArray[priorityQueue.top().to][3] != 1)
        {
            // Set the Path for our vertex
            costArray[priorityQueue.top().to][1] = priorityQueue.top().from;

            // Set the Cost four our vertex
            costArray[priorityQueue.top().to][2] = priorityQueue.top().cost;

            // Mark the vertex as found
            costArray[priorityQueue.top().to][3] = 1;

            // Pop the current edge from the queue
            Edge curEdge(priorityQueue.top().from, priorityQueue.top().to, priorityQueue.top().cost);
            priorityQueue.pop();

            // Handle the edges from our vertex
            for (int i = 0; i < matrixSize; i++)
            {
                // If an edge exists and the vertex is not marked as found, we push it to the queue
                if (adjacencyMatrix[curEdge.to][i] > 0 && costArray[i][3] != 1)
                {
                    // Create an Edge object that stores the From, To, and Cost of the edge.
                    Edge theEdge(curEdge.to, i, (adjacencyMatrix[curEdge.to][i] + costArray[curEdge.to][2]));

                    // Add the edge to the priority queue
                    priorityQueue.push(theEdge);
                }
            }
        }
        else if (priorityQueue.top().cost < costArray[priorityQueue.top().to][2]) // Check if the current path is a shorter path than the one calculated earlier
        {
            // Update the Path
            costArray[priorityQueue.top().to][1] = priorityQueue.top().from;

            // Update the Cost
            costArray[priorityQueue.top().to][2] = priorityQueue.top().cost;
        }
        else // Remove the edge from the queue
            priorityQueue.pop();
    }

    // Print the Results
    cout << "Shortest Paths from " << vertices[initialVertex] << ":\n";

    // Go through each vertex and print their stack
    for (int i = 0; i < matrixSize; i++)
    {
        // We don't want to print the initial vertex's path
        if (costArray[i][1] >= 0)
        {
            // Stack to keep track of the path
            stack<int> theStack;

            // Keeps track of the current vertex we're at
            int curVertex = i;

            // Push the vertex we're looking at
            theStack.push(costArray[i][0]);

            // If necessary, backtrack until we reach the initial node
            while (costArray[curVertex][1] != initialVertex)
            {
                // Push the current to the array
                theStack.push(costArray[curVertex][1]);

                // Change the vertex we're looking at
                curVertex = costArray[curVertex][1];
            }

            // Print the path
            cout << vertices[initialVertex] << " --> ";

            // Iterate through each vertex in the stack and print it
            while (!theStack.empty())
            {
                // If the previous is already the initial vertex, just print the line
                if (theStack.size() == 1)
                {
                    cout << vertices[theStack.top()] << " || Weight: " << costArray[i][2] << "\n";
                    theStack.pop();
                }
                else
                {
                    cout << vertices[theStack.top()] << " --> ";
                    theStack.pop();
                }
            }
        }
        else if (costArray[i][1] == -3) // If we could not find a path
        {
            cout << "No path from " << vertices[initialVertex] << " to " << vertices[costArray[i][0]] << " found.\n";
        }
    }
}

void Graph::computeMinimumSpanningTree()
{
    // Disjoint Set
    DisjointSet disjointSet(matrixSize);

    // Queue to sort the edges
    priority_queue<Edge, vector<Edge>, sortQueue> priorityQueue;

    // Sorted Queue for the final results
    priority_queue<Edge, vector<Edge>, sortQueue> results;

    // Sort the edges
    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixSize; j++)
        {
            // If an edge exists
            if (adjacencyMatrix[i][j] > 0)
            {
                Edge theEdge(i, j, adjacencyMatrix[i][j]);

                // Sort
                priorityQueue.push(theEdge);
            }
        }
    }

    // Do union of the two sets
    bool unionLoop = false;

    // Total Cost
    int totalCost = 0;

    while (!unionLoop)
    {
        // Used to determine if the vertices are in the same set
        int set1 = disjointSet.find(priorityQueue.top().from);
        int set2 = disjointSet.find(priorityQueue.top().to);

        // Check if the From and To vertex are in the same set
        if (set1 != set2)
        {
            // Do Union
            unionLoop = disjointSet.doUnion(priorityQueue.top().from, priorityQueue.top().to);

            // Store the edge for printing purposes
            Edge theEdge(priorityQueue.top().from, priorityQueue.top().to, priorityQueue.top().cost);
            results.push(theEdge);

            // Add to the total cost
            totalCost += theEdge.cost;
        }
        priorityQueue.pop();
    }

    // Print Results
    cout << "Minimum Spanning Tree:\n";

    while (!results.empty())
    {
        cout << vertices[results.top().from] << " -- " << vertices[results.top().to] << " || Weight: " << results.top().cost << endl;
        results.pop();
    }
    cout << "Total Cost: " << totalCost << "\n";
}

bool Graph::foundNodes(int costArray[][4])
{
    // Go through each row in the cost array
    for (int i = 0; i < matrixSize; i++)
        if (costArray[i][3] == -3) // Check if the vertex is found
            return false;
    return true;
}