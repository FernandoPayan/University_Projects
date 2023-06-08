import java.util.*;
/**
 * Authors: Fernando Payan, Zach Derose, and Shawn Cherry
 * File made by Zach DeRose, to minimize DFA
 */
public class minimizeDFA {
    public static toDFA minimize(toDFA dfa) {
        // Step 1: Eliminate unreachable states
        Set<Integer> reachableStates = new HashSet<>();
        findReachableStates(dfa, dfa.initialState, reachableStates);
        // Step 2: Partition states into accepting and non-accepting
        Set<Integer> acceptingStates = new HashSet<>(dfa.finalStates);
        Set<Integer> nonAcceptingStates = new HashSet<>(reachableStates);
        nonAcceptingStates.removeAll(acceptingStates);
        List<Set<Integer>> partition = new ArrayList<>();
        partition.add(acceptingStates);
        partition.add(nonAcceptingStates);
        // Step 3: Refine the partition using the Myhill-Nerode Theorem
        boolean changed;
        do {
            changed = false;
            for (int i = 0; i < partition.size(); i++) {
                Set<Integer> group = partition.get(i);
                List<Set<Integer>> newGroups = new ArrayList<>();
                for (Integer state : group) {
                    boolean found = false;
                    for (Set<Integer> newGroup : newGroups) {
                        Integer representative = newGroup.iterator().next();
                        if (areStatesEquivalent(dfa, state, representative, partition)) {
                            newGroup.add(state);
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        Set<Integer> newGroup = new HashSet<>();
                        newGroup.add(state);
                        newGroups.add(newGroup);
                    }
                }
                if (newGroups.size() > 1) {
                    changed = true;
                    partition.remove(i);
                    partition.addAll(i, newGroups);
                }
            }
        } while (changed);
        // Step 4: Merge equivalent states and construct the minimized DFA
        toDFA minimizedDFA = new toDFA();
        minimizedDFA.numStates = partition.size();
        minimizedDFA.sigmaVals = dfa.sigmaVals;
        for (Set<Integer> group : partition) {
            int newState = minimizedDFA.transition.size();
            if (group.contains(dfa.initialState)) {
                minimizedDFA.initialState = newState;
            }if (!Collections.disjoint(group, dfa.finalStates)) {
                minimizedDFA.finalStates.add(newState);
            }
            Map<Character, List<Integer>> newTransitions = new HashMap<>();
            Integer representative = group.iterator().next();
            for (Character symbol : dfa.sigmaVals) {
                List<Integer> targetStates = dfa.transition.get(representative).get(symbol);
                List<Integer> newTargetStates = new ArrayList<>();
                for (Integer targetState : targetStates) {
                    newTargetStates.add(findGroupIndex(targetState, partition));
                }
                newTransitions.put(symbol, newTargetStates);
            }
            minimizedDFA.transition.add(newTransitions);
        }
        return minimizedDFA;
    }
    private static void findReachableStates(toDFA dfa,int state,Set<Integer>reachableStates){//Method for eliminating nonreachable states, recursively
        if (!reachableStates.contains(state)) { //nonreachable being states the only have outputs rather than a way to get to
            reachableStates.add(state);
            for (Character symbol : dfa.sigmaVals) {
                List<Integer> nextStates = dfa.transition.get(state).get(symbol);
                for (Integer nextState:nextStates) {
                    findReachableStates(dfa,nextState,reachableStates);
                }
            }
        }
    }
    private static boolean areStatesEquivalent(toDFA dfa, int state1, int state2, List<Set<Integer>> partition) {
        for (Character symbol : dfa.sigmaVals) { //Checks if states are indistinguishable so we can group and remove them
            List<Integer> nextStates1 = dfa.transition.get(state1).get(symbol);
            List<Integer> nextStates2 = dfa.transition.get(state2).get(symbol);
            if (nextStates1.size() != nextStates2.size()) {
                return false;
            }
            for (int i = 0; i < nextStates1.size(); i++) {
                if (findGroupIndex(nextStates1.get(i), partition) != findGroupIndex(nextStates2.get(i), partition)) {
                    return false;
                }
            }
        }
        return true;
    }
    private static int findGroupIndex(int state, List<Set<Integer>> partition) {
        for (int i = 0; i < partition.size(); i++) { //helper method for finding grouped states that can be merged
            if (partition.get(i).contains(state)) {
                return i;
            }
        }
        return -1; // Shouldn't happen if the state is reachable
    }
    public static void printMinimizedDFA(toDFA minimizedDFA) { //For printing the new minimized DFA. Not too important too code
        System.out.println("|Q|: " + minimizedDFA.numStates); //Follows required format
        System.out.print("Sigma: ");
        for (Character symbol : minimizedDFA.sigmaVals) {
            System.out.print(" " + symbol + "  ");
        }
        System.out.println("\n----------------------------------------");
        for (int i = 0; i < minimizedDFA.numStates; i++) {
            System.out.print("  " + i + ": ");
            for (Character symbol : minimizedDFA.sigmaVals) {
                System.out.print(" " + minimizedDFA.transition.get(i).get(symbol) + "  ");
            }
            System.out.println();
        }
        System.out.println("----------------------------------------");
        System.out.println("Initial State: " + minimizedDFA.initialState);
        System.out.print("Accepting State(s): ");
        for (int i = 0; i < minimizedDFA.finalStates.size(); i++) {
            System.out.print(minimizedDFA.finalStates.get(i));
            if (i < minimizedDFA.finalStates.size() - 1) {
                System.out.print(", ");
            }
        }
        System.out.println();
    }
}
//Zach DeRose
