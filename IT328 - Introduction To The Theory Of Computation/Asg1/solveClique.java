
/*
    This program file takes in a text file of graph data and solves Clique problem

    Author: fpayan
*/
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Collections;

public class solveClique {

	/* Vertex Class */
	public class Vertex implements Comparable<Vertex>{
		/* Local Variables */
		private int vertexNum;
		private ArrayList<Vertex> adjVertices;
		
		/* Default Constructor */
		public Vertex(int number) 
		{
			vertexNum = number;
			adjVertices = new ArrayList<Vertex>();
		}

		public int getVertex()
		{
			return vertexNum;
		}
		
		/* Getter for adjacent verticies */
		public ArrayList<Vertex> getAdjVerticies()
		{
			return adjVertices;
		}
		
		/* Adds vertex to the list of adjacent vertices */
		public void addAdjacentVertex(Vertex vertex)
		{
			this.adjVertices.add(vertex);
		}
		
		/* Used to parse the integer as a string when outputting the results */
		@Override
		public String toString() 
		{
			return String.valueOf(vertexNum);
		}

		/* Used to be able to sort the ArrayList of verticies found for the max clique in ascending order */
		@Override
		public int compareTo(Vertex vertex)
		{
			int compareVal = ((Vertex)vertex).getVertex();

			return this.vertexNum - compareVal;
		}
	}	

	/* Graph Class */
	public class Graph {

		/* Local Variables */
		private int numVertices; 						/* Stores the number of verticies in the graph */
		private int numEdges;							/* Stores the number of edges in the graph */
		private ArrayList<Vertex> vertices;				/* Stores the list of verticies in the graph */
		private int[][] graphInput;						/* Stores the values obtained from the graphs.txt file */
		private List<ArrayList<Vertex>> cliques;		/* Stores the variables that make up the max clique in the graph */
		
		/* Default Constructor */
		public Graph(int vertices)
		{
			/* Set the number of verticies for the graph */
			this.numVertices = vertices;

			/* Set the number of edges for the graph */
			this.numEdges = 0;

			/* Set the numer of vertices for the graph */
			this.vertices = new ArrayList<Vertex>();

			/* Create the adjacency matrix */
			this.graphInput = new int[vertices][vertices];
			
			/* Create the list to store cliques */
			cliques = new ArrayList<ArrayList<Vertex>>();
		}

		/* Getter and Setters for Vertices */
		public ArrayList<Vertex> getVertices()
		{
			return vertices;
		}

		public void addVertex(Vertex vertex)
		{
			this.vertices.add(vertex);
		}

		/* Returns the number of vertices in the graph */
		public int getVertexCount()
		{
			return numVertices;
		}
		
		/* Getter and Setters for Edge Count */
		public int getEdgeCount() 
		{
			return numEdges;
		}
		
		public void setEdgeCount(int numEdges) 
		{
			this.numEdges = numEdges;
		}

		/* Getter for Cliques */
		public List<ArrayList<Vertex>> getCliques() 
		{
			return cliques;
		}

		public void addClique(ArrayList<Vertex> clique) 
		{
			this.cliques.add(clique);
		}	

		public int[][] getAdjacencyMatrix() 
		{
			return graphInput;
		}
	}
		
	/* Generate the graphs */
	public ArrayList<Graph> readGraphs(String filename) throws Exception {
		
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
				int vertexCount = Integer.parseInt(sc.nextLine());
				Graph graph = new Graph(vertexCount);

				/* Mark and store the verticies to our Graph ArrayList */
				for (int i = 0; i < vertexCount; i++) 
				{
					Vertex vertex = new Vertex(i);
					graph.addVertex(vertex);
				}

				/* Iterate through the list and determine which vertices are connected/has edges */
				for (int i = 0; i < vertexCount; i++) 
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

						if (matrixVal == 1 && i != curVariableIndex) /* Ensures that we don't count out the same variable as an existing edge */
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
	public void findMaxClique(ArrayList<Vertex> cliqueList, ArrayList<Vertex> verticesList, ArrayList<Vertex> retainedList, Graph graph) {
		/* Base condition: When we found our clique, we add it and store it to our graph's ArrayList of Cliques */
		if (verticesList.isEmpty() && retainedList.isEmpty())
			graph.addClique(cliqueList);

		/* Iterate through all the veritices in the graph */
		for (int i = 0; i < verticesList.size(); i++)
		{
			/* Get the current vertex */
			Vertex curVertex = verticesList.get(i); 

			/* Create a temp list of our current lists */
			ArrayList<Vertex> newCliqueList = new ArrayList<>(cliqueList);
			ArrayList<Vertex> newVerticesList = new ArrayList<>(verticesList);
			ArrayList<Vertex> curRetainedList = new ArrayList<>(retainedList);

			/* Add the current vertex to our list of cliques */
			newCliqueList.add(curVertex);

			newVerticesList.retainAll(curVertex.getAdjVerticies());
			curRetainedList.retainAll(curVertex.getAdjVerticies());

			findMaxClique(newCliqueList, newVerticesList, curRetainedList, graph);
			
			/* Clean Up */
			verticesList.remove(curVertex);
			retainedList.add(curVertex);
		}
	}	

	public static void main(String[] args) throws Exception {
		solveClique sClique = new solveClique();

		/* Check if argument was passed */
		if (args.length == 0)
		{
			System.out.println("Did not pass in a text file. Please pass it as an argument");
			System.exit(0);
		}

		/* Get the file */
		String input = args[0];

		/* Create the graphs from the file */
		ArrayList<Graph> graphList = sClique.readGraphs(input);
		
		System.out.println("* Max Cliques in graphs in " + input);
		System.out.println("\t(|V|,|E|) (size, ms used) Cliques");
		

		/* Iterates through all the graphs from the text file and prints out the results to the console */
		for (int i = 0; i < graphList.size() - 1; i++) {
			Graph graph = graphList.get(i);

			/* Print out the graph number */
			System.out.print("G" + (i+1) + " (" + graph.getVertexCount() + "," + graph.getEdgeCount() + ")");

            /* Calculate the time to solve the graph in ms */
			long startTime = System.currentTimeMillis();

			sClique.findMaxClique(new ArrayList<Vertex>(), graph.getVertices(), new ArrayList<Vertex>(), graph);

			long endTime = (new Date()).getTime() - startTime;

            ArrayList<Vertex> maxClique = new ArrayList<Vertex>();

            /* Calculate the size of the maximum clique */
			for (ArrayList<Vertex> clique : graph.getCliques()) {
				if (clique.size() > maxClique.size())
					maxClique = new ArrayList<>(clique);
			}

            /* RESULTS */

			/* Sort the list of Maximum Clique in ascending order */
			Collections.sort(maxClique);

			/* Size of Maximum Clique and how long (in ms) it took */
            System.out.print(" (size=" + maxClique.size() + " ms=" + endTime + ") {");

            /* Print out the vertex cover */
			for (int j = 0; j < maxClique.size(); j++) {
				if (j < maxClique.size() - 1) /* Print the variables that make up the maximum clique */
				{
					System.out.print(maxClique.get(j) + ",");
				}
				else
				{
					System.out.print(maxClique.get(j) + "}\n");
				}
			}
		}
		System.out.println("***");
	}
}