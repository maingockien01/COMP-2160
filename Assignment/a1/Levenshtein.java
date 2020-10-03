public class Levenshtein
{

    private static int testsFailed = 0;
    private static int testsExecuted = 0;

    public static void main( String[] args )
    {
        System.out.println( "Testing typical cases.\n" );
        testDistance( "kitten", "kitten", 0 );
        testDistance( "kitten", "sitting", 3 );
        testDistance( "kitten", "mittens", 2 );
        testDistance( "balloon", "saloon", 2 );
        testDistance( "hello", "doggo", 4 );
        testDistance( "\t\thi", "\t\t\t\thi", 2 );

        System.out.println( "\nTesting empty/edge cases.\n" );
        testDistance( "", "", 0 );
        testDistance( "hello", "", 5 );
        testDistance( "", "doggo", 5 );
        testDistance( "a", "b", 1 );
        testDistance( "b", "b", 0 );
        testDistance( " ", " ", 0 );

        System.out.println( "\nThis might take a while...\n" );
        testDistance( "12345678901", "123456789012", 1 );   // how many chars are we looking at?

        System.out.println( "\n******These tests will be opposite in the C version******\n" );
        System.out.println( "\n******These tests **should** FAIL in the C version*******\n" );
        testDistance( "kitten", "mitten\0s", 3 );           // ????
        testDistance( "\0totally", "\0different", 9 );

        System.out.println( "\nTotal number of tests executed: " + testsExecuted );
        System.out.println( "Number of tests passed: " + (testsExecuted - testsFailed) );
        System.out.println( "Number of tests failed: " + testsFailed );
    }

    public static void testDistance( String s, String t, int expected )
    {
        int distance = levenshtein( s, t );

        if ( distance == expected )
        {
            System.out.println( "Passed! You can get from '" + s + "' to '" + t + "' in " + expected + " moves." );
        }
        else
        {
            System.out.println( "FAILED: I thought it would take " + expected + " moves, but apparently it takes " + distance + 
                    " moves to get from '" + s + "' to '" + t + "'." );
            testsFailed++;
        }

        testsExecuted++;
    }


    public static int levenshtein( String s, String t )
    {
        int cost;
        int distance;
        String deleteS;
        String deleteT;

        if (s.length() == 0)
        {
            distance = t.length();
        }
        else if (t.length() == 0)
        {
            distance = s.length();
        }
        else
        {
            if (s.charAt(0) == t.charAt(0))
            {
                cost = 0;
            }
            else
            {
                cost = 1;
            }

            deleteS = s.substring(1);
            deleteT = t.substring(1);

            assert(deleteS.length() == s.length() - 1);
            assert(deleteT.length() == t.length() - 1);

            assert(s.endsWith(deleteS)); 
            assert(t.endsWith(deleteT));

            distance = minimum(new int[] { levenshtein(deleteS, t) + 1,
                               levenshtein(s, deleteT) + 1,
                               levenshtein(deleteS, deleteT) + cost });
        }

        return distance;
    }

    public static int minimum( int minimum[] ) 
    {
        int min = 0;
        assert( minimum.length > 0 );

        if ( minimum.length > 0 )
        {
          min = minimum[0];

          for ( int i = 1; i < minimum.length; i++ )
          {
              if ( minimum[i] < min )
              {
                  min = minimum[i];
              }
          }
        }

        return min;
    }
}
