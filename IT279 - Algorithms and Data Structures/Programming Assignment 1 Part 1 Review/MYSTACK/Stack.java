/**
 * Array-based implementation of a Stack class using int data
 * 
 * @author Mary Elaine Califf
 */
public class Stack {

    private int[] data;
    private int topIndex = -1;

    /**
     * Default constructor
     */
    public Stack() {
        data = new int[100];
    }

    /**
     * Determines whether stack is empty
     * 
     * @return true if empty, false otherwise
     */
    public boolean isEmpty() {
        return topIndex == -1;
    }

    /**
     * Get value from top of stack Precondition: the stack is not empty
     * 
     * @return value at top of stack
     */
    public int top() {
        return data[topIndex];
    }

    /**
     * Add value to top of stack
     * 
     * @param value item to push onto stack
     */
    public void push(int value) {
        // if and exception unnecessary for linked list version
        if (topIndex + 1 < data.length - 1) {
            topIndex++;
            data[topIndex] = value;
        } else {
            throw new ArrayIndexOutOfBoundsException();
        }

    }

    /**
     * Remove value from top of stack, returning the removed value Precondition: the
     * stack is not empty
     * 
     * @return removed value
     */
    public int pop() {

        int value = data[topIndex];
        topIndex--;
        return value;
    }

}