import java.rmi.*;

/** Remote interface declares each of the methods
 that you want to call remotely 
 IT 386 - Example */
public interface HelloInterface extends Remote {

    /** Remotely invocable method */
    String sayHello() throws RemoteException;

    int calSum(int a, int b) throws RemoteException;

}
