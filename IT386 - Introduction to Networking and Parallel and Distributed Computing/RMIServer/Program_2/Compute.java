import java.rmi.*;

/** Remote interface declares each of the methods that you want to call remotely
 *  Author: fpayan
 *  Homework: Program 02
 * */
public interface Compute extends Remote {

    /* Addition of any two numbers, and returns the result */
    double add(double a, double b) throws RemoteException;

    /* Subtraction of any two numbers, and returns the result */
    double subtract(double a, double b) throws RemoteException;

    /* Multiplication of any two numbers, and returns the result */
    double multiply(double a, double b) throws RemoteException;

    /* Division of any two numbers, and returns the result */
    double divide(double a, double b) throws RemoteException;

    /* The GCD of two large integers using the Euclidean Algorithm and returns the result. */
    int gcd(int a, int b) throws RemoteException;

    /* Area of a circle given the radius, and returns the result */
    double circleArea(double radius) throws RemoteException;

    /* Area of a rectangle given the length and height, and returns the result */
    double rectangleArea(double length, double height) throws RemoteException;

}
