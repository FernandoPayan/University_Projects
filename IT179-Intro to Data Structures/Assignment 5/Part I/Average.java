import java.util.*;
import java.io.*;

public class Average
{
  public static void main(String [] args) throws IOException
    {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int num = 0;
        int counter = 0;

        System.out.println("Enter as many integers as you'd like. To calcualte the average, please write 'stop': ");

        try {
            while (true)
            {
                String input = reader.readLine();
                if (input.equals("stop"))
                {
                    break;
                }
                num += Integer.parseInt(input);
                counter++;
            }
            if (num == 0 || counter == 0)
            {
                System.out.println("No integers were entered. Please restart the program and enter integers");
                System.exit(1);
            }
            System.out.println("The sum is: " + num);
            System.out.println("The average is: " + (num / counter));
        } catch (NumberFormatException e)
        {
            System.out.println("Sorry, that is not an integer. Please restart the program and try again");
        }
        
    }
}