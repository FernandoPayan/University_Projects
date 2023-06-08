This program is a simulation of a simple card game.

The game uses only the numbered cards of the regular playing cards deck. (i.e.: 1 through 10 of hearts, spades, clubs, and diamonds)
The game can be played by a minimum of 2 players and up to 5 players. Each player will start with 4 cards and the goal is to collect 4 cards of the same type (for example all your cards are hearts) or have the total of the cards equal to 20. 
The game will start by shuffling the cards and handing each player 4 cards. If one of the players has all their cards of the same type or the total of the numbers is equal to 20 that player wins.
If that’s not the case, the first player starts by drawing a card from the remaining cards which should be placed in a stack face down. After drawing that card, if they have 4 cards of the same type or if 4 of the cards, they are holding are adding up to 20 they win. Otherwise, they will have to throw a card to the floor face up. The next player will look at the card on the floor. If picking up that card will let them win, they will pick that card and win the game. Otherwise they will pick a card from the faced down stack of cards. Again, if after drawing that card they have 4 cards of the same type or if 4 of the cards, they are holding are adding up to 20 they win. If not, they will throw a card to the floor -face up- on top of the other faced up card(s).
The game will keep going until there is a winner or no more cards are left on the faced down stack of cards.

Classes:
1.	A Game class which will include:
    •	A linked list to store the unshuffled cards
    •	A stack of the faced down cards 
    •	A stack of the faced-up cards that are thrown to the floor
    •	A queue of the players
    •	A shuffle method 
        o	Randomly adds the cards from the linked list to the faced down stack
    •	Constructors:
        o	Takes the player names
        o	Calls the shuffle method
        o	Create the player objects
    •	A method to simulate the game

2.	A Player class which will include:
    •	A data structure to store the cards a player is holding.
    •	A constructor that sets the player name and takes the initial 4 cards.
    •	A method that will decide whether to draw a card from the stack or the floor
        o	You should only draw from the floor if that card makes the player win.
    •	A method that will draw a card (either from the floor or the faced down stack).
        o	This method should let us know if the player has winning cards after drawing
    •	A method to throw a card to the floor.
        o	Should throw based on the card types (see example below)

3.	Main class:
    •	Will have the main method
    •	Controls the flow of execution 
    •	Takes input to start the simulation
    •	Create the game and start the simulation
