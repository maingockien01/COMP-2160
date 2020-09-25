#include<stdio.h>
#include<string.h>

#define WORDMAX 100

int main(void) {
    char word[WORDMAX], sig[WORDMAX], oldsig[WORDMAX];
    int linenum = 0;
    strcpy(oldsig, "");
    while(scanf("%s %s", sig, word) != EOF) {
        if (strcmp(oldsig, sig) != 0 && linenum >0) 
            printf("\n");
        strcpy(oldsig, sig);
        linenum ++;
        printf("%s ", word);
    };
    printf("\n");
    return 0;
}
