import java.rmi.Naming;
import java.rmi.server.*;

/** Remote Server class
 *  Author: fpayan
 *  Homework: Program 02
*/
public class Server {
    public static void main(String args[]) {
        try {
            ComputeImpl obj = new ComputeImpl();
            // Bind this object instance to the name "Server"
            int portNum = Integer.parseInt(args[0]);

            Naming.rebind("//localhost:" + portNum + "/Server", obj);
            System.out.println("The Server is ready");
        } catch (Exception e) {
            System.out.println("Server failed: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
