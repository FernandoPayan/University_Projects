package fpayanilstu.edu;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;

/***
 * 
 * @author Fernando Payan
 * Main class controls the flow of execution
 */

public class MainClass {

	/***
	 * Controls the flow of the program.
	 */
	public static void main(String[] args) {
		/***
		 * Global Variables used to get the user's input and creates the morse code tree.
		 */
		Scanner input = new Scanner(System.in);
		String userInput = " ";
		boolean cont = true;
		MorseTree letters = new MorseTree(" ", null, null);
		buildTree(letters);

		
		/***
		 * While loop that asks the user to enter the encoded message. The loop breaks when the user enters "stop".
		 */
		while (cont)
		{
			System.out.print("Please enter the encoded message or stop to exit (* for dot | - for dash): ");
			userInput = input.nextLine();

			if (!userInput.contains("*") || !userInput.contains("*"))
			{
				if (userInput.equals("stop"))
					cont = false;
				else
					System.out.println("Please enter a vaild Morse Code!");
			} else
				System.out.println("The decoded message is: " + decode(letters, userInput));
		}
		
		System.out.println("Thank you for using our decorder!");
		input.close();
		 
	}
	
	/***
	 * Builds the tree using the file that contains the letters and their codes
	 * @param tree | the MorseTree object
	 */
	private static void buildTree(MorseTree tree)
	{
		try {
			FileInputStream fis;
			fis = new FileInputStream("letters.txt");
			Scanner in = new Scanner(fis);
			
			while(in.hasNext()) 
			{
				String line = in.nextLine();
				String array[] = line.split(" "); // Gets every letter in the line along with its code and puts it into an array		
				
				for (int i = 0; i < array.length; i++) // Adds each letter in the line into the tree
					tree.add(array[i]);
			}

		} catch (FileNotFoundException e) {
			System.out.println("FileNotFound Exception Error. Please make sure the text file 'letters.txt' is in the project folder.");
			System.exit(0);
		}
	}
	
	/***
	 * Decodes the message entered by the user
	 * @param tree | gets the Morse Code tree
	 * @param input | gets the user's input to decode
	 * @return returns the decoded message
	 */
	private static String decode(MorseTree tree, String input)
	{
		String array[] = input.split(" "); // Gets every code in the line and puts it into an array
		StringBuilder message = new StringBuilder();
		
		for (int i = 0; i < array.length; i++) // Decodes each morse code given and adds the resulting decoded letter to the String Builder.
		{
			message.append(tree.decode(array[i]));
		}
		return message.toString();
	}
}