package fpayanilstu.edu;

import java.util.Scanner;

/***
 * 
 * @author Fernando Payan
 * Main class controls the flow of execution
 */
public class Main {

	/***
	 * Controls the flow of the program.
	 */
	public static void main(String[] args) {
		/***
		 * Global Variables used to determine number of players and creates the Game object.
		 */
		Scanner input = new Scanner(System.in);
		int numPlayers = 0;
		System.out.print("How many players are playing? (Minimum of 2, Max of 5): ");
		numPlayers = input.nextInt();
		
		switch (numPlayers)
		{
			case 2: 
			{
				System.out.println("Please enter the first name of the players:");
				Game game = new Game(input.next(), input.next());
				game.simulateGame(); // This will start the game
				break;
			}
			case 3:
			{
				System.out.println("Please enter the first name of the players:");
				Game game = new Game(input.next(), input.next(), input.next());
				game.simulateGame(); // This will start the game
				break;
			}
			case 4: 
			{
				System.out.println("Please enter the first name of the players:");
				Game game = new Game(input.next(), input.next(), input.next(), input.next());
				game.simulateGame(); // This will start the game
				break;
			}
			case 5: 
			{
				System.out.println("Please enter the first name of the players:");
				Game game = new Game(input.next(), input.next(), input.next(), input.next(), input.next());
				game.simulateGame(); // This will start the game
				break;
			}
		}
		input.close();
	}

}
