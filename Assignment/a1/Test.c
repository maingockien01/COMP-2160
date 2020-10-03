#include<stdio.h>
#include<string.h>


int main() {
    char letter;
    while (scanf("%c", &letter) != EOF) {
        printf("%c", letter);
    };


    printf("---> %d", EOF == '\0');

    return 0;
}
