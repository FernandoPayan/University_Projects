package fpayanilstu.edu;

import java.util.Collections;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

/***
 * 
 * @author Fernando Payan
 * 
 */
public class Game {
	
	/***
	 * A linked list to store the unshuffled cards
	 */
	private LinkedList<String> unshuffledCards = new LinkedList<>();
	
	/***
	 * A stack of the faced down cards 
	 */
	private Stack<String> faceDownCards = new Stack<>();
	
	/***
	 * A stack of the faced-up cards that are thrown to the floor
	 */
	private Stack<String> faceUpCards = new Stack<>();
	
	/*** 
	 * A queue of the players
	 */
	 private Queue<Player> players = new LinkedList<>();
	
	/***
	 * A shuffle method that randomly adds the cards from the linked list to the faced down stack.
	 */
	private void shuffle() 
	{
		addCards(); // Creates the cards and adds them to the LinkedList
		Collections.shuffle(unshuffledCards); // Shuffles the cards
		
		while (unshuffledCards.size() > 0) // Randomly adds the cards from the linked list to the faced down stack.
		{
			faceDownCards.add(unshuffledCards.pop());
		}			
	}
	
	/***
	 * Constructors that takes the player names, calls the shuffle method, and create the player objects.
	 * @param p1 the first player
	 * @param p2 the second player
	 */
	public Game(String p1, String p2)
	{
		shuffle();
		Player player1 = new Player(p1, faceDownCards);
		players.add(player1);
		
		Player player2 = new Player(p2, faceDownCards);
		players.add(player2);
	}
	/***
	 * 
	 * @param p1 the first player
	 * @param p2 the second player
	 * @param p3 the third player
	 */
	public Game(String p1, String p2, String p3)
	{
		shuffle();
		Player player1 = new Player(p1, faceDownCards);
		players.add(player1);
		
		Player player2 = new Player(p2, faceDownCards);
		players.add(player2);
		
		Player player3 = new Player(p3, faceDownCards);
		players.add(player3);
	}
	
	/***
	 * 
	 * @param p1 the first player
	 * @param p2 the second player
	 * @param p3 the third player
	 * @param p4 the fourth player	
	 */
	public Game(String p1, String p2, String p3, String p4)
	{
		shuffle();
		Player player1 = new Player(p1, faceDownCards);
		players.add(player1);
		
		Player player2 = new Player(p2, faceDownCards);
		players.add(player2);
		
		Player player3 = new Player(p3, faceDownCards);
		players.add(player3);
		
		Player player4 = new Player(p4, faceDownCards);
		players.add(player4);
	}
	
	/***
	 * 
	 * @param p1 the first player
	 * @param p2 the second player
	 * @param p3 the third player
	 * @param p4 the fourth player	
	 * @param p5 the fifth player
	 */
	public Game(String p1, String p2, String p3, String p4, String p5)
	{
		shuffle();
		Player player1 = new Player(p1, faceDownCards);
		players.add(player1);
		
		Player player2 = new Player(p2, faceDownCards);
		players.add(player2);
		
		Player player3 = new Player(p3, faceDownCards);
		players.add(player3);
		
		Player player4 = new Player(p4, faceDownCards);
		players.add(player4);
		
		Player player5 = new Player(p5, faceDownCards);
		players.add(player5);
	}
	
	/***
	 * Method to simulate the game
	 */
	public void simulateGame()
	{
		System.out.println("Starting the game! You will have to press any key to continue through the simulation! (Preferred Key: 'n' for Next)");
		
		/***
		 * A while loop that allows the game to continue until a player has run out of cards or if a player has won.
		 */
		boolean loop = false;
		while (loop == false)
		{
			for (Player e: players)
				if (e.decideDraw(faceUpCards, faceDownCards))
				{
					loop = true;
					break;
				}
		}
		
		for (Player e: players)
			e.printHand();
	}
	
	
	/***
	 * A method used to add cards to the LinkedList unshuffledCards
	 */
	private void addCards() {
		String[] suits = {"Hearts", "Spades", "Clubs", "Diamonds"};
		int[] num = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		String card = "";
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				card = num[j] + " of " + suits[i];
				unshuffledCards.add(card);
			}
		}
	}
}
