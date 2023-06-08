import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.HashMap;
import java.util.Collections;

public class parse {
    
    
    public void parseDFA(toDFA graph2, String argsString) throws FileNotFoundException{
        File file = new File(argsString);
        Scanner sc = new Scanner(file);
        //toDFA graph = new toDFA(sc);
        //toDFA graph2 = graph.convertToDFA();

        //------------------
        int currState;
        Map<Character, List<Integer>> currMap; 
        int initialState;
        boolean throughTop = false;
        int lineCounter = 0;
        String inputString;
        int inputStringLength;
        char currLetter;
        int lastState;
        int numYes = 0;
        int numNo = 0;

        
        

        initialState = graph2.initialState;
        currState = initialState;
        lastState = initialState;
        //initialState =

        

        //graph2.printDFA();
        //System.out.println(s);
        //graph.transitionPrint();

        

        //-------------------------------------
        file = new File(argsString);
        sc = new Scanner(file);
        //List<Map<Character, List<Integer>>> transition = graph.transition;
        //System.out.println(transition);
        while (sc.hasNextLine()) {
            lineCounter++;
            inputString = sc.nextLine();
            if (inputString.contains("Input strings")) {
                throughTop = true;
                lineCounter++;
            }

            if (throughTop) {
                boolean keepGoing = true;
                currState = initialState;
                while (sc.hasNextLine()) {
                    initialState = 0;
                    currState = initialState;
                    inputString = sc.nextLine();
                    boolean tru = false;
                    inputStringLength = inputString.length();
                    for (int i = 0; i < inputStringLength; i++) {
                        currLetter = inputString.charAt(i);

                        // HEAVY LOGIC

                        if (currLetter == 'c') {
                            currState = graph2.transition.get(currState).get(currLetter).get(0);
                        } else if (currLetter == 'b') {
                            currState = graph2.transition.get(currState).get(currLetter).get(0);
                        } else if (currLetter == 'a') {
                            currState = graph2.transition.get(currState).get(currLetter).get(0);
                        } else if (currLetter == 'd') {
                            currState = graph2.transition.get(currState).get(currLetter).get(0);
                        } else {
                            System.out.println("False NOT VALID LETTER");
                            tru = false;
                        }

                        if (keepGoing == false) {
                            tru = false;
                            break;
                        }
                    }

                    for (int i = 0; i < graph2.finalStates.size(); i++) {
                        if (currState == graph2.finalStates.get(i)) {
                            tru = true;
                        }
                    }

                    if (tru == true) {
                        System.out.print("Yes ");
                        numYes++;
                    } else {
                        System.out.print("No ");
                        numNo++;
                    }
                    tru = false;
                    keepGoing = true;

                    if (!sc.hasNextLine()) {
                        break;
                    }
                }
                System.out.println("\nYes: " + numYes + " No: " + numNo);
            }
}

        //------------------


        sc.close();
    }
        
    

    
        



}
