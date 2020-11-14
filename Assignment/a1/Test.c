#include<stdio.h>
#include<string.h>


int main() {
    char test[12] = "I am Kevin.";
    char* substring = &test[1];

    printf("%s", substring);
    return 0;
}
