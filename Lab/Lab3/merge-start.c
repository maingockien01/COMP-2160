#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUT_LENGTH 128
#define FIELD_LENGTH 30
#define NUM_FIELDS   9

int main( void )
{
    FILE *template = NULL;
    FILE *data = NULL;

    char input[INPUT_LENGTH];                     // a string for reading from a file
    char customerData[NUM_FIELDS][FIELD_LENGTH];  // an **array of strings** for storing the results of a "split"

    const char tokenSplitter[2] = "|";

    // these 3 variables are useful for processing the text input
    int  element = 0;
    char *next;
    char ch;

    char *token;

    // yes, we're hard-coding file names... note that this is *unacceptable*, unless we explicitly tell you to do it
    template = fopen( "template.txt", "r" );
    if ( template != NULL )
    {
        // read in the customers until we're done
        data = fopen( "data.txt", "r" );
        if ( data != NULL )
        {
            while ( fgets( input, INPUT_LENGTH, data ) != NULL )
            {
                
                // INSERT PARSING CODE FOR `data.txt` HERE! 
                // Your job here is to:
                //
                // * Tokenize the line from the file data.txt
                // * Copy each field into the customerData array
                //
                // We're trying to do something that resembles `split` in Java
                
                element = 0;
                token = strtok(input, tokenSplitter);

                while (token != NULL) {
                    strcpy(customerData[element], token);

                    element ++;
                    token = strtok (NULL, tokenSplitter);
                }

                // generate the output by reading and parsing the template
                // instead of reading it into a buffer it just re-reads the file each time
                rewind( template );
                while ( fgets( input, INPUT_LENGTH, template ) != NULL )
                {
                    // INSERT PARSING CODE FOR `template.txt` HERE!
                    // Your job here is to:
                    //
                    // * Read one character at a time (it's an *array*!)
                    // * Based on the character you read, decide
                    //   * Is this a character to print?
                    //   * Is this a variable to replace with customerData data?
                      
                    int i;
                    int inputLength = strlen(input);
                    for (i = 0; i < inputLength ; i ++) {
                        if (input[i] == '$') {
                            int fieldIndex = input[++i] - '0';
                            printf("%s", customerData[fieldIndex]);

                        } else {
                            printf("%c", input[i]);
                        }
                        
                    }
                      
                     
                }
                printf("----------\n\n");
            }

            fclose( data );
        }

        fclose( template );
    }

    return EXIT_SUCCESS;
}
