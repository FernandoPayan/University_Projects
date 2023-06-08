package fpayanilstu.edu;

/***
 * 
 * @author fernando payan
 *
 */
public class Term {
	/***
	 * Two private instance variables that store the coefficient and the exponent.
	 */
	private int coefficient;
	private int exponent;
	
	/*** Getters and Setters
	 * Retrieves the coefficient
	 * @return the coefficient value
	 */
	public int getCoefficient() {
		return coefficient;
	}
	
	/***
	 *  Sets the coefficient
	 * @param coefficient the coefficient of the term
	 */
	public void setCoefficient(int coefficient) {
		this.coefficient = coefficient;
	}
	
	/*** 
	 * Retrieves the exponent
	 * @return the exponent value
	 */
	public int getExponent() {
		return exponent;
	}
	
	/***
	 *  Sets the exponent
	 * @param exponent the exponent of the term
	 */
	public void setExponent(int exponent) {
		this.exponent = exponent;
	}
	/***
	 * End of Getters and Setters
	 */
	
	/***
	 * Constructor that takes the parameters for both instance variables
	 * @param coefficient the coefficient of the term
	 * @param exponent the exponent of the term
	 */
	public Term(int coefficient, int exponent) { 
		this.coefficient = coefficient;
		this.exponent = exponent;
	}
	
	/***
	 * a toString that returns the Term
	 */
	public String toString() {
		if (this.getCoefficient() == 1 && this.getExponent() > 1)
			return "x^" + this.getExponent();
		else if (this.getCoefficient() == 1 && this.getExponent() == 1)
			return "x";
		
		
		/***
		 * Exponent Check
		 */
		if (this.getExponent() == 0)
			return "" + this.getCoefficient();
		else if (this.getExponent() == 1)
			return this.getCoefficient() + "x";
		else
			return this.getCoefficient() + "x^" + this.getExponent();
	}
	
	/***
	 * Takes a Term as a parameter and returns a Term that is the sum of the calling object and the parameter.
	 * @param term the term
	 * @return the term value
	 */
	public Term addTerm(Term term) { 
		/***
		 * Checks if the sum of the two terms can be expressed as a single Term
		 */
		if (this.exponent != term.getExponent()) 
			return null; 
		else {
			Term addedTerm = new Term((term.getCoefficient() + this.coefficient), this.exponent);
			return addedTerm;
		}
	}
	
} 
