package fpayanilstu.edu;
/***
 * 
 * @author Fernando Payan
 *
 */
public class Covid19Patient extends Patient{
	/***
	 * Declaration of private variables
	 */
	private double temperature;
	
	/***
	 * Constructs a Covid19Patient with id, first and last name, age, and temperature.
	 * @param id the id
	 * @param fName the first name
	 * @param lName the last name
	 * @param age the age
	 * @param temperature the temperature
	 */
	public Covid19Patient(int id, String fName, String lName, int age, double temperature) {
		super(id, fName, lName, age);
		this.temperature = temperature;
	}
	
	/***
	 * Retrieves the temperature
	 * @return temperature
	 */
	public double getTemperature() {
		return temperature;
	}
	
	/***
	 * Sets the temperature
	 * @param temperature the temperature
	 */
	public void setTemperature(double temperature) {
		this.temperature = temperature;
	}
	
	/***
	 * The treat method will return Remdesivir for patients over 65 who have a fever (temperature is over 37.5) otherwise, it will be fluids and Tylenol. 
	 * Any patient who has a temperature over 40, regardless of age, should be receiving Dexamethasone
	 * @return String
	 */
	public String treat() {
		StringBuilder treatment = new StringBuilder();
		if (this.getAge() > 65 && this.temperature > 37.5) 
			 treatment.append("Remdesivir");
		else 
			treatment.append("Fluids and Tylenol");
		if (this.temperature > 40) 
			if (treatment.length() > 0)
				treatment.append(" and Dexamethasone");
			else
				treatment.append("Dexamethasone");
		return treatment.toString();
	}

	/***
	 * Creates a toString method that returns a Covid19Patient's ID, full name, age, temperature, PCR test result, and their treatment.
	 * @return String
	 */
	public String toString() {
		
		return "Id: " + this.getId() 
		+ "\nFull name: " + this.getfName() + " " + this.getlName() 
		+ "\nAge: " + this.getAge() 
		+ "\nTemperature: " + this.getTemperature() 
		+ "\nPCR test result: Positive/" + this.getPcr()
		+ "\nTreatment: " + this.treat();
	}
}
