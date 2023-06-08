/***
 * @author Fernando Payan
 * 
 */
package fpayanilstu.edu;

import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.Scanner;

public class MainClass {

	/***
	 * Controls the flow of the program.
	 */
	public static void main(String[] args) {
		/***
		 * Global variables and creation of ArrayList patients.
		 */
		ArrayList<Patient> patients = new ArrayList<>();
		Scanner input = new Scanner(System.in);
		int promptNum = 0;
		String userInput;
		
		/***
		 * This while loop keeps the options displayed after each selection until we exit the program.
		 */
		while (true) {
			
			/***
			 * Try and Catch method prompts the user to select one of the following options. 
			 */
			try {	
				System.out.println("Please select an option. Enter the number associated with option to select it:"
						+ "\n1. Admit a patient"
						+ "\n2. Print patient information"
						+ "\n3. Submit a PCR test result"
						+ "\n4. Do rounds"
						+ "\n5. Discharge patient"
						+ "\n6. Exit");
				
				promptNum = input.nextInt();
				
				/***
				 * If user selects a value outside of the given prompt values, it will ask user to try again.
				 */
				if (promptNum <= 0 || promptNum> 6)
					System.out.println("Invalid range. Please select the integer value associated with the given prompt you'd like to select.");

				input.nextLine();
			} catch (InputMismatchException e) {
				System.out.println("Entered value is not an integer. Please select the integer value associated with the given prompt you'd like to select.");
				main(null);
			};

				switch (promptNum) {
				/***  Option 1: Admit a patient
				 * The program will ask if the PCR test result is negative or positive then run the "admitPatient" method.
				 */
				case 1: { 
					System.out.println("Was the patient's PCR test result positive or negative? (Use '+' for positive and '-' for negative).");
					userInput = input.next();	
					admitPatient(userInput, patients);
					
					break;
					}
				/*** Option 2: Print patient information
				 * The program checks if there are any patients admitted to the hospital and, if there are, It will print all the patient information using the toString Method.
				 */
				case 2: {
					if (patients.size() == 0) 
						System.out.println("No patients are currently in the hospital! Please enter a patient through prompt 1!");
					else
						System.out.print("Please enter the patient's ID number: ");
						int id = input.nextInt();
						if (id >= patients.size() || id < 0) {
							System.out.println("Patient does not exist, please try again.\n");
						} else {
							if (patients.get(id) instanceof RegularPatient) 
								System.out.println(((RegularPatient)patients.get(id)).toString() + "\n");
							else if (patients.get(id) instanceof Covid19Patient)
								System.out.println(((Covid19Patient)patients.get(id)).toString() + "\n");
							}
						break;
						}
				/*** Option 3: Submit a PCR test result
				 * The program checks if there are any patients admitted to the hospital and, if there are, it will run the "submitPCR" method.
				 */
				case 3: {
					if (patients.size() == 0) 
						System.out.println("No patients are currently in the hospital! Please enter a patient through prompt 1!");
					else
						submitPCR(patients);
					break;
					}
				/*** Option 4: Do rounds
				 * The program checks if there are any patients admitted to the hospital and, if there are, it will run the "doRounds" method.
				 */
				case 4: {
					if (patients.size() == 0) 
						System.out.println("No patients are currently in the hospital! Please enter a patient through prompt 1!");
					else
						doRounds(patients);
						break;
					}
				/***Option 5: Discharge patient
				 * The program checks if there are any patients admitted to the hospital and, if there are, it will run the "discharge" method.
				 */
				case 5: {
					if (patients.size() == 0) 
						System.out.println("No patients are currently in the hospital! Please enter a patient through prompt 1!");
					else
						discharge(patients);
					break;
					}
				/*** Option 6: Exit
				 * It will exit the program
				 */
				case 6: {
					System.out.println("Terminating program...");
					input.close();
					System.exit(0);
					}				
			System.out.println("\n");
			
			} 
		} 
	} 
	/***
	 * Based on the user's input of whether the PCR test result is positive or negative, it will decide what type of patient we have and what information we will ask for.
	 * @param pcr the PCR test result
	 * @param patients the ArrayList patients
	 */
	public static void admitPatient(String pcr, ArrayList<Patient> patients) {
		String firstN;
		String lastN;
		int age;
		double temp;
		String symp;
		@SuppressWarnings("resource")
		Scanner admitInput = new Scanner(System.in);
		try {
			if (pcr.equals("+")) { // If positive, patient is considered a COVID-19 patient from that moment.
				System.out.print("Please enter the patient's first name: ");
				firstN = admitInput.next();
				System.out.print("\nPlease enter the patient's last name: ");
				lastN = admitInput.next();
				System.out.print("\nPlease enter the patient's age: ");
				age = admitInput.nextInt();
				System.out.print("\nPlease enter the patient's temperature: ");
				temp = admitInput.nextDouble();
				
				Patient covidPatient = new Covid19Patient(patients.size(), firstN, lastN, age, temp);
				covidPatient.setPcr(true);
				
				patients.add(covidPatient);
				}
			
			else if (pcr.equals("-")) {// If negative, patient is considered a regular patient from that moment.
				System.out.print("Please enter the patient's first name: ");
				firstN = admitInput.next();
				System.out.print("\nPlease enter the patient's last name: ");
				lastN = admitInput.next();
				System.out.print("\nPlease enter the patient's age: ");
				age = admitInput.nextInt();
				System.out.print("\nPlease enter the patient's main symptom: ");
				admitInput.nextLine();
				symp = admitInput.nextLine();
				
				Patient regularPatient = new RegularPatient(patients.size(), firstN, lastN, age, symp);
				regularPatient.setPcr(false);
				
				patients.add(regularPatient);
				}
			
			else { // Asks user to try again since they did not enter a correct option.
				System.out.println("Unrecognized character");
				}
		} catch (InputMismatchException e) {
			System.out.println("Input mismatch, please make sure to enter the values in the correct order next time: First Name, Last Name, Age, and Temperature. Press the space bar after each input.");
			main(null);
		}
	} 
	
	/***
	 *  This method will ask for the patient id and update the pcr test value for that patient. Any regular patient who gets a positive PCR test should be considered a covid19 patient from that moment.
	 * @param patients the ArrayList patients
	 */
	public static void submitPCR(ArrayList<Patient> patients) {
		@SuppressWarnings("resource")
		Scanner input = new Scanner(System.in);
		try {
			System.out.print("Please enter the Patient's ID: ");
			int id = input.nextInt();
			
			if (id >= patients.size() || id < 0) { // If the entered ID does not exist in the hospital, then it asks the user to try again.
				System.out.println("Patient does not exist, please try again.\n");
			} else {
				System.out.print("What is the patient's new PCR test value? (Enter 'true' for positive and 'false' for negative): ");
				boolean pcrVal = input.nextBoolean();
				
				if (pcrVal == true) { // If the PCR test result is positive, then it will update the patient to a Covid19Patient.
					System.out.print("Please enter the patient's temperature: ");
					double temp = input.nextDouble();
					patients.set(id, new Covid19Patient(patients.get(id).getId(), patients.get(id).getfName(), patients.get(id).getlName(), patients.get(id).getAge(), temp));
					
				} else if (pcrVal == false) { // If the PCR test result is negative, then it will update the patient to a RegularPatient.
					System.out.print("Please enter the patient's main symptom: ");
					input.nextLine();
					String symptom = input.nextLine();
					patients.set(id, new RegularPatient(patients.get(id).getId(), patients.get(id).getfName(), patients.get(id).getlName(), patients.get(id).getAge(), symptom));
				}
				patients.get(id).setPcr(pcrVal);
				System.out.println("Successfully updated patient " + patients.get(id).getfName() + "'s PCR test result!\n");
			}
			
		} catch (InputMismatchException e) {
			System.out.println("Input mismatch, please give the correct input type next time.");
		}
	} 
	
	/***
	 * This method will ask the user to enter the current temperature for every Covid19 patient.
	 * It will treat all the patients currently admitted to the hospital and print out each patient’s id and what is the recommended treatment.
	 * @param patients the ArrayList patients
	 */
	public static void doRounds(ArrayList<Patient> patients) {
		@SuppressWarnings("resource")
		Scanner input = new Scanner(System.in);

		for (int i = 0; i < patients.size(); i++) {
			if (patients.get(i) instanceof Covid19Patient) {
				System.out.print("Please enter the current temperature for Patient " + patients.get(i).getfName() + " " + patients.get(i).getlName() + ": ");
				double temp = input.nextDouble();
				((Covid19Patient)patients.get(i)).setTemperature(temp);
				((Covid19Patient)patients.get(i)).treat();
				System.out.println(patients.get(i).getfName() + " " + patients.get(i).getlName() + "'s recommended treatment is: " + ((Covid19Patient)patients.get(i)).treat());
			} else if (patients.get(i) instanceof RegularPatient) {
				((RegularPatient)patients.get(i)).treat();
				System.out.println(patients.get(i).getfName() + " " + patients.get(i).getlName() + "'s recommended treatment is: " + ((RegularPatient)patients.get(i)).treat());

			}
		}
		System.out.println("All patients have been treated.");
	} 
	
	/***
	 * It will remove the patient from our system. Before we discharge a patient, we need to make sure that they have a negative PCR test result.
	 * @param patients the ArrayList patients
	 */
	public static void discharge(ArrayList<Patient> patients) {
		@SuppressWarnings("resource")
		Scanner input = new Scanner(System.in);
		try {
			System.out.print("Please enter the Patient's ID whom you'd want to discharge: ");
			int id = input.nextInt();
			
			if (id >= patients.size() || id < 0) { // If the entered ID does not exist in the hospital, then it asks the user to try again.
				System.out.println("Patient does not exist, please try again.\n");
				
			} else if (patients.get(id).getPcr() != false) { //
				System.out.println("Patient's PCR test result is positive, they cannot be discharged until their PCR test result is negative.\n");
			} else if (patients.get(id).getPcr() != true) {
				System.out.println("Patient's PCR test result is negative, patient satifies requirement. Patient " + patients.get(id).getfName() + " " + patients.get(id).getlName() + " was successfully discharged.\n");
				patients.remove(id);
			}
		} catch (InputMismatchException e) {
			System.out.println("Input mismatch, please give the correct input type next time.");
		}
	} 
	
}