package fpayanilstu.edu;

import java.io.Serializable;

/***
 * 
 * @author Fernando Payan
 * Main class controls the flow of execution
 */

public class MorseTree<E extends Comparable<E>> implements Serializable{
	protected Node<E> root;

	/***
	 * The inner class
	 * @param <E> the object type
	 */
	protected static class Node<E>
	{
		protected E data;
		protected Node<E> left;
		protected Node<E> right;
		
		// Default constructor for Node
		public Node(E data)
		{
			this.data = data;
		}
	}
	
	/***
	 * Default Constructor
	 * @param data | the data 
	 * @param leftSub | the left sub tree
	 * @param rightSub | the right sub tree
	 */
	public MorseTree(E data, MorseTree<E> leftSub, MorseTree<E> rightSub)
	{
		root = new Node(data);
		
		if (leftSub != null)
			root.left = leftSub.root;
		
		if (rightSub != null)
			root.right = rightSub.root;
	}
	
	/***
	 * Add starter method to add a character to the tree
	 * @param item | String that contains the line for the letters with codes
	 */
	public void add(E item)
	{
		String letter = ((String)item).substring(0, 1);
		root = add(root, item, letter);
	}
	
	/***
	 * Add recursive method used to add a character to the tree
	 * @param localRoot | Gets the root node
	 * @param item | The morse code for the letter
	 * @param letter | The letter that is being added to the tree
	 * @return | returns the letter
	 */
	private Node<E> add(Node<E> localRoot, E item, String letter) // Recursive Method
	{
		String code = ((String)item).substring(1);
		// If no node
		if (localRoot == null)
		{
			return new Node<E>(((E)letter));
		}		
		
		// If there is a root
		if (code.charAt(0) == '*') // Moves left
		{
			localRoot.left = add(localRoot.left, ((E)code), letter);
			return localRoot;
		}
		else if (code.charAt(0) == '-') // Moves Right
		{
			localRoot.right = add(localRoot.right, ((E)code), letter);
			return localRoot;
		}
		return localRoot;
	} 
	
	
	/***
	 * Decode starter method used to retrieve the character from the tree using the Morse code value.
	 * @param input | the user's input
	 * @return | returns the decoded letter
	 */
	public String decode(String input) // Starter Method
	{
		Node<E> letter = decode(root, input);
		return letter.data.toString();
	}
	
	/***
	 * Decode recursive method used to retrieve the character from the tree using the Morse code value.
	 * @param localRoot | Gets the root node
	 * @param input | The morse code for the letter
	 * @return | returns the decoded letter
	 */
	private Node<E> decode (Node<E> localRoot, String input)
	{
		if (input.length() == 0)
		{
			return localRoot;
		}
		
		// If there is a root
		if (input.charAt(0) == '*') // Moves left
		{
			return decode(localRoot.left, input.substring(1));
			
		}
		else if (input.charAt(0) == '-') // Moves Right
		{
			return decode(localRoot.right, input.substring(1));
		}
		return localRoot;
	}
}