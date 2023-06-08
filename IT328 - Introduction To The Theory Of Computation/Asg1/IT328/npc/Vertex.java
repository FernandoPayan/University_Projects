import java.util.ArrayList;

public class Vertex implements Comparable<Vertex>
{
    /* Local Variables */
    private int vertexNum;
    private ArrayList<Vertex> adjVertices;
    
    /* Default Constructor */
    public Vertex(int number) 
    {
        vertexNum = number;
        adjVertices = new ArrayList<Vertex>();
    }

    /* Getter for vertex number (variable index) */
    public int getVertex()
    {
        return vertexNum;
    }
    
    /* Getter for adjacent vertices */
    public ArrayList<Vertex> getAdjvertices()
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

    /* Used to be able to sort the ArrayList of vertices found for the max clique in ascending order */
    @Override
    public int compareTo(Vertex vertex)
    {
        int compareVal = ((Vertex)vertex).getVertex();

        return this.vertexNum - compareVal;
    }
}	
