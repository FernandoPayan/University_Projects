/**
 * Client UDP file
 * Authors: Fernando Payan and Tim Buranicz
*/

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;

class ClientUDP {
  public static void main (String[] args) throws Exception
  {
    // Client reads a line of characters from its keyboard
    Scanner input = new Scanner(System.in);
    System.out.println("Please enter the message you want to send: ");
    String message  = input.nextLine();
    input.close();

    
    byte[] buffer = message.getBytes();
    
    //Getting local IP from client
    InetAddress ip = InetAddress.getByName(args[1]);

    // Constructs a datagram socket
    DatagramSocket clientSocket = new DatagramSocket();

    //TEMP SOCKET NUMBER
    DatagramPacket packet = new DatagramPacket(buffer, buffer.length, ip, Integer.parseInt(args[0]));
    clientSocket.send(packet);
    
    //Receive data from server
    byte[] receive = new byte[9999];

    //Receiving packet
    DatagramPacket recvPacket = new DatagramPacket(receive, receive.length);

    clientSocket.receive(recvPacket);
    String receiveData = new String(recvPacket.getData());

    //Print out results
    System.out.println("Message is: " + receiveData);

    // Close the socket
    clientSocket.close();
  }
}