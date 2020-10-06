#include<stdio.h>
#include<string.h>

int testsFailed = 0;
int testsExecuted = 0;

int minimum (int* minimum, int length);
int levenshtein (char*s, char* t);
void testDistance(char* s, char* t, int expected);

int main () {
    printf( "Testing typical cases.\n" );
    testDistance( "kitten", "kitten", 0 );
    testDistance( "kitten", "sitting", 3 );
    testDistance( "kitten", "mittens", 2 );
    testDistance( "balloon", "saloon", 2 );
    testDistance( "hello", "doggo", 4 );
    testDistance( "\t\thi", "\t\t\t\thi", 2 );

    printf( "\nTesting empty/edge cases.\n" );
    testDistance( "", "", 0 );
    testDistance( "hello", "", 5 );
    testDistance( "", "doggo", 5 );
    testDistance( "a", "b", 1 );
    testDistance( "b", "b", 0 );
    testDistance( " ", " ", 0 );

    printf( "\nThis might take a while...\n" );
    testDistance( "12345678901", "123456789012", 1 );   // how many chars are we looking at?

    printf( "\n******These tests will be opposite in the C version******\n" );
    printf( "\n******These tests **should** FAIL in the C version*******\n" );
    testDistance( "kitten", "mitten\0s", 3 );           // ????
    testDistance( "\0totally", "\0different", 9 );

    printf( "\nTotal number of tests executed: %d\n" , testsExecuted );
    printf( "Number of tests passed: %d\n" , (testsExecuted - testsFailed) );
    printf( "Number of tests failed: %d\n" , testsFailed );

    return 0;
}

int minimum (int* minimum, int length) {
    int min = 0;
    int i;
    
    if (length > 0) {
        min = minimum[0];
        
        for (i = 1; i < length; i ++) {
            if (minimum[i] < min) {
                min = minimum[i];
            }
        }
    }

    return min;
}

int levenshtein (char* s, char* t) {
    int cost;
    int distance;

    char* deleteS;
    char* deleteT;

    if (strlen(s) == 0) {
        distance = strlen(t);
    } 
    else if (strlen(t) == 0) {
        distance = strlen(s);
    }
    else {
        if (s[0] == t[0]) {
            cost = 0;
        } 
        else {
            cost = 1;
        }

        deleteS = &s[1];
        deleteT = &t[1];

        int possibleMin[3] = {levenshtein(deleteS, t) + 1, levenshtein(s, deleteT) + 1, levenshtein(deleteS, deleteT) + cost};

        distance = minimum(possibleMin, 3);
    }

    return distance;
}

void testDistance (char* s, char* t, int expected) {
    int distance = levenshtein(s, t);

    if (distance == expected) {

        printf("Passed! You can get from '%s' to '%s' in %d moves.\n", s, t, expected);
    }
    else {
        printf("FAILED: I thought it would take %d moves, but apparently it takes %d moves to get from '%s' to '%s'.\n", expected, distance, s, t);

        testsFailed ++;
    };

    testsExecuted ++;

}
