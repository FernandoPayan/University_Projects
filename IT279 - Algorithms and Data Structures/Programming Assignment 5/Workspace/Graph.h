// Graph header file
// By Fernando Payan
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

class Graph
{
private:
    /**
        Structure used for edges in a graph
    */
    struct Edge
    {
        // The "From" Vertex
        int from;

        // The "To" Vertex
        int to;

        // The cost of the edge
        int cost;

        // Constructor
        Edge(int row = -1, int column = -1, int weight = -1) : from(row), to(column), cost(weight) {}
        
    };

    /**
        Structure used for our priority queue. Helps sort the queue by the cost of the edge.
    */
    struct sortQueue
    {
        bool operator()(const Edge& edge1, const Edge& edge2)
        {
            if (edge1.cost != edge2.cost) // If the cost aren't the same
                return edge1.cost > edge2.cost;
            else if (edge1.cost == edge2.cost) // If the cost is the same, then we check if the from is the same
            {
                if (edge1.from != edge2.from) // If the from vertices aren't the same
                    return edge1.from > edge2.from;
                else if (edge1.from == edge2.from) // If the cost and from is the same, return the smallest "to"
                {
                    return edge1.to > edge2.to;
                }
            }
        }
    };

    // Stores the contents of the adjacency matrix. Initially declared empty
    vector<vector <int>> adjacencyMatrix;

    // Stores the names of all of the verticies
    vector<string> vertices;

    // Stores the adjacency matrix's dimensions
    int matrixSize;

    // Stores the number of edges
    int numEdges;

    // Stores the file name
    string fileName;

    // Input stream class to operate on files
    ifstream inputFile;

public:
    // constructor
    Graph();

    /**
        Accepts the name of a file and read in a new graph from that file, replacing 
        whatever the object currently holds (if anything). It will return a boolean 
        which will be true unless the input file could not be opened.
    */
    bool readGraph(string input);

    /**
        Prints the graph to cout in the same format as the graphs we are reading.
    */
    void printGraph();

    /**
        Print to standard output a topological sort of the graph or an error message
        indicating that a topological sort of the graph is not possible.
    */
    void computeTopologicalSort();

    /**
        Accept a node name as a parameter and print to standard output the actual path
        and the cost to each other vertex that can be reached (one path and cost per line). 
        For any nodes that cannot be reached, it will print a message to effect.
    */
    void computeShortestPaths(string nodeName);

    /**
        Print to standard output a list of the edges in the minimum spanning tree for the 
        graph, one per line, with the weight of each edge, followed by the total weight of
        the minimum spanning tree.
    */
    void computeMinimumSpanningTree();

    /**
        Used as a condition to check if we need to stop calulating the shorest path
    */
    bool foundNodes(int costArray[][4]);
};

#endif