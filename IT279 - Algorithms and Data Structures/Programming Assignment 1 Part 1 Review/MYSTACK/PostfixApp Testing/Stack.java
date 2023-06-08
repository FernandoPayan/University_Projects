/**

 * Single Linked-List based implementation of a Stack class using int data

 * 

 * @author Fernando Payan

 */

public class Stack 

{

	private class Node 

	{

		private int data;

		private Node next;

		

		private Node() {

			this.data = data;

		}

		

		private Node(int data, Node next)

		{

			this.data = data;

			this.next = next;

		}

	}

	

	Node head;

	public Stack() 

	{

		this.head = head;

	}



    /**

     * Determines whether stack is empty

     * 

     * @return true if empty, false otherwise

     */

	public boolean isEmpty()

	{

		if (head == null)

			return true;

		return false;

	}

	

    /**

     * Get value from top of stack Precondition: the stack is not empty

     * 

     * @return value at top of stack

     */

	public int top()

	{

		if (!isEmpty())

			return head.data;

		return -1;

	}

	

    /**

     * Add value to top of stack

     * 

     * @param value item to push onto stack

     */

	public void push(int value) 

	{

		head = new Node(value, head); // This updates the head with the pushed value and points to the previous head as the next item in the stack.

	}

	

    /**

     * Remove value from top of stack, returning the removed value Precondition: the

     * stack is not empty

     * 

     * @return removed value

     */

    public int pop() 

    {

    	if (!isEmpty())

    	{

    		Node current = head;

        	head = head.next;

        	int result = current.data;

        	current = null; // This deletes the node so we don't have any unused nodes taking up memory

        	return result;

    	}

    	return -1;

    }

}