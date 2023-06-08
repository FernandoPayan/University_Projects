This sample program is for a hospital based on the below UML Diagram requirements:

Patient
-------------------
-id: int
-fName: String
-lName: String
-age: int
-pcr: boolean
-------------------
+Patient(int, String, String, int)
+getPcr(): Boolean
+setPcr(Boolean pcr):void
+getId(): int
+setId(int id): void
+getFName(): String
+setFName(String fName):void
+getLName(): String
+setLName(String lName): void
+getAge(): int
+setAge(int age): void
+treat(): String
+toString(): String


Covid19Patient (inherits Patient)
-------------------
-temperature: double
-------------------
+Covid19Patient(int, String, String, int, double)
+getTemp(): double
+setTemp(double temp):void
+treat(): String
+toString(): String

RegularPatient (inherits Patient)
-------------------
-mainSymptom: String
-------------------
+RegularPatient(int, String, String, int,String)
+treat(): String
+toString(): String

Files:
MainClass:
  Will have the main method:
  •	It will control the flow of your program.
  •	It will create an arraylist of patients (only one arraylist should exist in your program)
  •	It will prompt the user to select one of the following options (these options will keep being displayed after each selection until we exit the program):
    1.	Admit a patient 
        The program will ask if the PCR test result is negative or positive and that will decide what type of patient we have and what information we will ask for. 
    2.	Print patient information
        It will print all the patient information using the toString Method
    3.	Submit a PCR test result
        It will ask for the patient id and update the pcr test value for that patient. Any regular patient who gets a positive PCR test should be considered a covid19 patient from that moment. (Hint: copy old object data to the new object) a covid19 patient will be discharged if the PCR test result was negative.
    4.	Do rounds
        •	It will ask you to enter the current temperature for every Covid19 patient.
        •	It will treat all the patients currently admitted to the hospital and print out each patient’s id and what is the recommended treatment 
    5.	Discharge patient
        It will remove the patient from our system. Before we discharge a patient, we need to make sure that they have a negative PCR test result
    6.	Exit 

Patient:
  Uses the uml diagram above to create the abstract class.
Covid19Patient
  Uses the uml diagram above to create the class
    •	The treat method will return Remdesivir for patients over 65 who have a fever (temperature is over 37.5) otherwise, it will be fluids and Tylenol. Any patient who has a temperature over 40, regardless of age, should be receiving Dexamethasone
    •	the toString method in the Covid19Patient class to return a String similar to the sample below:
        Id: 3
        Full name: Shukri Abotteen
        Age: 70
        Temperature: 38
        PCR test result: Positive
        Treatment: Remdesivir
RegularPatient
  Use the uml diagram above to create the class
    •	The treat method will return Amoxicillin for patients with upper respiratory tract infections (symptoms include coughing, runny nose, or stuffy nose). Patients who have hypertension will be taking ACE inhibitors. All other patients will be on IV fluids.
    •	the toString method in the RegularPatient class will return a String similar to the sample below:
        Id: 4
        Full name: Shukri Abotteen
        Age: 70
        Main Symptom: Vomiting
        PCR test result: Negative
        Treatment: IV fluids







