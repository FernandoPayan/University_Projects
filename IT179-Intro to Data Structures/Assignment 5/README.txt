This programming assignment is broken up into two parts. The first part was a Linux exercise and has little to no programming work. The second part has programming and it is a Morse Code program.

Classes:
  •	MorseTree
    o	Includes:
      	The node inner class.
      	Default constructor.
      	Add methods to add a character to the tree. (starter method and a recursive method)
      	Decode methods to retrieve the character from the tree using the Morse code value. (starter method and a recursive method)
  •	MainClass.java
    o	Includes
      	The main method
  •	Controls the flow of the program
  •	Prompts the user for the encoded message
      	buildTree method
  •	builds the tree using the file the contains the letters and their codes
      	decode method
  •	decodes the message entered by the user

Sample output:
Please enter encoded message or stop to exit: .... . .-.. .-.. ---
The decoded message is: hello
Please enter encoded message or stop to exit: hello
Please enter a valid Morse Code!
Please enter encoded message or stop to exit: stop
Thank you for using our decoder!
