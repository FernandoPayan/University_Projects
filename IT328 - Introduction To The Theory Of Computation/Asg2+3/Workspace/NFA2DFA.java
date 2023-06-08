/**
 * Authors: Fernando Payan, Zach Derose, and Shawn Cherry
 * Main file to execute NFA -> DFA, Minimize DFA, and read in the parsed strings
 */

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class NFA2DFA {
	public static void main(String[] args) throws FileNotFoundException {
        /* Check if user passed enough arguments */
        if (args.length != 1)
        {
            System.out.println("Incorrect. Usage: java NFA2DFA {filename}");
            System.exit(0);
        }
        
        /* Get the file from the command line */
        String nfaFile = args[0];

        try
        {
            Scanner nfaScanner = new Scanner(new File(nfaFile));
            
            /* Read the NFA file from args[0] */
            toDFA nfa = new toDFA(nfaScanner);
            
            /* Print the header */
            System.out.println("NFA " + nfaFile + " to DFA " + nfaFile.charAt(0) + ".dfa:");

            /* convert the NFA to the DFA*/
            toDFA dfa = nfa.convertToDFA();

            /* Print the DFA */
            dfa.printDFA();  
            
            /* Print out the parsing results */
            System.out.println("\nParsing results of strings attached in " + nfaFile + ":");
            parse p = new parse();
            p.parseDFA(dfa, nfaFile);


            /* Minmize the DFA */
            minimizeDFA min = new minimizeDFA();
            toDFA minDFA = min.minimize(dfa);

            /* Print out the Minimized DFA table */
            System.out.println("\nMinimized DFA from " + nfaFile.charAt(0) + ".dfa:");
            minDFA.printDFA();

            /* Print out the parsing results */
            System.out.println("\nParsing results of strings attached in " + nfaFile + ":");
            p.parseDFA(minDFA, nfaFile);

            /* Print out the number of states that changed */
            System.out.println("\n|Q| " + dfa.numStates + " -> " + minDFA.numStates); /* INSERT NUMBER OF STATES FOR MINIMIZED DFA HERE @ Zach */

            /* Close the Scanners */
            nfaScanner.close();
        }
        /* If the file is not found, throw a FileNotFoundException */
		catch (FileNotFoundException e)
		{ 
			System.out.println("Could not locate " + nfaFile + ". Please restart the program and make sure the file is in the same directory.");
			System.exit(0);
		} 	
    }
}