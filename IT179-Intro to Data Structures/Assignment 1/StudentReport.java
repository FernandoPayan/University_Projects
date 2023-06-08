package fpayanilstu.edu;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.text.DecimalFormat;
import java.util.Scanner;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class StudentReport extends MainClass{
	
	// Declaring instance variables
	private String filename;
	private Integer [][] grades;
	private String [] students;
	private String[] gradedItems;

	// Getters and Setters
	public String getFilename() {
		return filename;
	}


	public void setFilename(String filename) {
		this.filename = filename;
	}


	public Integer[][] getGrades() {
		return grades;
	}


	public void setGrades(Integer[][] grades) {
		this.grades = grades;
	}


	public String[] getStudents() {
		return students;
	}


	public void setStudents(String[] students) {
		this.students = students;
	}


	public String[] getGradedItems() {
		return gradedItems;
	}


	public void setGradedItems(String[] gradedItems) {
		this.gradedItems = gradedItems;
	}
	// End of Getters and Setters
	
	// Default constructor
	public StudentReport() { 
		this.filename = "Grades.csv";
		this.grades = new Integer [20][9];
	}

	public void readFile(String file) { // This will read the .csv file and store the values in the arrays we have.
		// Declaring local variables for method
		int rows = 0;
		int columns = 0;
		ArrayList <String> string = new ArrayList<> ();
		
		try { // Scans and reads the inputted file
			Scanner fileReader = new Scanner(new File(file));
			while (fileReader.hasNext()) { 
				String line = fileReader.nextLine();
				
				// Counts rows and columns
				String[] lnArray = line.split(",");
				rows++;
				columns = lnArray.length;	
				
				// Gets value of next token in the file
				Scanner scan = new Scanner(line);
				scan.useDelimiter(",");
				while (scan.hasNext()) {							
					string.add(scan.next());
				}
				scan.close();
			}
		} catch (FileNotFoundException e) { // If user runs into FileNotFoundException, it will display a message to prompt the user to try again and calls the "main" method in MainClass to restart the program.
			System.out.print("\nFile not found, please try again:\n\n");
			main(null);
			
		}
		// End of Reading File
		
		// Stores the values of the file into a 2-D String Array which will be used to update the values for the other arrays.
		String[][] arrayFile = new String[rows][columns];
		int counter = 0;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				arrayFile[i][j] = string.get(counter);
				counter++;
			}
		}
		
		// Sets the dimensions of the arrays
		this.grades = new Integer[rows - 1][columns - 1];
		this.students = new String[rows - 1];
		this.gradedItems = new String[columns - 1];
		
		updateValues(arrayFile);
		
		System.out.println("Successfully read file!");
	}	

	public void writeFile(String stuName) { // This will generate a report card for the selected student and save it as a .txt file with the title of the .txt file as the student's name.
		try { // used for FileWriter to catch any IOException errors.
			// Declaring local variables in the method.
			FileWriter fw = new FileWriter(stuName + ".txt", false);
			PrintWriter pw = new PrintWriter(fw);
			int total = 0;
			char finalGrade = '-';
			// for loop that checks if the inputted name matches with a name in the file. 
			for (int i = 0; i < this.students.length; i++) {
				if (stuName.equals(this.students[i])) { // If the entered name is in the file, it will append the results to the .txt file.
					System.out.println("Student Found! Please open the file " + stuName + ".txt for the results.");
					pw.append("Name: " + stuName + "\n");
					for (int j = 0; j < this.grades[i].length; j++) { // Prints the 
						pw.print(this.gradedItems[j] + ": " + grades[i][j] + "\n");
						total += grades[i][j];
					}
					// Calculates Grade for the student
					if (total >= 90)
						finalGrade = 'A';
					else if (total >= 80 && total < 90)
						finalGrade = 'B';
					else if (total >= 70 && total < 80)
						finalGrade = 'C';
					else if (total >= 60 && total < 70)
						finalGrade = 'D';
					else if (total < 60) {
						finalGrade = 'F';
					}
					
					// Print total and final grade for student
					pw.print("Total:" + total + " Final Grade: " + finalGrade);			
					break;
				}
				// If the student's name is not found in the array, it will let the user know that the student was not found in the file.
				if (i >= this.students.length - 1) {
					System.out.println("Student not found! Student is not in file or was typed incorrectly. Please try again.");
				}
			}
			pw.close();
		} catch (IOException e) {
			e.printStackTrace();

		}	
	}
	
	public String printStudents(String[] array) { // This method is used to print the students name to the console.
		// Declaring local variables for the method
		StringBuilder newString = new StringBuilder();
		
		// for loop that appends each item in the array (student array) to a string. Method will return the string which is list of students.
		for (int i = 0; i < array.length; i++) 
			newString.append(array[i] + " | ");
		return newString.toString();
	}
	
	public void getStatistics(Integer[][] gradeFile) { // This method is used to calculate the average, highest total, and lowest total in the file.
		// Declaring local variables for the method
		Integer[] gradeArray = new Integer[gradeFile.length];
		double average = 0;
		DecimalFormat f = new DecimalFormat("#.##"); // used to format class average
		
		// for loop that adds all the grades in the file to a 1-D Integer array which is used to find the min and max.
		for (int i = 0; i < gradeFile.length; i++) {
			int sum = 0;
			for (int j = 0; j < gradeFile[i].length; j++) {
				sum += gradeFile[i][j];
			}
			gradeArray[i] = sum;
			average+= sum;
		}
		int smallestValue = Collections.min(Arrays.asList(gradeArray));
		int largestValue = Collections.max(Arrays.asList(gradeArray));
		average = average / gradeFile.length;
		System.out.println("\nClass Average: " + f.format(average) + "%" + "\tHighest Total: " + largestValue + "\tLowest Total: " + smallestValue);
	}
	
	public void updateValues(String[][] fileArray) { // This method is used to update the values in the instance arrays.
		// Updates the values for the array "gradedItems".
		for (int j = 0; j < this.gradedItems.length; j++) {
			this.gradedItems[j] = fileArray[0][j + 1];
		}
		
		// Updates the values for the array "students".
		for (int k = 0; k < this.students.length; k++) {
			this.students[k] = fileArray[k + 1][0];
		}
		
		// Gets all digit values from the file and appends it to "values".
		ArrayList<Integer> values = new ArrayList<>();
		for (int i = 0; i < fileArray.length; i++) {
			for (int j = 0; j < fileArray[i].length; j++) {
				String str = fileArray[i][j];
				for (char c: str.toCharArray()) {
					if (Character.isDigit(c)) {
						values.add((Integer.parseInt(str)));
						break;
					} else if (Character.isLetter(c)) {
						break;
					}
				}
			}
		}
		// Gets the integers from the array "values" and adds them to the 2D array "grades". 
		int gradesTracker = 0;
		for (int i = 0; i < this.grades.length; i++) {
			for (int j = 0; j < this.grades[i].length; j++) {
				grades[i][j] = values.get(gradesTracker);
				gradesTracker++;
			}
		}
	}
}