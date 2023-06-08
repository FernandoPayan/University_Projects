import java.rmi.Naming;
/** Client class that will use the remote service 
 * IT 386 Example
*/
public class HelloRMIClient{

public static void main (String[] argv) {

    try {

      HelloInterface remoteObj =
        (HelloInterface) Naming.lookup("//localhost/HelloRMIServer");

      System.out.println (remoteObj.sayHello());
      System.out.println(remoteObj.calSum(5, 2));
    } catch (Exception e) {
      System.out.println ("HelloClient exception: " + e);
    }
  }


}
