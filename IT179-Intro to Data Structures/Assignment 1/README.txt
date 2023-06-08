This is a program that reads and processes a .csv file that holds the grades of all students in a class. 

MainClass:
  Will have the main method:
    i.	It will control the flow of your program.
    ii.	It will prompt the user to select one of the following options (these options will keep being displayed after each selection until we exit the program):
      1.	Enter the file name to process
      2.	Print a list of all students
          This will print out all the student names to the console.
      3.	Generate a report card for a specific student
          a.	If selected it will ask the user to enter the name of the student
          b.	It will then call the writeFile method to generate the report card
      4.	Display statistics.
          a.	It will print out the average of the class, the highest total and the lowest total.
      5.	Exit
StudentReport
 i.	Instance variables:
      1.	filename: a String that will hold the name of the file we want to read.
      2.	grades: a double 2d array that will hold the grades for all the students.
      3.	students: a 1d String array that will hold the names of all the students. 
      4.	gradedItems: a 1d String array that will hold the names of all the graded items in the file
 ii.	We have the following methods:
      1.	A constructor that will take the file name and instantiate the arrays.
      2.	readFile:
          •	it will read the .csv file and store the values in the arrays we have.
      3.	writeFile:
          •	it will generate a report card for the selected student and save it as a .txt file. The name of the file should be the student’s name.
          •	Your report file that contains:
             i.	The student’s name
             ii.	Their grade in every exam, assignment with the appropriate label. For example: Exam one:  50.
             iii.	Their Total.
             iv.	Their letter grade. (90 and above A, 80-89 B,70-79 C, 60-69 D, below 69 F)
