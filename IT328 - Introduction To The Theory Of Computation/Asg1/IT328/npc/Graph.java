import java.util.ArrayList;
import java.util.List;

public class Graph
{
	/* Local Variables */
	private int numVertices; 						/* Stores the number of vertices in the graph */
	private int numEdges;							/* Stores the number of edges in the graph */
	private ArrayList<Vertex> vertices;				/* Stores the list of vertices in the graph */
	private int[][] graphInput;						/* Stores the values obtained from the graphs.txt file */
	private List<ArrayList<Vertex>> cliques;		/* Stores the arraylists of cliques that make up the max clique in the graph */
	
	/* Default Constructor */
	public Graph(int vertices)
	{
		/* Set the number of vertices for the graph */
		this.numVertices = vertices;

		/* Set the number of edges for the graph */
		this.numEdges = 0;

		/* Set the number of vertices for the graph */
		this.vertices = new ArrayList<Vertex>();

		/* Create the adjacency matrix */
		this.graphInput = new int[vertices][vertices];
		
		/* Create the list to store our arraylist of cliques */
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

	/* Add the ArrayList of cliques to our list of all the cliques found */
	public void addClique(ArrayList<Vertex> clique) 
	{
		this.cliques.add(clique);
	}	

	public int[][] getAdjacencyMatrix() 
	{
		return graphInput;
	}
}
