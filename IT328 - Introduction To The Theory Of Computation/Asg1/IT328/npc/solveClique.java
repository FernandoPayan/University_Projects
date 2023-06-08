/*
    This program file takes in a text file of graph data in adjacency matrix format and solves the Max Clique problem

    Author: fpayan
*/

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

public class solveClique 
{	
	/* Generate the graphs */
	public ArrayList<Graph> readGraphs(String filename) throws Exception
	{
		/* Crate the ArrayList to store the graph */
		ArrayList<Graph> graphList = new ArrayList<Graph>();

		/* Try-Catch safeguard in case the file is not found */
		try 
		{
			/* Open the input file */
			File file = new File(filename);
			Scanner sc = new Scanner(file);

			/* Iterate through all the lines in the text file */
			while (sc.hasNextLine())
			{
				/* Read the size of the graph and create a graph of vertexCount size */
				Graph graph = new Graph(Integer.parseInt(sc.nextLine()));

				/* Mark and store the vertices to our Graph ArrayList */
				for (int i = 0; i < graph.getVertexCount(); i++) 
				{
					graph.addVertex(new Vertex(i));
				}

				/* Iterate through the list and determine which vertices are connected/has edges */
				for (int i = 0; i < graph.getVertexCount(); i++) 
				{
					/* Get the next line */
					String row = sc.nextLine();

					/* Reset the variable we're looking at */
					int curVariableIndex = 0;

					/* Interates through the row in the matrix and puts the values into the graph's 2D array */
					for (String num : row.split(" ")) 
					{
						/* Gets the current value found in matrix */
						int matrixVal = Integer.parseInt(num);

						/* Stores the value to our graph's 2D array */
						graph.getAdjacencyMatrix()[i][curVariableIndex] = matrixVal;

						if (i != curVariableIndex && matrixVal == 1) /* Ensures that we don't count out the same variable as an existing edge */
						{
							/* Add to list of adjacent vertices for this current vertex */
							graph.getVertices().get(i).addAdjacentVertex(graph.getVertices().get(curVariableIndex));

							/* Update the edge count */
							graph.setEdgeCount(graph.getEdgeCount() + 1);
						}

						/* Move to the next variable */
						curVariableIndex++;
					}
				}

				/* Since we're always incrementing the edge count by 1 for every edge we detect, we are counting duplicates.
				 * In order to fix this, we can simply divide our edge count two so that we don't count the same edge twice */
				graph.setEdgeCount(graph.getEdgeCount() / 2);

				/* Add the graph to our list of graphs */
				graphList.add(graph);
			}

			/* Close Scanner */
			sc.close();
		}

		/* If the file is not found, throw a FileNotFoundException */
		catch (FileNotFoundException e)
		{ 
			System.out.println("Could not locate " + filename + ". Please restart the program and make sure the file is in the same directory.");
			System.exit(0);
		}

		/* Return the list of graphs found in the text file */
		return graphList;
	}
	
	/* Recursive method to find the Maximum Clique. Stores the list into the graph object */
	public void solveMaxClique(ArrayList<Vertex> cliqueList, ArrayList<Vertex> adjacentVertices, Graph graph)
	{
		/* Base condition: When we found our clique, we add it and store it to our graph's ArrayList of Cliques */
		if (adjacentVertices.isEmpty())
		{
			graph.addClique(cliqueList);
		}

		/* Iterate through all the veritices in the graph */
		for (int i = 0; i < adjacentVertices.size(); i++)
		{
			/* Create a temp list of our current lists */
			ArrayList<Vertex> curCliqueList = new ArrayList<>(cliqueList);
			ArrayList<Vertex> curAdjacentVertices = new ArrayList<>(adjacentVertices);

			/* Add the current vertex to our list of cliques */
			curCliqueList.add(adjacentVertices.get(i));

			/* Use retainAll to calculate which vertices have a clique */
			curAdjacentVertices.retainAll(adjacentVertices.get(i).getAdjvertices());

			/* Recursively call the method with our new updated list of adjacent vertices/current clique list */
			solveMaxClique(curCliqueList, curAdjacentVertices, graph);
			
			/* Clean Up */
			adjacentVertices.remove(adjacentVertices.get(i));
		}
	}	

	public static void main(String[] args) throws Exception {
		/* Create our Clique object */
		solveClique cliques = new solveClique();

		/* Check if argument was passed */
		if (args.length == 0)
		{
			System.out.println("Did not pass in a text file. Please pass it as an argument");
			System.exit(0);
		}

		/* Create the graphs from the file */
		ArrayList<Graph> inputGraphs = cliques.readGraphs(args[0]);
		
		/* Print out the opening message */
		System.out.println("* Max Cliques in graphs in " + args[0]);
		System.out.println("\t(|V|,|E|) (size, ms used) Cliques");
		

		/* Iterates through all the graphs from the text file and prints out the results to the console */
		for (int i = 0; i < inputGraphs.size() - 1; i++) 
		{
			Graph graph = inputGraphs.get(i);

			/* Print out the graph number */
			System.out.print("G" + (i+1) + " (" + graph.getVertexCount() + "," + graph.getEdgeCount() + ")");

            /* Calculate the time to solve the maximum clique for the current graph in ms */
			long startTime = System.nanoTime();

			cliques.solveMaxClique(new ArrayList<Vertex>(), graph.getVertices(), graph);

			long endTime = (System.nanoTime()- startTime) / (long) 1e6;
			
			/* ArrayList to store all the verticies found in the max clique */
            ArrayList<Vertex> maxClique = new ArrayList<Vertex>();

            /* Populate our ArrayList with the vertices that make up the max clique */
			for (ArrayList<Vertex> curCliqueList : graph.getCliques()) 
			{
				if (maxClique.size() < curCliqueList.size())
				{
					maxClique = new ArrayList<>(curCliqueList);
				}
			}

            /* RESULTS */

			/* Sort the list of Maximum Clique in ascending order */
			Collections.sort(maxClique);

			/* Size of Maximum Clique and how long (in ms) it took */
            System.out.print(" (size=" + maxClique.size() + " ms=" + String.format("%.0f", Math.ceil(endTime)) + ") {");

            /* Print out the maximum clique variables */
			for (int j = 0; j < maxClique.size() - 1; j++)
			{
				System.out.print(maxClique.get(j) + ",");
			}

			/* Print out the last value */
			System.out.print(maxClique.get(maxClique.size() - 1) + "}\n");
		}
		System.out.println("***");
	}
}