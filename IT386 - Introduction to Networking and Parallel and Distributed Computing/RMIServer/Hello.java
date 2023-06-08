import java.rmi.*;
import java.rmi.server.*;
/**
 * Remote server class that implements HelloInterface
 * IT 386 - Example
*/
public class Hello extends UnicastRemoteObject implements HelloInterface{
    private String message;

    /** Constructor for remote object */
    public Hello (String msg) throws RemoteException{
        message = msg;
    }

    /** Implementation of remotely invocable method*/
    public String sayHello() throws RemoteException{
        return message;
    }

    /** Returns the sum of two integers */
    public int calSum(int a, int b)
    {
        return a + b;
    }
}
