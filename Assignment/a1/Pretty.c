//----------------------------------------------------------------
// NAME:		KIEN MAI
// STUDENT NUMBER:	7876083
// COURSE: 		COMP 2160, SECTION A02
// INSTRUCTOR		Dr. Eskicioglu
// ASSIGNMENT: 		#1
//
// REMARKS: 		Conver a pragraph to wanted format.
//
//----------------------------------------------------------------

#include<stdio.h>
#include<string.h>

#define LINE_LENGTH 50

int main () {

    char line[LINE_LENGTH];
    int position = 1;

    while (fgets (line, LINE_LENGTH, stdin)) {
        if (line[strlen(line)-1] == '\n') {
            line[strlen(line)-1] = '\0';
        }

        if (line[0] == '\0') {
            if (position > 1) {
                printf("\n");
            }

            printf("\n");
            position = 1;
        } else {
            if ((position + strlen(line) - 1) > LINE_LENGTH) {
                printf("\n");
                position = 1;
            }
            printf("%s", line);

            position += strlen(line);

            if (position <= LINE_LENGTH) {
                printf(" ");
                position ++;
            }
        }
    }

    return 0;
}

