//----------------------------------------------------------
// NAME: kien mai
// STUDENT NUMBER: 7876083
// COURSE: COMP 2160, SECTION: A02
// INSTRUCTOR: Dr. Eskicioglu
// ASSIGNMENT: #3, QUESTION: #1
//
// REMARKS: test suite for the table.h implementation (table.c)
//---------------------------------------------------------

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "table.h"
#include "test.h"

//-------------------------------------------------------------
// CONSTANTS
//-------------------------------------------------------------

 int ARRAY_SORTED[] = {1,2,3,4,5,7,9,10,12,25};
const int ARRAY_SORTED_LENGTH = 10;
 int ARRAY_UNSORTED[] = {10,9,8,7,6,5,4,3,2,1};
const int ARRAY_UNSORTED_LENGTH = 10;

const int REPEAT_TIME = 10;

//--------------------------------------------------------------
// VARIABLES 
//-------------------------------------------------------------

//-------------------------------------------------------------
// PROTOTYPE
//-------------------------------------------------------------

//Test cases
void testEmptyTable ();
void testTableOneElement ();
void testClearTable ();
void testMemoryLeak ();
void testInsertSorted ();
void testRemove ();
void testItemsInOrder ();

//Helpers
Boolean searchArray(int *array, int length);
Boolean insertArray(int *array, int length);
Boolean removeArray(int *array, int length);
Boolean insertOne(int item);
Boolean removeOne(int item);
//------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------
int main() {
    testCase("Empty table: firstItem, search, remove, next should all return false", testEmptyTable);
    testCase("Table with one element: insertItem, firstItem, searchItem, nextItem, removeItem should return true", testTableOneElement);
    testCase("Table: clearTable - memeory leak", testClearTable);
    testCase("Table: items are inserted in order accending", testInsertSorted);
    testCase("Table: inserted and removing items - memeory leak", testRemove);
    reportTest();
}

//Helpers
Boolean insertOne (int item) {
    return insertItem(item);
};

Boolean removeOne(int item) {
    return removeItem(item);
}

Boolean insertArray(int *array, int length) {
    if (array == NULL) {
        return false;
    };
    Boolean isInsert = true;
    int i;
    printf("Insert: ");
    for (i = 0; i < length; i ++) {
        printf("%d ", array[i]);
        isInsert = isInsert && insertOne(array[i]);
    }
    printf("\n");

    return isInsert;
}

Boolean removeArray(int *array, int length) {
    if (array == NULL) {
        return false;
    };
    Boolean isRemove = true;
    int i;
    printf("Remove: ");
    for (i = 0; i < length; i ++) {
        printf("%d ", array[i]);
        isRemove = isRemove && removeOne(array[i]);
    }
    printf("\n");

    return isRemove;
}

Boolean searchArray(int *array, int length) {
    Boolean isSearch = true;
    int i;
    printf("Search: ");
    for (i = 0; i < length; i ++) {
        printf("%d ", array[i]);
        isSearch = isSearch && search(array[i]);
    }
    printf("\n");

    return isSearch;
}

void testItemsInOrder () {
    int temp;
    int prevTemp;
    Boolean isInOrder = true;
    nextItem(&prevTemp); //Assign prevTemp to the first item
    nextItem(&prevTemp); //Assign prevTemp to the first item
    while (nextItem(&temp)) {
        isInOrder = isInOrder && prevTemp <= temp;
        prevTemp = temp;
    }
    test("Items are in order should return true", isInOrder);
    printf("Print item: ");
    while(nextItem(&temp)) {
        printf("%d ", temp);
    }
    printf("\n");
}


//Test cases
void testEmptyTable () {
    int temp;
    test("empty table, firstItem should return false", !firstItem(&temp));
    test("empty table, nextItem should return false", !nextItem(&temp));

}

void testTableOneElement () {
    int theItem = ARRAY_SORTED[0];
    int temp;
    int tempNext;
    test("Insert theItem should return true",insertItem(theItem)); //Should be true
    test("First Item after insert the item should return true",firstItem(&temp)); //Should be true
    test("The temp after first item function should equal the item inserted",temp==theItem); //Should be true
    test("Search the inserted item should return true", search(theItem)); //Should be true
    test("Search a not inserted item should return false", !search(123)); //Should be false
    test("nextItem should return true", nextItem(&tempNext)); //Should be true
    test("tempNext callback value of next item should equal theItem inserted", tempNext == theItem ? true : false); //Should be true
    test("Insert duplicated item should be false", !insertItem(theItem));
    test("remove item 123 - not inserted item should return false", !removeItem(123)); //Should be false
    test("remove theItem inserted should return true", removeItem(theItem)); //Should be true
    test("firstItem after removing theItem should return false", !firstItem(&temp)); //Should be false - confirm removing successful

}

void testClearTable () {
    int temp;
    int count;

    printf("Clear table with one element");
    insertItem(ARRAY_SORTED[0]);
    test("First Item before clear table should return true", firstItem(&temp)); //Should be true
    clearTable();
    test("First Item after clear table should return false", !firstItem(&temp)); //Should be true

    printf("Clear table with array - repeating %d times\n", REPEAT_TIME);
    //Insert an array
    for (count = 0; count < REPEAT_TIME; count ++) {
        insertArray(ARRAY_UNSORTED, ARRAY_UNSORTED_LENGTH);
        printf("Clear table\n");
        clearTable();
    }
    testEmptyTable();
}

void testInsertSorted () {
    printf("Insert sorted array.\n");
    insertArray(ARRAY_SORTED, ARRAY_SORTED_LENGTH);
    testItemsInOrder();
    printf("Clear table\n");
    clearTable();

    printf("Insert unsorted array.\n");
    insertArray(ARRAY_UNSORTED, ARRAY_UNSORTED_LENGTH);
    testItemsInOrder();
    printf("Clear table\n");
    clearTable();
}

void testRemove() {
    int i;
    int j;
    printf("Test with ARRAY_UNSORTED\n");
    insertArray(ARRAY_SORTED, ARRAY_SORTED_LENGTH);
    removeArray(ARRAY_SORTED, ARRAY_SORTED_LENGTH);
    testEmptyTable();

    printf("Test with ARRAY_SORTED\n");
    insertArray(ARRAY_UNSORTED, ARRAY_UNSORTED_LENGTH);
    removeArray(ARRAY_UNSORTED, ARRAY_UNSORTED_LENGTH);
    testEmptyTable();

    printf("Scaffolding - repeat %d times\n", REPEAT_TIME);
    for (i = 1; i <= REPEAT_TIME; i ++) {
        printf("Insert and remove #%d.\n", i);
        //insert then remove
        int array[i];
        for (j = 0; j < i; j ++) {
            array[j] = j;
        }
        insertArray(array, i);
        removeArray(array, i);
    }
}


