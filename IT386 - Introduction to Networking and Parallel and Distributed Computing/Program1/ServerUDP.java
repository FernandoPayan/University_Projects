/**
 * Server UDP file
 * Authors: Fernando Payan and Tim Buranicz
*/

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;


public class ServerUDP {
    public static void main (String[] args) throws Exception
  {
    DatagramSocket serverSocket = new DatagramSocket(Integer.parseInt(args[0]));

    byte[] receive = new byte[9999];

    //Receiving packet
    DatagramPacket recvPacket = new DatagramPacket(receive, receive.length);

    serverSocket.receive(recvPacket);
    String receiveData = new String(recvPacket.getData());
    System.out.println("Received packet: " + receiveData);
 
    // Binds the datagram socket to available port on the local host machine
    
    // Converts the characters to uppercase
    String result = (InetAddress.getLocalHost().getHostName() + ": " + receiveData.toUpperCase());
    receive = result.getBytes();

    //TEMP SOCKET NUMBER
    DatagramPacket sender = new DatagramPacket(receive, receive.length, InetAddress.getByName(args[1]), recvPacket.getPort());
    serverSocket.send(sender);
    
    //Close socket
    System.out.println("Packet sent. Now closing socket...");
    serverSocket.close();
  }
}
