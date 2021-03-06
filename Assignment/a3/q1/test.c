#include <stdio.h>

#include "test.h"

char SUCCESS[] = "Success!";
char FAIL[] = "Fail!";

int testExecuted = 0;
int testFailed = 0;

void testCase(char *desc, void (*testFunction)()) {
    printf("\nTest case: %s\n", desc);
    (*testFunction)();
    printf("End test case!\n");
}

void test(char *desc, Boolean expectTrue) {
    testExecuted ++;

    char *result;
    if (expectTrue == true) {
        result = SUCCESS;

    } else {
        result = FAIL;
        testFailed ++;
    }
    printf("Test: %s: %s\n", desc, result);
}

Boolean expectEqual (int expect, int actual) {
    if (expect == actual) {
        return true;
    } else {
        return false;
    }
}

Boolean expectNull (void* value) {
    if (value == NULL) {
        return true;
    } else {
        return false;
    }
}

Boolean expectNotNull (void* value) {
    if (value != NULL) {
        return true;
    } else {
        return false;
    }
}



void reportTest () {
    
    printf("\nTest summary:\n");
    printf("The total number of executed tests: %d \n", testExecuted);
    printf("The total number of failed tests: %d \n", testFailed);
    
}


