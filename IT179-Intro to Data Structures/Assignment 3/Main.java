package fpayanilstu.edu;

import java.util.Scanner;

/***
 * 
 * @author fernando payan
 *
 */

public class Main {

	/***
	 * Controls the flow of the program.
	 */
	public static void main(String[] args) {
		/***
		 * Global variables and creation of Polynomial linked lists.
		 */
		Scanner input = new Scanner(System.in);
		String userInput;
		char cont = 'y';
		Polynomial<Term>list1;
		Polynomial<Term>list2;
		System.out.println("Welcome to the Polynomial Addition Program.");

		/***
		 * This while loop keeps the options displayed after each selection until the user does not enter 'y'.
		 */
		while (cont == 'y') {
			System.out.println("Please enter your first polynomial: ");
			userInput = input.nextLine();
			list1 = new Polynomial(userInput); 
			
			System.out.println("Please enter your second polynomial: ");
			userInput = input.nextLine();
			list2 = new Polynomial(userInput); 
			
			System.out.println("\nThe sum is: ");
			list1.addPolynomial(list2);	

			System.out.print("\nWould you like to add two more polynomials? ");
			cont = input.next().charAt(0);
			input.nextLine(); 

			if (cont == 'n')
				System.out.println("\nThank you for using the Polynomial Addition Program.");
		}
		input.close();
		System.exit(0);
	}
}