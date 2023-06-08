package fpayanilstu.edu;

import java.util.Scanner;

/***
 * 
 * @author fernando payan
 *
 * @param <E> the data type
 */
public class Polynomial<E> {
	
	/***
	 * Private inner class Node with two instance variables termData of type Term
	 * and next of type Node.
	 * @param <Term> the data type
	 */
	private static class Node<Term> {
		/***
		 * Two private instance variables of type Node
		 */
		private Term termData;
		private Node<Term> next;
		
		/***
		 * Default constructor
		 * @param termData the term data
		 */
		private Node(Term termData) {
			this.termData = termData;
		}
		
		/***
		 * @param termData the term data
		 * @param next the next node
		 */
		private Node(Term termData, Node<Term> next) {
			this.termData = termData;
			this.next = next;
		}
	}
	/***
	 * Two private variables of type Node: termsHead and termsTails.
	 */
	private Node<Term> termsHead = null;
	private Node<Term> termsTail = null;
	
	/***
	 * Default constructor
	 */
	public Polynomial() {
		this.termsHead = termsHead;
		this.termsTail = termsTail;
	}

	/***
	 * Constructor that accepts a String representing a polynomial and initializes the object
	 * to represent that polynomial.
	 * @param polynomial
	 */
	public Polynomial(String polynomial) {
		getPolynomial(polynomial);
	}
	
	/***
	 * Method that adds a Term to the end of the list of terms.
	 * @param term the term value
	 */
	public void addTermToPolynomial(Term term) {
		Node<Term> current = this.termsHead;
		if (current == null)
			current = new Node<Term>(term, current);
		 else
		{
			while (current.next != null)
			{
				current = current.next;
			}
			current.next = new Node<Term>(term, current.next);
			termsTail = current.next;
		}
	}
	
	/***
	 * toString that returns a String representing the polynomial.
	 */
	public String toString() {
		StringBuilder polySentence = new StringBuilder();
		Node<Term> current = this.termsHead;

		polySentence.append(current.termData);
		current = current.next;

		while (current != null) 
		{
			if (current.termData.getCoefficient() < 0) 
			{
				polySentence.append(" " + current.termData.toString());
				current = current.next;
				
			} else
			{ 
				polySentence.append((" + " + current.termData.toString()));
				current = current.next;
			}

		}
		return polySentence.toString();
	}
	
	/***
	 * Method that accepts a Polynomial object as a parameter and returns a Polynomial object
	 * representing the sum of the calling object and the parameter.
	 * @param polyObject
	 */
	public void addPolynomial(Polynomial<Term> polyObject) 
	{ 
		/***
		 * Global variables and creation of Node<Term> longPoly, shortPoly, checkHeads, and Polynomial result.
		 */
		Node<Term> longPoly = termsHead;
		Node<Term> shortPoly = polyObject.termsHead;
		Node<Term> checkHeads = termsHead;
		int coefResult = 0;
		int expResult = 0;
		boolean largestPoly = true;
		boolean findTerm = true;
		Polynomial<Term> result = new Polynomial<>();
		
		/***
		 * While loop that finds the longest polynomial between the two polynomials and sets longPoly to the longest one.
		 */
		while (longPoly != null || shortPoly != null)
		{
			/***
			 * If 2nd polynomial list is longer than 1st polynomial list
			 */
			if (longPoly == null) 
			{
				shortPoly = termsHead;
				longPoly = polyObject.termsHead;
				largestPoly = false;
				checkHeads = longPoly;
				break;
				
				/***
				 * If 1st polynomial list is longer than 2nd polynomial list
				 */
			} else if (shortPoly == null) 
			{
				longPoly = termsHead;
				shortPoly = polyObject.termsHead;
				break;	
			}
			longPoly = longPoly.next;
			shortPoly = shortPoly.next;
		}
		/***
		 * If both polynomials are the same size
		 */
		if (longPoly == null && shortPoly == null)
		{
			longPoly = termsHead;
			shortPoly = polyObject.termsHead;
		}

		/***
		 * While loop that is used to iterate through each term
		 */
		while (longPoly != null) 
		{
			/***
			 * Skips terms with coefficient of 0.
			 */
			if (longPoly.termData.getCoefficient() == 0)
				longPoly = longPoly.next;
			
			/***
			 * This will iterate through each Node<Term> in our second polynomial.
			 */
			while (shortPoly != null)
			{
				Term newTerm = null;
				/***
				 *  If exponents are =, adds the terms
				 */
				if (longPoly.termData.getExponent() == shortPoly.termData.getExponent())
				{
					coefResult = longPoly.termData.getCoefficient() + shortPoly.termData.getCoefficient();
					expResult = longPoly.termData.getExponent();
					newTerm = new Term(coefResult, expResult);
					/***
					 *  If it's the first data type, it sets it to be termsHead (first term in node).
					 */
					if (result.termsHead == null)
					{
						result.termsHead = new Node<Term>(newTerm);
						break;
					} else
					{
						if (newTerm.getCoefficient() == 0)
							break;
						else 
						{
						result.addTermToPolynomial(newTerm);
						
						if (largestPoly)
							shortPoly = polyObject.termsHead;
						else
							shortPoly = termsHead;
						break;
						}
					}
				} 
				/***
				 * Determines if Term goes at the end of the list or at the front based on it's exponent.
				 */
				else if (longPoly.termData.getExponent() > shortPoly.termData.getExponent())
				{
					if (longPoly.termData.getExponent() >= checkHeads.termData.getExponent())
					{
						result.termsHead = new Node<Term>(longPoly.termData, result.termsHead);
						if (largestPoly)
							shortPoly = polyObject.termsHead;
						else
							shortPoly = termsHead; 
						break;
					}
					else
					{
						newTerm = new Term(longPoly.termData.getCoefficient(), longPoly.termData.getExponent());
						result.addTermToPolynomial(newTerm);
						if (largestPoly)
							shortPoly = polyObject.termsHead;
						else
							shortPoly = termsHead; ;
						break;
					}
					
				} else
				{
					/***
					 * Used to check if there is a term with no like terms.
					 */
					Node<Term> temp = null;
					if (largestPoly == false)
						temp = polyObject.termsHead;
					else
						temp = termsHead;
					
					while (temp != null)
					{
						if (shortPoly.termData.getExponent() == temp.termData.getExponent())
						{
							findTerm = false;
							break;
						} 

						findTerm = true;
						temp = temp.next;
					}
					shortPoly = shortPoly.next;
				}
			}
			coefResult = 0;
			expResult = 0;
			longPoly = longPoly.next;
		}
		
		/***
		 * If there is a term with no like terms, it will add it onto Polynomial result and sort it correctly.
		 */
		if (findTerm == true)
		{
			if (largestPoly)
			{
				shortPoly = polyObject.termsHead;
				longPoly = termsHead;
			} else
			{
				shortPoly = termsHead; 
				longPoly = polyObject.termsHead;
			}		
			
			
			Node<Term> current = result.termsHead;
			Polynomial<Term> updateResult = new Polynomial<>();
			int count = 0;
			boolean alreadyAdded = false;
			while (shortPoly != null)
			{
				while (current != null)
				{
					if (shortPoly.termData.getExponent() == current.termData.getExponent() && alreadyAdded == false)
					{
						updateResult.addTermToPolynomial(current.termData);
						alreadyAdded = true;
						current = result.termsHead;
						break;
					} else if (shortPoly.termData.getExponent() > current.termData.getExponent())
					{
						if (updateResult.termsHead == null)
							updateResult.termsHead = new Node<Term>(result.termsHead.termData);
						else
							updateResult.addTermToPolynomial(shortPoly.termData);
						count++;
						break;
					} else
					{
						if (updateResult.termsHead == null)
							updateResult.termsHead = new Node<Term>(result.termsHead.termData);
						else if (alreadyAdded == false)
							updateResult.addTermToPolynomial(current.termData);
						else if (shortPoly.termData.getExponent() + current.termData.getExponent() == 0)
							updateResult.addTermToPolynomial(current.termData);
						current = current.next;
					} 
				}
				shortPoly = shortPoly.next;
				current = result.termsHead;
			}
			result = updateResult;
			System.out.println(result.toString());
		} else
			System.out.println(result.toString());
	}
	
	/***
	 * Gets the Term of the polynomial
	 * @param index the position of the Term
	 * @return Term
	 */
	private Term getTerm(int index) {
		Node<Term> term = this.termsHead;
		if (term == null)
			return null;
		else
			for (int i = 0; i < index && term != null; i++) 
			{
				term = term.next;
			}
		return term.termData;
	}
	
	/***
	 * Called upon by the Polynomial constructor that accepts a String and initializes the object.
	 * @param sentence the user input polynomial
	 */
	private void getPolynomial(String sentence) {
		Scanner s = new Scanner(sentence);
		StringBuilder coefficient = new StringBuilder();
		StringBuilder exponent = new StringBuilder();
		Node<Term> current = termsHead;
		int numOfNodes = 0;

		for (int i = 0; i < sentence.length(); i++)
		{
			/***
			 * Global variables
			 */
			int coef = 0;
			int exp = 0;
			char c = sentence.charAt(i);
			boolean breakWhile = false;
			boolean constant = false;
			
			if (s.hasNext()) 
			{
				/***
				 *  If first term is a positive value
				 */
				if ((Character.isDigit(sentence.charAt(0))|| Character.isAlphabetic(sentence.charAt(0))) && i == 0)
				{
					while (sentence.charAt(i) != 'x')
					{
						c = sentence.charAt(i);
						coefficient.append(c);
						i++;	
					} if (sentence.charAt(0) == 'x') 
					{
						coef = 1;
						coefficient.append(coef);
					}
				}
				/***
				 * Positive operand
				 */
				if (sentence.charAt(i) == '+') 
				{
					i = i + 2;
					while (breakWhile == false && i < sentence.length()) 
					{
						
						if (sentence.charAt(i) != 'x')
						{
							c = sentence.charAt(i);
							coefficient.append(c);
							i++;
						} else
							breakWhile = true;
						
						/***
						 * Constant check
						 */
						if (i == sentence.length()) {
							exponent.append(exp);
							constant = true;
							break;
						}
					}
					breakWhile = false;
				}	
				if (constant != true) 
				{
					/***
					 *  Negative operand
					 */
					if (sentence.charAt(i) == '-' && i < sentence.length()) 
					{
						if (sentence.charAt(i + 1) == ' ')
						{
							i = i + 2;
							coefficient.append('-');
							while (sentence.charAt(i) != 'x') 
							{
								c = sentence.charAt(i);
								coefficient.append(c);
								i++;		
								
								/***
								 * Constant check
								 */
								if (i == sentence.length()) {
									exponent.append(exp);
									constant = true;
									break;
								}
							}
						}
						else 
						{
							while (sentence.charAt(i) != 'x')
							{
								c = sentence.charAt(i);
								coefficient.append(c);
								i++;	
							}	
							coef = Integer.parseInt(coefficient.toString());
						}
					}
				}
				if (constant != true)
				{
				
						/***
						 * When loop reaches 'x' in the sentence.
						 */
						if (sentence.charAt(i) == 'x' && i < sentence.length()) 
						{
							if (coefficient.charAt(0) == '-' && coefficient.length() <= 1)
							{
								coefficient.append('1');
							}
							coef = Integer.parseInt(coefficient.toString());
							exp = 1;
							
							/***
							 * Check if Term has an exponent or not
							 */
							if (i + 1 != sentence.length())
							{
								if (sentence.charAt(i + 1) == '^')
								{
									i = i + 2;
									
									while (breakWhile == false && i < sentence.length())
									{
										if (sentence.charAt(i) != ' ')
										{
											c = sentence.charAt(i);
											exponent.append(c);
											exp = Integer.parseInt(exponent.toString());
											i++;
										} else 
										{
											exp = Integer.parseInt(exponent.toString());
											breakWhile = true;
										}
										
										/***
										 * Checks if value is x^#
										 */
										if (coef == 1)
										{
											exp = Integer.parseInt(exponent.toString());
											breakWhile = true;
										}
									}
								} else
								{
									exponent.append(exp);
									i++;
								}
									
							} else
								exponent.append(exp);
						}
					}

				/***
				 * Creates a new Term using the values from coef and exp.
				 */
				if (termsHead == null) // Adds first Term to head
				{
					termsHead = new Node<Term>(new Term(coef, exp), termsHead);
					coefficient.delete(0, coefficient.length());
					exponent.delete(0, exponent.length());
					current = termsHead;
					numOfNodes++;
					
				/***
				* Checks if end of Polynomial and, if so, sets termTails equal to last term.
				*/
				} else if (i == sentence.length() || constant == true) 
				{
					coef = Integer.parseInt(coefficient.toString());
					exp = Integer.parseInt((exponent.toString()));
					termsTail = new Node<Term>(new Term(coef, exp), null);
					coefficient.delete(0, coefficient.length());
					exponent.delete(0, exponent.length());
					while (current.next != null)
						current = current.next;
					current.next = termsTail;
				} else
				{
					coefficient.delete(0, coefficient.length());
					exponent.delete(0, exponent.length());
					addTermToPolynomial(new Term(coef, exp));
					numOfNodes++;
				}
			} 
		} 
	} 
}