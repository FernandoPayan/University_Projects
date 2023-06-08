/**
 * Tester for simple Stack class that holds integers -- done as a program
 * because some students may not be familiar with JUnit
 * Based on a C++ version by Nick Dunne
 * 
 * @author Mary Elaine Califf
 */

public class TestStack {

    public static void main(String[] args) {
        // Collection of test names
        String[] allTests = {
                "addOneItem", "removeOneItem", "addManyItems",
                "addAndRemoveManyItems", "initialIsEmpty", "isEmptyAfterAddAndRemove"
        };

        System.out.println("EMPTY CONSTRUCTOR TEST RUNNING...");

        boolean constructor = testEmptyConstructor();

        // If the empty constructor test passes, run the rest of the tests.
        if (constructor) {
            if (args.length > 0) {
                String testName = args[0];
                // Run the test
                if (testName != "constructor") {
                    runSpecificTest(testName);
                }
            } else {
                boolean passedPreviousTest = true;
                int testIndex = 0;

                // Since a test name wasn't passed in, we will run all the tests in sequential
                // passing order
                while (passedPreviousTest && testIndex < allTests.length) {
                    passedPreviousTest = runSpecificTest(allTests[testIndex++]);
                }

                if (passedPreviousTest) {
                    System.out.println("Congrats! You have passed all of the required tests (" + allTests.length
                            + "). Please don't forget to double check your code for correct implementation, design, and clarity.");
                } else {
                    System.out.println("You have failed the last test that ran (" + testIndex + "/" + allTests.length
                            + "). Therefore, additional tests will not be run.\n"
                            + "Please fix your implementation so that the failing test passes, and run again once you believe that you've fixed that functionality.");
                }
            }
        } else {
            System.out.println("Constructor test failed, additional tests will not be run.");
        }
    }

    // RUNNER: Will run one test at a time, based on the test name given.
    private static boolean runSpecificTest(String testName) {
        if (testName.equals("addOneItem")) {
            // Call test
            System.out.println("ADD ONE ITEM (Needs top) TEST RUNNING...");
            return testAddOneItem();
        } else if (testName.equals("removeOneItem")) {
            // Call test
            System.out.println("REMOVE ONE ITEM TEST RUNNING...");
            return removeOneItem();
        } else if (testName.equals("addManyItems")) {
            // Call test
            System.out.println("ADD MULTIPLE ITEMS TEST RUNNING...");
            return testAddManyItems();
        } else if (testName.equals("addAndRemoveManyItems")) {
            // Call test
            System.out.println("ADD & REMOVE MULTIPLE ITEMS TEST RUNNING...");
            return testAddAndRemoveManyItems();
        } else if (testName.equals("initialIsEmpty")) {
            // Call test
            System.out.println("INITIAL ISEMPTY TEST RUNNING...");
            return testInitialIsEmpty();
        } else if (testName.equals("isEmptyAfterAddAndRemove")) {
            // Call test
            System.out.println("IS EMPTY AFTER ADD AND REMOVE TEST RUNNING...");
            return testIsEmptyAfterAddAndRemove();
        }

        else {
            System.err.println("===TEST NAME NOT FOUND, HELP===");
            System.exit(1);
        }
        return false;
    }

    // Check contents and print out any differences, removes items from the stack
    private static boolean validateAndPrintContents(Stack stack, int[] items, boolean validateList) {
        // Instantiate vars to store test result
        boolean passedTests = true;
        String testResult = "";

        try {
            // Check each item in the list
            if (validateList && items.length > 0) {

                for (int i = 0; i < items.length; i++) {

                    // Check each item
                    if (stack.top() != items[items.length - i - 1]) {
                        // Print a failed result
                        testResult += "\n\tstack[" + i + "] = " + stack.top() + "; SHOULD BE "
                                + items[items.length - i - 1]
                                + "\n";

                        // Some validation failed
                        passedTests = false;
                    }

                    stack.pop();
                }
            }
        } catch (Exception e) {
            System.out.println("EXCEPTION: " + e.getMessage());
            passedTests = false;
        }

        if (passedTests) {
            System.out.println("PASSED");
        } else {
            System.out.println("FAILED");
        }

        return passedTests;
    }

    private static Stack getStack(int[] arr)

    {

        Stack stack = new Stack();

        for (int item : arr) {
            stack.push(item);
        }

        return stack;
    }

    private static boolean testEmptyConstructor() {
        Stack stack = new Stack();

        return validateAndPrintContents(stack, null, false);
    }

    private static boolean testAddOneItem() {
        Stack stack = new Stack();
        int[] items = { 4 };

        // Add int
        stack.push(items[0]);

        int topOfStack = stack.top();

        if (topOfStack == items[0]) {
            System.out.println("PASSED");
            return true;
        } else {
            System.out.println("FAILED\n\tstack[top] = " + topOfStack + "; SHOULD BE " + items[0]);
            return false;
        }
    }

    private static boolean removeOneItem() {
        Stack stack = new Stack();
        int[] items = { 4 };

        // Add int
        stack.push(items[0]);

        int resultInt = stack.pop();

        if (resultInt == items[0]) {
            System.out.println("PASSED");
            return true;
        } else {
            System.out.println("FAILED\n\tstack popped " + resultInt + "; SHOULD BE " + items[0]);
            return false;
        }
    }

    private static boolean testAddManyItems() {
        int[] items = { 5, 10, 3456, -1, 60 };

        // Add ints
        Stack stack = getStack(items);

        // Verify test results
        boolean result = validateAndPrintContents(stack, items, true);

        return result;
    }

    private static boolean testAddAndRemoveManyItems() {
        int[] items = { 5, 10, 3456, -1, 60 };

        // Add ints
        Stack stack = getStack(items);
        stack.pop();
        stack.pop();
        stack.push(9);
        int[] resultingItems = { 5, 10, 3456, 9 };

        // Verify test results
        boolean result = validateAndPrintContents(stack, resultingItems, true);

        return result;
    }

    private static boolean testInitialIsEmpty() {
        Stack stack = new Stack();

        if (!stack.isEmpty()) {
            System.out.println("FAILED\n\tempty stack claims to not be empty");
            return false;
        } else {
            System.out.println("PASSED");
            return true;
        }
    }

    private static boolean testIsEmptyAfterAddAndRemove() {
        int[] items = { 5, 2, -3, 9, 10, 12 };
        Stack stack = getStack(items);
        boolean passedTest = !stack.isEmpty();
        if (!passedTest) {
            System.out.println("FAILED\n\tnot empt stack claims to be empty");
        } else {
            for (int i = 0; i < 3; i++)
                stack.pop();
            stack.push(100);
            for (int i = 0; i < 4; i++)
                stack.pop();
            passedTest = stack.isEmpty();
            if (!passedTest) {
                System.out.println("FAILED\n\tempty stack claims to not be empty");
            } else {

                System.out.println("PASSED");
            }
        }

        return passedTest;
    }

}