import java.rmi.Naming;
import java.lang.Math;

/** Client class that will use the remote service 
 *  Author: fpayan
 *  Homework: Program 02
*/
public class Client{

public static void main (String[] argv) {

    try 
    {
      /* Obtain the port number */
      int portNum = Integer.parseInt(argv[0]);
      double a = Double.parseDouble(argv[1]); /* First value for Addition/Subtraction/Multiplication/Division/GCD/ */
      double b = Double.parseDouble(argv[2]);

      Compute remoteObj = (Compute) Naming.lookup("//localhost:" + portNum + "/Server"); 

      /* Print the result of Addition method */
      System.out.println("Addition of " + a + " and " + b + " = " + remoteObj.add(a, b));

      /* Print the result of Subtraction method */
      System.out.println("Subtraction of " + a + " and " + b + " = " + remoteObj.subtract(a, b));

      /* Print the result of Multiplication method */
      System.out.println("Multiplication of " + a + " and " + b + " = " + remoteObj.multiply(a, b));

      /* Print the result of Division method */
      System.out.println("Division of " + a + " and " + b + " = " + remoteObj.divide(a, b));

      /* Print the result of GCD method */
      System.out.println("The GCD of " + (int) a + " and " + (int) b + " = " + remoteObj.gcd((int) a, (int) b));

      /* Print the result of Area of a Circle method */
      System.out.println("The area of a circle with radius "+ a + " is " + remoteObj.circleArea(a));

      /* Print the result of Area of a Rectangle method */
      System.out.println("The area of a rectangle with length " + a + " and height " + b + " = " + remoteObj.rectangleArea(a, b));

    } catch (Exception e) 
    {
      System.out.println ("Client exception: " + e);
    }
  }
}
