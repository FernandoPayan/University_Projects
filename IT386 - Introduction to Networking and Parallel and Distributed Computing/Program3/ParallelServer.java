/**
 * Parallel Server file
 * Author: Fernando Payan
 * Course: IT386-001
 * Date: May 4th, 2023
*/
import java.net.ServerSocket;
import java.net.Socket;
import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;


public class ParallelServer {
  /* Global Variable */
  private static int clientNumber = 0;

  public static void main (String[] args) throws Exception
  {

    /* Check if the user passed enough arguments */
    if (args.length != 1) 
    {
      System.err.println("Usage: java ParallelServer <port number>");
      System.exit(1);
    }

    /* Initialize local variables */
    String clientSentence = "";
    String returnSentence = "";

    /* Obtaining port number and create server socket */
    int portNumber = Integer.parseInt(args[0]);

    /* Create a welcoming socket */
    ServerSocket welcomeSocket = new ServerSocket(portNumber);
    System.out.println("Parallel TCP server waiting ...");
    
    /* Wait on welcoming socket for contact from the client */
    while (true)
    {
      Socket connectionSocket = welcomeSocket.accept();

      /* Parallel Work */
      WorkerServer obj = new WorkerServer(clientSentence, connectionSocket);
      Thread worker = new Thread(obj);
      worker.start();

    }    
  }

  private static class WorkerServer implements Runnable
  {
    /* Declare local variables */
    private String receiveData;
    private Socket socket;
    private int clientNum;
    
    /* Constructor */
    public WorkerServer(String clientSentence, Socket connectionSocket)
    {
      this.receiveData = clientSentence;
      this.socket = connectionSocket;

      /* Increment the client number */
      incrementClient();

      this.clientNum = clientNumber;
    }

    /* Thread Work */
    @Override
    public void run()
    {
      System.out.println("Connected to client " + clientNum);

      try
      {
        /* Create input stream attached to socket */
        BufferedReader inFromClient = new BufferedReader(new InputStreamReader(socket.getInputStream()));

        /* 1 - Create a return message, can simple transform sentence toUpperCase */
        receiveData = inFromClient.readLine();
        System.out.println("From Client " + clientNum + ": " + receiveData);

        /* 2 - Create output stream, attached to socket */
        DataOutputStream outToClient = new DataOutputStream(socket.getOutputStream());

        /* 3 - Write the line out to Socket */
        outToClient.writeBytes(receiveData.toUpperCase() + '\n');
        System.out.println("reply sent: " + clientNum);
      }
      catch (IOException e)
      {
        System.out.println("An error has occured trying to retrieve the message...");
      }
    }
    
    /* Synchronized method used to increment the client number */
    private synchronized void incrementClient()
    {
      clientNumber++;
    }
  }
}
