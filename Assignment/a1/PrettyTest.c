#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define LINE_SIZE 50

int scanLine(char* line);

int main () {

    char* line = NULL;
    int isEOF;
    do {
        char* line = (char* ) malloc(LINE_SIZE * sizeof(char));
        isEOF = scanLine(line);
        printf("%s", line);
    } while (isEOF);
        
        


    return 0;
}

int scanLine (char* lineAddress) {
    int isEOF;
    char* line = lineAddress;

    char letter;
    int lineIndex = 0;

    while ((isEOF = (scanf("%c", &letter) != EOF))) {
        if(letter == '\n') {
            break;
        }

        line[lineIndex] = letter;
        lineIndex ++;
    }

    line[lineIndex] = '\0';
    printf("%s", line);

    return isEOF;
}

