package fpayanilstu.edu;

import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;
import java.util.Scanner;

/***
 * 
 * @author Fernando Payan
 *
 */
public class Player {

	/***
	 * A data structure to store the cards a player is holding.
	 */
	private LinkedList<String> playerHand = new LinkedList<>();

	/***
	 * Global Variables used to keep track of the player's name and an input used to help maintain the flow of the program.
	 */
	private String playerName = "";
	private Scanner input = new Scanner(System.in);
	
	/***
	 * A constructor that sets the player name and takes the initial 4 cards.
	 * @param name the player's name
	 * @param deck the deck the player is drawing from (For the constructor, it will always be faceDownCards)
	 */
	public Player(String name, Stack<String> deck) {
		this.playerName = name;
		
		for (int i = 0; i < 4; i++)
		{
			playerHand.push(deck.pop());
		}
		
		/***
		 * Checks if the player already has a winning hand
		 */
		if (isWinningHand())
		{
			System.out.println(this.playerName + "'s initial hand wins! Player Hand: " + this.playerHand);
		}
	}
	
	/***
	 * A method that will decide whether to draw a card from the stack or the floor. You should only draw from the floor if that card makes the player win.
	 * If value is returned true, it will break the while loop in the Game class and ends the game.
	 * @param faceUp the floor/face up stack
	 * @param faceDown the face down stack
	 * @return
	 */
	public boolean decideDraw(Stack<String> faceUp, Stack<String> faceDown)
	{
			if (faceUp.isEmpty() && faceDown.isEmpty())
			{
				System.out.println("Ran out of cards! Nobody wins!");
				return true;
			}
			
			/***
			 * The starting message of a player's turn
			 */
			System.out.print("\nIt's " + this.playerName + "'s turn! (Hand: " + this.playerHand + ") | Enter any key to continue: ");
			input.next();
			
			/***
			 * String result is used to determine if the player has won or, if not, will store the card value that must be thrown to the floor.
			 */
			String result = null;
			
			/***
			 * Checks if the floor is empty (Used to force player 1 to draw from the face down stack on turn 1).
			 */
			if (!faceUp.isEmpty())
			{
				System.out.println("The current floor card is: " + faceUp.peek());
				if (isWinningCard(faceUp))
				{
					System.out.print("\n" + this.playerName + " is going to draw from the floor pile! | Enter any key to continue: ");
					input.next();
					drawCard(faceUp);
					return true;

				} else
				{
					System.out.print("\n" + this.playerName + " is going to draw from the stack pile! | Enter any key to continue: ");
					input.next();
					result = drawCard(faceDown);
					
					/***
					 * Checks if the card results in a win or not
					 */
					if (!result.equals("won"))
					{
						faceUp.push(result);
						input.next();
					} else
					{
						return true;
					}
				}
			} else
			{
				System.out.print("\n" + this.playerName + " is going to draw from the stack pile! | Enter any key to continue: ");
				input.next();
				result = drawCard(faceDown);
				
				/***
				 * Gets the result from drawCard that determined if the player won.
				 */
				if (!result.equals("won"))
				{
					faceUp.push(result);
					input.next();
				} else
				{
					return true;
				}
			}
		return false;
	}
	
	/***
	 * A method that will draw a card (either from the floor or the faced down stack). This method should let us know if the player has winning cards after drawing.
	 * @param deck the deck the player is drawing from
	 * @param condition if a win condition is met or not
	 * @return
	 */
	private String drawCard(Stack<String> deck)
	{				
		String result;
		
		/***
		 *  Player has the winning cards
		 */
		if (isWinningCard(deck)) 
		{
			throwCard(deck.pop());
			System.out.println(this.playerName + " has won the game with a hand of " + this.playerHand + "!");
			return "won";
		}
		/***
		 * Player does not have the winning cards
		 */
		else
		{
			result = throwCard(deck.pop());
			System.out.println(this.playerName + " cannot win. They will throw the card: " + result + ".\nNew hand is : " + playerHand + "| Enter any key to continue:");
			return result;
		}		
	}
	
	/***
	 * A method to throw a card to the floor. Should throw based on the card types.
	 * @param drawnCard the drawnCard from either the floor or the face down deck
	 * @return
	 */
	private String throwCard(String drawnCard)
	{
		/***
		 * A Queue used to have a copy of the playerHand and adds the drawn card to that temporary hand
		 */
		Queue<String> determineThrownCard = new LinkedList<>();
		determineThrownCard.addAll(playerHand);
		determineThrownCard.offer(drawnCard);
		
		System.out.println(this.playerName + " drew a " + drawnCard);
		
		/***
		 * Variables used to help find the card that needs to be thrown
		 */
		String[] split = null;
		String[] findCard = {"", "", "", "", ""};
		Queue<String> tracker = new LinkedList<>();
		int[] cardVals = new int[5];

		/***
		 * Determines which cards that will need to be tested to be thrown or not.
		 */
		for (int i = 0; !determineThrownCard.isEmpty(); i++)
		{
			split = determineThrownCard.poll().split(" ");
			if (tracker.contains(split[2]))
			{	
				for (int j = 0; j < findCard.length; j++)
				{
					if (findCard[j].equals(split[2]))
					{
						findCard[j] = "";
						cardVals[j] = 0;
					}
				}
			} else
			{
				findCard[i] = split[2];
				cardVals[i] = Integer.parseInt(split[0]);
				tracker.offer(split[2]);
			}
		}
		
		/***
		 * Finds card to throw away
		 */
		String card = null;
		int highestVal = 0;
		for (int k = 0; k < findCard.length; k++)
			if (!findCard[k].equals(""))
			{
				if (highestVal < cardVals[k])
				{
					highestVal = cardVals[k];
					card = highestVal + " of " + findCard[k];
				}
			}
		
		/***
		 * Finds the card to throw away if there is a tie between # of card ranks (EX: 3 Diamonds, 2 spades: Determines which card to throw away between the two spades).
		 */
		if (tracker.size() == 2)
		{
			Stack<String> cardRank1 = new Stack<>();
			Stack<String> cardRank2 = new Stack<>();
			String card1 = tracker.poll();
			
			for (String e: playerHand)
			{
				if (e.substring(5).equals(card1) || e.substring(6).equals(card1))
					cardRank1.push(e);
				else
					cardRank2.push(e);
			}
			if (drawnCard.substring(5).equals(card1) || drawnCard.substring(6).equals(card1))
				cardRank1.push(drawnCard);
			else
				cardRank2.push(drawnCard);
			
			if (cardRank1.size() > cardRank2.size() && (cardRank1.size() != 1 && cardRank2.size() != 1))
			{
				split = cardRank2.pop().split(" ");
				int num1 = Integer.parseInt(split[0]);
				split = cardRank2.pop().split(" ");
				int num2 = Integer.parseInt(split[0]);
				
				if (num1 > num2)
					card = num1 + " of " + split[2];
				else
					card = num2 + " of " + split[2];
			} else if (cardRank2.size() > cardRank1.size() && (cardRank2.size() != 1 && cardRank1.size() != 1))
			{
				split = cardRank1.pop().split(" ");
				int num1 = Integer.parseInt(split[0]);
				split = cardRank1.pop().split(" ");
				int num2 = Integer.parseInt(split[0]);
				
				if (num1 > num2)
					card = num1 + " of " + split[2];
				else
					card = num2 + " of " + split[2];
			}

		}
		
		/***
		 * Check if player wins by sum.
		 */
		split = drawnCard.split(" ");
		int floorValue = Integer.parseInt(split[0]);
		int[] sum = new int[5];
		sum[4] = floorValue;
		Stack<String> playersTempHand = new Stack<>();
		playersTempHand.addAll(playerHand);

		for (int i = 0; i < playerHand.size(); i++)
		{
			split = playersTempHand.pop().split(" ");
			sum[i] = Integer.parseInt(split[0]);
		}
		
		sum = addsToTwenty(sum);
		if (sum != null) {
			playersTempHand.addAll(playerHand);
			playersTempHand.add(drawnCard);
			playerHand.clear();
			while (playerHand.size() != 4)
			{
				int counter = 0;
				split = playersTempHand.pop().split(" ");
				for (int i = 0; i < sum.length; i++)
				{
					if (sum[counter] == Integer.parseInt(split[0]))
					{
						playerHand.add(split[0] + " of " + split[2]);
						break;
					} else
						counter++;
				}				 
			}
		}
		
		/***
		 * If thrown card is in player hand, it will remove it and add the drawn card.
		 */
		if (playerHand.contains(card))
		{
			playerHand.remove(card);
			playerHand.add(drawnCard);
		} 
		return card;
	}
	
	/***
	 *  Checks if the floor card would allow the player to win
	 * @param deck the deck the player is drawing from (floor or face down)
	 * @return
	 */
	private boolean isWinningCard(Stack<String> deck) 
	{
		/***
		 * Floor/Stack Card
		 */
		boolean won = false;
		String[] splitCard = deck.peek().split(" ");
		int floorValue = Integer.parseInt(splitCard[0]);
		String floorRank = splitCard[2];
		
		/***
		 * Player's Hand
		 */
		Stack<String> playersTempHand = new Stack<>();
		playersTempHand.addAll(playerHand);
		int[] isTwenty = new int[5];
		isTwenty[4] = floorValue;
		int sameType = 0;	// Checks if the player wins by same type of card (wins if this value is equal to 3)
		
		/***
		 * Loop that is used to check if either win condition is met
		 */
		for (int i = 0; i < playerHand.size(); i++)
		{
			splitCard = playersTempHand.pop().split(" ");
			isTwenty[i] = Integer.parseInt(splitCard[0]);
			
			if (splitCard[2].equals(floorRank))
				sameType++;
		}
		if (sameType == 3 || addsToTwenty(isTwenty) != null) // Checks if a win condition is met
			won = true;		
		
		return won;
	}

	/***
	 * Checks if the 4 of the player's card equals 20, leading to a win.
	 * @param array an array that holds the card value of each card in the player's hand + the drawn card 
	 * @return
	 */
	private int[] addsToTwenty(int[] array)
	{
		for (int i = 0; i < array.length; i++)
			for (int j = i + 1; j < array.length; j++)
				for (int k = j + 1; k < array.length; k++)
					for (int l = k + 1; l < array.length; l++)
						if (array[i] + array[j] + array[k] + array[l] == 20)
						{
							int[] ans = {array[i], array[j], array[k], array[l]};
							return ans;
						}
		return null;
	}
	
	/***
	 * Checks if the player's current hand is a winning hand.
	 * @return
	 */
	private boolean isWinningHand() 
	{
		/***
		 * Variables used to determine if the player currently has a winning hand
		 */
		Stack<String> winningHand = new Stack<>();
		winningHand.addAll(playerHand);
		String[] splitCard = null;
		String[] splitSecondCard = null;
		int[] isTwenty = new int[4];
		String firstCard = "!";	// Checks if the player wins by same type of card (wins if this value is equal to 3)
		String secondCard = "-";
		
		for (int j = 0; j < 2; j++)
		{
			splitCard = winningHand.pop().split(" "); // Gets first card
			
			splitSecondCard = winningHand.pop().split(" "); // Gets second card
			
			isTwenty[j] = Integer.parseInt(splitCard[0]); // Sends the card value to the array
			
			if (splitCard[2].equals(splitSecondCard[2]))
				if (firstCard.length() <= 1)
					firstCard = splitCard[2];
				else
					secondCard = splitCard[2];
		}
		if (firstCard.equals(secondCard) || addsToTwenty(isTwenty) != null)
			return true;
		
		return false;
	}

	/***
	 * Used to print the final hands of each players
	 */
	public void printHand()
	{
		System.out.print("\n" + this.playerName + "'s Final Hand: " + this.playerHand);
	}
}