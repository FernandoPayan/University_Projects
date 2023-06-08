/**

 * Program that requests postfix expressions from the user and evaluates them.

 * 

 * @author Fernando Payan

 */



import java.util.Scanner;

public class PostfixApp 

{

	public static void main(String[] args)

	{

		Scanner input = new Scanner(System.in);

		

		//Start of program

		System.out.println("Welcome to the Postfix App!\n");

		System.out.print("Enter Expression (Q to quit): ");

		String userInput = input.nextLine();

		// Check if the expression quits the program

		while (!userInput.contains("Q"))

		{

			Stack stack = new Stack();

			String[] splitStr = userInput.split("\\s+"); // Splits the string and separates each integer & operator.			

			for (String s: splitStr)

			{

				//Checks if the element is an operator. If it is, it will perform the arithmetic operation.

				if (s.contains("+") || s.contains("-") || s.contains("*") || s.contains("/") || s.contains("%"))

				{

					stack.push(computeValue(stack.pop(), stack.pop(), s));


				} else

				{

					stack.push(Integer.parseInt(s));

				}

			}

			System.out.println("Result: " + stack.top() + "\n");

			System.out.print("Enter Expression (Q to quit): ");

			userInput = input.nextLine();

		}

		System.exit(0);

	}

	

	public static int computeValue(int val1, int val2, String operator)

	{
		switch (operator)

		{

		case "+":
			return val2 + val1;

		case "-":
			return val2 - val1;

		case "*":
			return val2 * val1;

		case "/":
			return val2 / val1;

		case "%":
			return val2 % val1;

		}
        return (Integer)null;
	}

}