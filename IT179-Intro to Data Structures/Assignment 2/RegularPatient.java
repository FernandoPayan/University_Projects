package fpayanilstu.edu;

/***
 * 
 * @author Fernando Payan
 *
 */

public class RegularPatient extends Patient{
	/**
	 * Declaring private variables
	 */
	private String mainSymptom;
	
	/***
	 * Constructs a RegularPatient with id, first and last name, age, and main symptom.
	 * @param id the id
	 * @param fName the first name
	 * @param lName the last name
	 * @param age the age
	 * @param mainSymptom the main symptom
	 */
	public RegularPatient(int id, String fName, String lName, int age, String mainSymptom) {
		super(id, fName, lName, age);
		this.mainSymptom = mainSymptom;
	}
	
	/***
	 * The treat method will return Amoxicillin for patients with upper respiratory tract infections (symptoms include coughing, runny nose, or stuffy nose). 
	 * Patients who have hypertension will be taking ACE inhibitors. 
	 * All other patients will be on IV fluids.
	 * @return String
	 */
	public String treat() {
		this.mainSymptom = this.mainSymptom.toLowerCase();
		if (this.mainSymptom.equals("coughing") || this.mainSymptom.equals("runny nose") || this.mainSymptom.equals("stuffy nose")) 
			return "Amoxicillin";
		else if (this.mainSymptom.equals("hypertension"))
			return "ACE inhibitor";
		
		return "IV fluids";
	}

	/***
	 * Creates a toString method that returns a RegularPatient's ID, full name, age, main symptom, PCR test result, and their treatment.
	 * @return String
	 */
	public String toString() {
		return "Id: " + this.getId() 
		+ "\nFull name: " + this.getfName() + " " + this.getlName() 
		+ "\nAge: " + this.getAge() 
		+ "\nMain Symptom: " + this.mainSymptom 
		+ "\nPCR test result: Negative/" + this.getPcr() 
		+ "\nTreatment: " + this.treat();
	}
}
