/**author: fpayan
 *  This program generates an NFA from a given file and converts to a DFA
 */

import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.HashMap;
import java.util.Collections;

public class toDFA
{
    public int numStates; /* Stores the number of states */
    public int initialState; /* Stores the initial state */
    public List<Integer> finalStates; /* Stores the final states */
    public List<Character> sigmaVals; /* Stores the Sigma values */
    public List<Map<Character, List<Integer>>> transition; /* Stores the transition states */

    /* Default Constructor */
    public toDFA()
    {
        this.numStates = 0;
        this.initialState = 0;
        this.finalStates = new ArrayList<>();
        this.sigmaVals = new ArrayList<>();
        this.transition = new ArrayList<>();
    }

    /* Constructor to build the NFA */
    public toDFA(Scanner sc)
    {
        /* 1.) Read in the number of states */
        String line = sc.nextLine();

        /* 1a.) Store the number of states into numStates */
        numStates = Integer.parseInt(line.replaceAll("[\\D]", ""));

        /* 2.) Read in the Sigma values */
        line = sc.nextLine();

        /* 2a.) Trim it so that it only contains the sigma values */
        line = line.replace("Sigma: ", "");
        
        /* 2b: Store the sigma values in an array */
        sigmaVals = new ArrayList<>();
        for (char c: line.toCharArray())
            if (c != ' ')
                sigmaVals.add(c);

        /* 2c. Add in the lambda variable */
        sigmaVals.add(' ');

        /* 3. Skip the line so we can read the transition table */
        sc.nextLine();
        
        /* 3a. Iterate through the NFA table and read in the transition states */
        transition = new ArrayList<>();

        for (int i = 0; i < numStates; i++)
        {
            /* Read in the line */
            line = sc.nextLine();
            
            /* Create a HashMap to store the transition states */
            Map<Character, List<Integer>> trans_state = new HashMap<>();

            /* Interate through the characters and store the states based on that character */
            for (Character input : sigmaVals)
            {
                /* Create a list of integers to store the list of states */
                List<Integer> states = new ArrayList<>();

                /* Parse the string so that we only get the states */
                line = readTransitionStates(line, states);

                /* Add to our hash map */
                trans_state.put(input, states);
            }

            /* Add the list of states to our transitions list */
            transition.add(trans_state);
        }

        /* Skip the line so we can read the initial state */
        sc.nextLine();

        /* 3b. Read in the initial state of the NFA */
        initialState = Integer.parseInt(sc.nextLine().replace("initial State: ", ""));

        /* 3c. Read in the final states */
        line = sc.nextLine().replace("Accepting State(s): ", "");

        String[]splitStr = line.split(",");
        finalStates = new ArrayList<>();

        /* Add the final states */
        for (String state : splitStr)
            finalStates.add(Integer.parseInt(state));
    }

    /* Helper method used to convert the NFA to a DFA */
    public toDFA convertToDFA()
    {
        /* 1. Construct the DFA object */
        toDFA dfa = new toDFA();
        
        /* 2. Construct our lists of unique and current sets, and add it to our set of unique lists */
        List<List<Integer>> uniqueSets = new ArrayList<>();
        List<Integer> currentSet = findLambdaStates(initialState);

        uniqueSets.add(currentSet);

        /* 3. Create the list of inputs */
        List<Character> inputs = new ArrayList<>();
        inputs.addAll(this.sigmaVals);

        /* 3a. Remove the Lambda transition */
        inputs.remove(Character.valueOf(' '));

        /* 4. Iterate until we reach the end */
        int nfaStateIndex = 0, dfaStateIndex = 0;
        
        while (currentSet != null)
        {
            /* Create a HashTable to store the states we're tracking */
            Map<Character, List<Integer>> inputStateMap = new HashMap<>();

            /* Iterate through each character in our inputs */
            for (Character input : inputs)
            {
                List<Integer> setOfStates = new ArrayList<>();

                /* Get the lambda transitions */
                for (Integer currentState : currentSet)
                    for (Integer n : this.transition.get(currentState).get(input))
                        findLambdaStates(n, setOfStates);

                /* Sort the set of states */
                Collections.sort(setOfStates);

                /* Store the translated list of states */
                List<Integer> dfaSet = new ArrayList<>();

                if (uniqueSets.contains(setOfStates))
                    dfaSet.add(uniqueSets.indexOf(setOfStates));
                else
                {
                    uniqueSets.add(++dfaStateIndex, setOfStates);

                    dfaSet.add(dfaStateIndex);
                }

                /* Map the set to the sigma variable */
                inputStateMap.put(input, dfaSet);
            }

            /* Add the states to our DFA */
            dfa.numStates++;
            dfa.transition.add(inputStateMap);

            /* 5. Iterate through the list of final states to find any potential accepting states */
            for (int finalState : finalStates)
            {
                /* If it contains the final state, then we need to consider this set as an accepting state */
                if (currentSet.contains(finalState))
                    if (!(dfa.finalStates.contains(finalState)))
                    {
                        dfa.finalStates.add(nfaStateIndex);
                        break;
                    }
            }

            /* Check if we continue or stop reading */
            if (++nfaStateIndex >= uniqueSets.size())
                currentSet = null;
            else
                currentSet = uniqueSets.get(nfaStateIndex);
        }

        dfa.sigmaVals = inputs;

        return dfa;
    }

    /* Helper method used to print out the DFA */
    public void printDFA()
    {
        System.out.println("Sigma: ");

        /* Print out the sigma vals */
        for (Character input : sigmaVals) 
            System.out.print(input.toString() + " ");
        
        System.out.println("\n----------------------------------------");

        /* Print out the DFA table */
        for (int i = 0; i < numStates; i++) 
        {
            System.out.print("     " + i + ":   ");
            for (int j = 0; j < sigmaVals.size(); j++) 
                System.out.print(transition.get(i).get(sigmaVals.get(j)).toString().replace("[", "").replace("]", "") + "\t  ");
            System.out.println("");
        }

        System.out.println("----------------------------------------");
        
        /* Print the initial state for the DFA */
        System.out.println(initialState + ":\tInitial State");

        /* Print out the accepting states for the DFA */
        System.out.println(finalStates.toString().replace("[","").replace("]","") + ": Accepting State(s)");
    }

    /* Helper method used to read in the transition states from the NFA table */
    private String readTransitionStates(String line, List<Integer> target)
    {
        /* Parse the line */
        line = line.substring(line.indexOf('{') + 1, line.length());
        
        /* Check that we didn't reach the end of the set */
        if (!(line.charAt(0) == '}'))
        {
           /* Boolean used to check for commas */
            boolean hasCommas;

            /* While loop to add in every state we find */
            while (hasCommas = line.indexOf(',') < line.indexOf('}') && line.indexOf(',') > 0)
            {
                /* Add the state */
                target.add(Integer.parseInt(line.substring(0, line.indexOf(','))));

               /* Parse the line */
                line = line.substring(line.indexOf(',') + 1, line.length());
            }

            /* Add to our list */
            if (!hasCommas)
                target.add(Integer.parseInt(line.substring(0, line.indexOf("}"))));
        }
        
        /* Return the parsed string */
        return line.substring(line.indexOf("}") + 1, line.length());
    }

    /* Caller method that returns list of integers of states we can reach through lambda */
    private List<Integer> findLambdaStates(int state)
    {
        /* Construct the list of totals */
        List<Integer> reachableStates = new ArrayList<>();

        /* Call our lambda method */
        findLambdaStates(state, reachableStates);

        /* Return the list */
        return reachableStates;
    }

    /* Recursive function used to find out what states are reachable through lambda */
    private void findLambdaStates(int state, List<Integer> reachableStates)
    {
        /* Check that the list does not contain our current state */
        if (!reachableStates.contains(state))
        {
            /* If not, add the state and it's transitions */
            reachableStates.add(state);

            for (Integer inState : transition.get(state).get(' '))
                findLambdaStates(inState, reachableStates);
        }
    }
}