/**
   A Java program for Client using Sockets
   The TCP socket client reads input
   from the user and prints echoed message from the server

   Conpile: javac TCPclient.java
   Run: java TCPclient <host name> <port number>

   ToDO: Complete implementation of items 1 to 3.
   IT 386 - Spring 2023

   Name:

*/
import java.net.*;
import java.io.*;

class TCPclient {
  public static void main (String argv[]) throws Exception
  {
    String sentence; // store message to be sent
    String returnSentence; // store returned message from server
    /* Getting host name and port number from user */
    if (argv.length != 2) {
            System.err.println(
                "Usage: java ClientTCP <host name> <port number>");
            System.exit(1);
    }
    String hostName = argv[0];
    int portNumber = Integer.parseInt(argv[1]);
    /* Create the User input stream */
    BufferedReader inFromUser =
    new BufferedReader(new InputStreamReader(System.in));
    /* Create client socket, and connect it to the Server */
    Socket clientSocket =  new Socket (hostName, portNumber);
    System.out.println("Connected. Type your message to the server and press Return:");
    /* Create the output data stream attached to the Socket */
    DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());
    sentence = inFromUser.readLine(); // read user input from terminal
    /* Write (Send) line out to the Server */
    outToServer.writeBytes(sentence + '\n');
    System.out.println("Message sent...\n");
    /* ToDo: Get return message from server, and print to screen */
    /* 1 - Create input stream attached to socket to get incomming return message from server */
    BufferedReader inFromClient = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
    /* 2 - Read the line from Server */
    sentence = inFromClient.readLine();

    /* 3 - Print returned message from server */
    System.out.println(clientSentence);

    clientSocket.close();
    System.out.println("\nConnection closed\n ");
  }
}
