package fpayanilstu.edu;

import java.util.InputMismatchException;
import java.util.Scanner;

public class MainClass {

	public static void main(String[] args) {
		// Declaration of object StudentReport
		StudentReport report = new StudentReport();
		
		// Global Variables
		int promptNum = 0;		
		String userInput;
		
		while (true) { // This loop keeps the prompts displayed after each selection until we exit the program.
			Scanner input = new Scanner(System.in);
			
			try { // If user writes something that is not an integer, it will catch the InputMisMatchException and restart the program.
			System.out.println("Please select an option. Enter the number associated with option to select it:\n1. Enter the file name to process\n2. Print a list of all students\n3. Generate a report card for a specific student\n4. Display statistics\n5. Exit");
				
			promptNum = input.nextInt();
			if (promptNum <= 0 || promptNum> 5) { // If user selects a value outside of the given prompt values, it will ask user to try again.
				System.out.println("Invalid range. Please select the integer value associated with the given prompt you'd like to select.");
			}
			input.nextLine();
			} catch (InputMismatchException e) {
				System.out.println("Entered value is not an integer. Please select the integer value associated with the given prompt you'd like to select.");
				main(null);
			}
			
			try { // If user incorrectly types the file name, it will catch the NullPointerException and restart
				switch (promptNum) {
				case 1: { // Option 1: Enter the file name to process
					System.out.print("Enter the file name including the extension: ");
					userInput = input.nextLine();
					report.readFile(userInput);
					break;
					}
				case 2: { // Option 2: Print a list of all students
					System.out.println("\n" + report.printStudents(report.getStudents()));
					break;
				}
				case 3: { // Option 3: Generate a report card for a specific student
					System.out.print("Enter the name of the student: ");
					report.writeFile(input.nextLine());
					break;
					}
				case 4: { // Option 4: Display statistics
					report.getStatistics(report.getGrades());
					break;
					}
				case 5: { // Option 5: Exit
					System.out.println("Terminating program...");
					input.close();
					System.exit(0);
					break;
					}
				}
				System.out.print("\n"); // Creates a space between the last prompt and the next.
			} catch (NullPointerException e) {
				System.out.println("No file is detected. Please enter prompt 1 to enter a file name to process.\n");
			}
		}
	}
}