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


//--------------------------------------------------------------
// VARIABLES 
//-------------------------------------------------------------

//-------------------------------------------------------------
// PROTOTYPE
//-------------------------------------------------------------
void testEmptyTable ();
void testInsertOneItem ();
void testClearTable ();
void testWithArray(int *array, int length);
void testItemsInOrder ();
void testSearchItems (int *array, int length);
void testInsertSorted ();
void testInsertUnsorted ();
void testClearTableWithGivenArray(int *array, int length);
void testClearTableWithArray();
void testRemoveWithArray ();
void testRemoveWithGivenArray(int *array, int length);
void testMemoryLeak ();

Boolean searchArray(int *array, int length);
Boolean insertArray(int *array, int length);
Boolean removeArray(int *array, int length);
Boolean insertOne(int item);
Boolean removeOne(int item);
//------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------
int main() {
    testCase("function firstItem, search, remove, next of empty table should all be false", testEmptyTable);
    testCase("Insert one item and firstItem, searchItem, nextItem, removeItem should work", testInsertOneItem);
    testCase("Insert one item and clearTable", testClearTable);
    testCase("Insert ARRAY_SORTED, items are inserted in order, searching all items then remove all items", testInsertSorted);
    testCase("Insert ARRAY_UNSORTED, items are inserted not in order however the items in the table should be in order", testInsertUnsorted);
    testCase("Insert array, clear table, table should be empty after clearing", testClearTableWithArray);
    testCase("Insert array, remove all items, table should be empty after removing", testRemoveWithArray);
    testCase("Test memory leak by allocating and freeing repeatedly", testMemoryLeak);
    reportTest();
}

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
    for (i = 0; i < length; i ++) {
        isInsert = isInsert && insertOne(array[i]);
    }

    return isInsert;
}

Boolean removeArray(int *array, int length) {
    if (array == NULL) {
        return false;
    };
    Boolean isRemove = true;
    int i;
    for (i = 0; i < length; i ++) {
        isRemove = isRemove && removeOne(array[i]);
    }

    return isRemove;
}

Boolean searchArray(int *array, int length) {
    Boolean isSearch = true;
    int i;
    for (i = 0; i < length; i ++) {
        isSearch = isSearch && search(array[i]);
    }

    return isSearch;
}

void testEmptyTable () {
    int temp;
    test("empty table, firstItem should return false", !firstItem(&temp));
    test("empty table, nextItem should return false", !nextItem(&temp));

}

void testInsertOneItem () {
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
    test("remove item 123 - not inserted item should return false", !removeItem(123)); //Should be false
    test("remove theItem inserted should return true", removeItem(theItem)); //Should be true
    test("firstItem after removing theItem should return false", !firstItem(&temp)); //Should be false - confirm removing successful

}

void testClearTable () {
    int temp;
    int *tempPointer = NULL;
    insertItem(ARRAY_SORTED[0]);
    
    test("First Item before clear table should return true", firstItem(tempPointer)); //Should be true

    clearTable();

    test("First Item after clear table should return false", !firstItem(&temp)); //Should be true

}

void testWithArray(int *array, int length) {
    Boolean isInserted = true;
    int i;
    test("Insert all items in given array", insertArray(array, length));
   
    testItemsInOrder();
    test("Search all item in the given array should return true", searchArray(array, length));
    
 
} 

void testItemsInOrder () {
    int *tempPointer = NULL;
    int temp;
    int prevTemp;
    Boolean isInOrder = true;
    nextItem(&prevTemp); //Assign prevTemp to the first item
    while (nextItem(&temp)) {
        isInOrder = isInOrder && prevTemp <= temp;
    }
    test("Items are in order should return true", isInOrder);
 
}



void testInsertSorted () {
    testWithArray(ARRAY_SORTED, ARRAY_SORTED_LENGTH);
}

void testInsertUnsorted () {
    testWithArray(ARRAY_UNSORTED, ARRAY_UNSORTED_LENGTH);
}

void testClearTableWithArray () {
    printf("Test with ARRAY_UNSORTED\n");
    testClearTableWithGivenArray(ARRAY_UNSORTED, ARRAY_UNSORTED_LENGTH);
    printf("Test with ARRAY_SORTED\n");
    testClearTableWithGivenArray(ARRAY_SORTED, ARRAY_SORTED_LENGTH);
}

void testClearTableWithGivenArray (int *array, int length) {
    Boolean isInserted = true;
    int i;
    for (i = 0; i < length; i ++) {
        isInserted = isInserted && insertItem(array[i]);
    };
    test("Insert all items in given array", isInserted);
    
    clearTable();

    printf("Call clear table, table should be empty now\n");

    testEmptyTable ();

}

void testRemoveWithArray() {
    printf("Test with ARRAY_UNSORTED\n");
    testRemoveWithGivenArray(ARRAY_UNSORTED, ARRAY_UNSORTED_LENGTH);
    printf("Test with ARRAY_SORTED\n");
    testRemoveWithGivenArray(ARRAY_SORTED, ARRAY_SORTED_LENGTH);
}

void testRemoveWithGivenArray(int *array, int length) {
    testWithArray(array, length);

    printf("Remove item\n");
    int i;
    Boolean isRemoveAllItem = true;
    for(i = 0; i < length; i ++) {
        isRemoveAllItem = isRemoveAllItem && removeItem(array[i]);
    };
    test("Removed all items, table should be empty", isRemoveAllItem);
    testEmptyTable();
}

void testMemoryLeak () {
    

}
