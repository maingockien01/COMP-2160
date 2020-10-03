import java.io.*;
import java.util.*;

public class Pretty
{
  public static final int LINE_SIZE = 50;
  
  public static void main(String[] parms)
  {
    String inputLine;
    int position = 1;
    Scanner fileIn = new Scanner(System.in);

    while (fileIn.hasNextLine())
    {
      inputLine = fileIn.nextLine();

      if (inputLine.equals(""))
      {
        if (position > 1)
        {
          System.out.println();
        }
          
        System.out.println();
        position = 1;
      }
        
      else
      {
        if ((position+inputLine.length()-1) > LINE_SIZE)
        {
          System.out.println();
          position = 1;
        }
        System.out.print(inputLine);
          
        position += inputLine.length();
        if (position <= LINE_SIZE)
        {	// add a blank after the current word
          System.out.print(" ");
          position++;
        }
      }   
    }      
  }
}
