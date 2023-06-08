package fpayanilstu.edu;

/***
 * 
 * @author Fernando Payan
 *
 */
public abstract class Patient {
	/***
	 * Declaration of private variables
	 */
	private int id;
	private String fName;
	private String lName;
	private int age;
	private boolean pcr;
	
	
	/***
	 * Constructs a Patient with id, first and last name, and age.
	 * @param id the id
	 * @param fName the first name
	 * @param lName the last name
	 * @param age the age
	 */
	public Patient(int id, String fName, String lName, int age) { 
		this.id = id;
		this.fName = fName;
		this.lName = lName;
		this.age = age;
	}

	/*** Getters and Setters
	 * Retrieves the next pcr
	 * @return the pcr value
	 */
	public boolean getPcr() {
		return pcr;
	}
	
	/***
	 * Sets the pcr value
	 * @param pcr the pcr test result
	 */
	public void setPcr(boolean pcr) {
		this.pcr = pcr;
	}
	
	/***
	 * Retrieves the next id
	 * @return the id number
	 */
	public int getId() {
		return id;
	}
	
	/***
	 * Sets the id value
	 * @param id the id number
	 */
	public void setId(int id) {
		this.id = id;
	}
	
	/***
	 * Retrieves the first name
	 * @return the first name
	 */
	public String getfName() {
		return fName;
	}
	
	/***
	 * Sets the first name
	 * @param fName the first name
	 */
	public void setfName(String fName) {
		this.fName = fName;
	}
	
	/***
	 * Retrieves the last name
	 * @return the last name
	 */
	public String getlName() {
		return lName;
	}
	
	/***
	 * Sets the last name
	 * @param lName the last name
	 */
	public void setlName(String lName) {
		this.lName = lName;
	}
	
	/***
	 * Retrieves the age
	 * @return the age 
	 */
	public int getAge() {
		return age;
	}
	
	/***
	 * Sets the age
	 * @param age the age
	 */
	public void setAge(int age) {
		this.age = age;
	}
	
	/***
	 * End of Getters and Setters
	 */
	
	/***
	 * Creates an abstract treat method.
	 * @return String
	 */
	public abstract String treat();
	
	/***
	 * Creates a toString method that return's a patient's ID, full name, and age.
	 * @return String
	 */
	public String toString() {
		
		return "ID: " + this.getId()
		+ " Full name: " + this.getfName() + " " + this.getlName()
		+ " Age: " + this.getAge();
	}
}
