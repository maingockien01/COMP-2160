// This program reads in lines of text and extracts the nth word in each line.

import java.util.Scanner;

public class Nthword 
{
  public static void main( String args[] )
  {
    String line;
    int word;
    Scanner stdin = new Scanner(System.in);

    while ( stdin.hasNextLine() )
    {
      line = stdin.nextLine();
      word = stdin.nextInt(); stdin.nextLine(); // get rid of the newline after the int

      System.out.println( "Read line: \"" + line + "\", extracting word [" + word + "]" );
      System.out.println( "Word #" + word + " is: " + extractWord( line, word ) );
    }

    stdin.close();

    System.out.println( "\nEnd of processing" );
    
  }

  // returns the first word of the string
  private static String extractWord( String theLine, int word )
  {
    int start;
    int end;
    int spaces = 1;
    String result = "";

    // search for the nth non-blank character
    for (start = 0; start < theLine.length() && spaces < word; start++)
    {
        if ( Character.isSpaceChar( theLine.charAt( start ) ) )
        {
            spaces++;
        }
    }

    // only need to continue if we haven't gone past the end of the string
    if ( start<theLine.length() )
    {
      // the next blank character is the end
      for ( end=start ; end<theLine.length() && !Character.isSpaceChar( theLine.charAt( end ) ) ; end++ )
        ;

      // we now have the word 
      result = theLine.substring( start, end );
    }

    return( result );
  }
  
}
