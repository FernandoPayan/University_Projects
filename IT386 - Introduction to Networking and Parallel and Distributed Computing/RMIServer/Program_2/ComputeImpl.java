import java.rmi.*;
import java.rmi.server.*;
import java.lang.Math;

/**
 * Remote server class that implements HelloInterface
 *  Author: fpayan
 *  Homework: Program 02
*/
public class ComputeImpl extends UnicastRemoteObject implements Compute{

    /** Constructor for remote object */
    public ComputeImpl () throws RemoteException{};

	public double add(double a, double b) throws RemoteException
    {
        return Math.round((a + b) * 100.0) / 100.0;
	}

	public double subtract(double a, double b) throws RemoteException
    {
        return Math.round((a - b) * 100.0) / 100.0;
	}

	public double multiply(double a, double b) throws RemoteException
    {
        return Math.round((a * b) * 100.0) / 100.0;
	}

	public double divide(double a, double b) throws RemoteException
    {
        /* Check for division for zero */
        if (b == 0)
            System.out.println("Error: Cannot divide by 0");
        else
            return Math.round((a / b) * 100.0) / 100.0;

        return 0;
	}

	public int gcd(int a, int b) throws RemoteException
    {
        /* Loop to find GCD until we reach a value of 0 */
        while (b != 0)
        {
            /* Swap values */
            int temp = b;
            b = a % b;
            a = temp;
        }

        return a;
	}

	public double circleArea(double radius) throws RemoteException
	{
        return Math.round(Math.PI * (radius * radius) * 100.0) / 100.0;
	}

	public double rectangleArea(double length, double height) throws RemoteException 
    {
        return multiply(length, height);
	}
}
