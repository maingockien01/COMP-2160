#include <stdio.h>

#include "test.h"
#include "set.h"

//----------------------------------------------------------
// CONSTANTS
//----------------------------------------------------------

int REPEAT_TIME = 20;

int ARRAY_1[] = {1,2,3,4,5,6,7,8,9,10};
int ARRAY_1_LENGTH = 10;

int ARRAY_2[] = {1};
int ARRAY_2_LENGTH = 1;

int ARRAY_3[] = {1,2};
int ARRAY_3_LENGTH = 2;

int ARRAY_4[] = {2,3};
int ARRAY_4_LENGTH = 2;

int ARRAY_5[] = {1,1,1,1,1,1,1,1,1,1};
int ARRAY_5_LENGTH = 10;

int ARRAY_6[] = {1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10};
int ARRAY_6_LENGTH = 20;

int ARRAY_7[] = {2};
int ARRAY_7_LENGTH = 1;

int ARRAY_8[] = {1,2,3,4,5,6,7,8,9};
int ARRAY_8_LENGTH = 9;

int ARRAY_9[] = {1,2,3,4,5,6,7,8,9,11};
int ARRAY_9_LENGTH = 10;

int ARRAY_10[] = {11,12,13,14,15,16,17,18,19,20};
int ARRAY_10_LENGTH = 10;

int ARRAY_11[] = {1,2,3,4,5,6,7,8,9,10,11};
int ARRAY_11_LENGTH = 11;

int ARRAY_12[] = {1,2,3,4};
int ARRAY_12_LENGTH = 4;

int ARRAY_13[] = {2,4,5,6};
int ARRAY_13_LENGTH = 4;

int ARRAY_14[] = {1,3,5,6};
int ARRAY_14_LENGTH = 4;

int ARRAY_15[] = {5,6,7,8,9,10};
int ARRAY_15_LENGTH = 5;



//----------------------------------------------------------
// PROTOTYPES
//----------------------------------------------------------

void testValidateMemUse ();

void testInsertAndRemove ();

void testAreEqual ();

void testAreDisjoint ();

void testUnionOf ();

void testSymmetricDifferenceOf ();

void testScaffolding();

//Helpers

//Return true if all the item in the array are inserted successfully
Boolean insertArray (Set *set, int *array, int length);

//Retturn true if all the item in the array exist and are removed from the set successfully
Boolean removeArray (Set *set, int *array, int length);

//----------------------------------------------------------
// IMPLEMENTATION
//----------------------------------------------------------

int main () {
    testCase("ValidateMemUse with newSet and deleteSet", testValidateMemUse);
    testCase("insertItem with removeItem", testInsertAndRemove);
    testCase("areEqual function", testAreEqual);
    testCase("areDisjoint function", testAreDisjoint);
    testCase("unionOf function", testUnionOf);
    testCase("symmetricDifferenceOf", testSymmetricDifferenceOf);
    testCase("repeating construct and deconstruct set to test memory leak", testScaffolding);

    reportTest();
}

//Helpers
Boolean insertArray(Set *set, int *array, int length) {
    int i;
    Boolean isNotDuplicate = true;
    printf("Insert: ");
    for (i = 0; i < length; i ++) {
        printf("%d ", array[i]);
        isNotDuplicate = isNotDuplicate && insertItem(set, array[i]);
    };
    printf("\n");
    return isNotDuplicate;
}

Boolean removeArray (Set *set, int *array, int length) {
    int i;
    Boolean isAllRemoved = true;
    printf("Remove: ");
    for (i = 0; i < length; i ++) {
        printf("%d ", array[i]);
        isAllRemoved = isAllRemoved && removeItem(set, array[i]);
    };
    printf("\n");
    return isAllRemoved;
}

//Test cases
void testValidateMemUse () {
    test("No set has been created, validateMemUse should return true", validateMemUse());
    printf("Create a set: firstSet\n");
    Set *firstSet = newSet ();
    test("The firstSet should be not null", !expectNull(firstSet));
    test("One set was created, validateMemUse should return false", !validateMemUse());
    test("Delete the first set, the returned set from function deleteSet should be null", expectNull(deleteSet(firstSet)));
    test("There is no set now, validateMemUse should return true", validateMemUse());
}

void testInsertAndRemove () {
    Set *set1 = newSet ();
    if (validateMemUse() || set1 == NULL) {
        printf("ERROR: Fail to construct set, unable to test other functions\n");
        return;
    };

    printf("Test insert and remove 1 item\n");
    test("Insert 1 item should return true", insertArray(set1, ARRAY_2, ARRAY_2_LENGTH));
    test("Remove wrong items should return false", removeArray(set1, ARRAY_7, ARRAY_7_LENGTH));
    test("Remove 1 item should return true", removeArray(set1, ARRAY_2, ARRAY_2_LENGTH));
    test("Remove same item second time (confirm removal) should return false", removeArray(set1, ARRAY_2, ARRAY_2_LENGTH));

    printf("Reconstruct set\n");
    deleteSet(set1);
    set1 = newSet();

    printf("Test insert and remove 2 items width duplicate\n");
    test("Insert 2 different items should return true", insertArray(set1, ARRAY_3, ARRAY_3_LENGTH));
    test("Insert 1 item that duplicate a item in set should return false", !insertArray(set1, ARRAY_2, ARRAY_2_LENGTH));
    test("Remove first two item should return true", removeArray(set1, ARRAY_3, ARRAY_3_LENGTH));
    test("Remove the item that tried to insert duplicate (to confirm no duplicate) should return false", !removeArray(set1, ARRAY_2, ARRAY_2_LENGTH));

    printf("Reconstruct set\n");
    deleteSet(set1);
    set1 = newSet();

    printf("Test insert and remove multiple items\n");
    test("Insert multiple items should return true", insertArray(set1, ARRAY_1, ARRAY_1_LENGTH));
    test("Remove multiple items (same items) should return true", removeArray(set1, ARRAY_1, ARRAY_1_LENGTH));
    
    deleteSet(set1);

}

void testAreEqual () {
    Set *set1 = newSet();
    Set *set2 = newSet();

    if(validateMemUse() || set1 == NULL || set2 == NULL) {
        printf("ERROR: Fail to construct set, unable to construct other functions!\n");
    }

    printf("Test multiple-item sets\n");
    printf("Insert set1, ");
    insertArray(set1, ARRAY_6, ARRAY_6_LENGTH);
    printf("Insert set2, ");
    insertArray(set2, ARRAY_6, ARRAY_6_LENGTH);
    test("Set1 should equal set2", areEqual(set1, set2));

    printf("Reconstruct set\n");
    deleteSet(set1);
    deleteSet(set2);
    set1 = newSet();
    set2 = newSet();

    printf("Test 2 empty\n");
    printf("Set 1: empty\n");
    printf("Set 2: empty\n");
    test("Set1 empty should equal set2 empty", areEqual(set1, set2));

    printf("Reconstruct set\n");
    deleteSet(set1);
    deleteSet(set2);
    set1 = newSet();
    set2 = newSet();

    printf("Test empty set with non-empty set\n");
    printf("Insert set1, ");
    insertArray(set1, ARRAY_6, ARRAY_6_LENGTH);
    printf("Set 2: empty\n");
    test("Set1 should NOT equal set2 empty", !areEqual(set1, set2));

    printf("Reconstruct set\n");
    deleteSet(set1);
    deleteSet(set2);
    set1 = newSet();
    set2 = newSet();

    printf("Test multiple-item same-length sets\n");
    printf("Insert set1, ");
    insertArray(set1, ARRAY_6, ARRAY_6_LENGTH);
    printf("Insert set2, ");
    insertArray(set2, ARRAY_9, ARRAY_9_LENGTH);
    test("Set1 should NOT equal set2", !areEqual(set1, set2));

    deleteSet(set1);
    deleteSet(set2);
}

void testAreDisjoint () {
    Set *set1 = newSet();
    Set *set2 = newSet();

    if(validateMemUse() || set1 == NULL || set2 == NULL) {
        printf("Fail to construct set, unable to construct other functions!\n");
    }

    printf("Test multiple-item length sets\n");
    printf("Insert set1, ");
    insertArray(set1, ARRAY_6, ARRAY_8_LENGTH);
    printf("Insert set2, ");
    insertArray(set2, ARRAY_6, ARRAY_8_LENGTH);
    test("Set1 should NOT disjoint set2", !areDisjoint(set1, set2));

    printf("Reconstruct set\n");
    deleteSet(set1);
    deleteSet(set2);
    set1 = newSet();
    set2 = newSet();

    printf("Test multiple-item sets\n");
    printf("Insert set1, ");
    insertArray(set1, ARRAY_1, ARRAY_1_LENGTH);
    printf("Insert set2, ");
    insertArray(set2, ARRAY_10, ARRAY_10_LENGTH);
    test("Set1 should disjoint set2", areDisjoint(set1, set2));

    printf("Reconstruct set\n");
    deleteSet(set1);
    deleteSet(set2);
    set1 = newSet();
    set2 = newSet();

    printf("Test empty set with non-empty set\n");
    printf("Insert set1, ");
    insertArray(set1, ARRAY_6, ARRAY_8_LENGTH);
    test("Set1 non-empty should disjoint set2 empty", areDisjoint(set1, set2));

    printf("Reconstruct set\n");
    deleteSet(set1);
    deleteSet(set2);
    set1 = newSet();
    set2 = newSet();

    printf("Test 2 empty sets\n");
    test("Set1 empty should disjoint set2 empty", areDisjoint(set1, set2));

    deleteSet(set1);
    deleteSet(set2);
}

void testUnionOf () {
    Set *set1 = newSet();
    Set *set2 = newSet();
    Set *set3 = newSet();
    Set *unionSet; 
    if(validateMemUse() || set1 == NULL || set2 == NULL || set3 == NULL) {
        printf("Fail to construct set, unable to construct other functions!\n");
    }

    printf("Test 2 disjoint set\n");
    printf("Set 1 ");
    insertArray(set1, ARRAY_2, ARRAY_2_LENGTH);
    printf("Set 2 ");
    insertArray(set2, ARRAY_7, ARRAY_7_LENGTH);
    printf("Set 3 ");
    insertArray(set3, ARRAY_3, ARRAY_3_LENGTH);
    printf("Union set 1 and set 2\n");
    unionSet = unionOf(set1, set2);
    test("Union set 1 and set 2 should equal set 3", areEqual(set3, unionSet));

    printf("Reconstruct sets\n");
    deleteSet(set1);
    deleteSet(set2);
    deleteSet(set3);
    deleteSet(unionSet);
    set1 = newSet();
    set2 = newSet();
    set3 = newSet();

    printf("Test 2 non-disjoint set\n");
    printf("Set 1 ");
    insertArray(set1, ARRAY_1, ARRAY_1_LENGTH);
    printf("Set 2 ");
    insertArray(set2, ARRAY_9, ARRAY_9_LENGTH);
    printf("Set 3 ");
    insertArray(set3, ARRAY_11, ARRAY_11_LENGTH);
    printf("Union set 1 and set 2\n");
    unionSet = unionOf(set1, set2);
    test("Union set 1 and set 2 should equal set 3", areEqual(set3, unionSet));

    printf("Reconstruct sets");
    deleteSet(set1);
    deleteSet(set2);
    deleteSet(set3);
    deleteSet(unionSet);
    set1 = newSet();
    set2 = newSet();
    set3 = newSet();


    printf("Test empty set and non-empty set\n");
    printf("Set 1 ");
    insertArray(set1, ARRAY_2, ARRAY_2_LENGTH);
    printf("Set 3 ");
    insertArray(set3, ARRAY_2, ARRAY_2_LENGTH);
    printf("Union set 1 and set 2\n");
    unionSet = unionOf(set1, set2);
    test("Union set 1 and set 2 empty should equal set 3", areEqual(set3, unionSet));

    printf("Reconstruct sets\n");
    deleteSet(set1);
    deleteSet(set2);
    deleteSet(set3);
    deleteSet(unionSet);
    set1 = newSet();
    set2 = newSet();
    set3 = newSet();


    printf("Test 2 empty set\n");
    printf("Union set 1 empty and set 2 empty\n");
    unionSet = unionOf(set1, set2);
    test("Union set 1 and set 2 should equal set 3 empty", areEqual(set3, unionSet));

    deleteSet(set1);
    deleteSet(set2);
    deleteSet(set3);
    deleteSet(unionSet);

}

void testSymmetricDifferenceOf () {
    Set *set1;
    Set *set2;
    Set *set3;
    Set *symmetricDifference;
    set1 = newSet ();
    set2 = newSet ();
    set3 = newSet ();

    if(validateMemUse() || set1 == NULL || set2 == NULL || set3 == NULL) {
        printf("Fail to construct set, unable to construct other functions!\n");
    }

    printf("Test 2 joint sets\n");
    printf("Set 1 :");
    insertArray(set1, ARRAY_12, ARRAY_12_LENGTH);
    printf("Set 2 :");
    insertArray(set2, ARRAY_13, ARRAY_13_LENGTH);
    printf("Set 3:");
    insertArray(set3, ARRAY_14, ARRAY_14_LENGTH);
    symmetricDifference = symmetricDifferenceOf(set1, set2);
    test("Symmetric Difference of set 1 and set 2 should equal set 3", areEqual(set3, symmetricDifference));


    printf("Reconstruct sets\n");
    deleteSet(set1);
    deleteSet(set2);
    deleteSet(set3);
    deleteSet(symmetricDifference);
    set1 = newSet();
    set2 = newSet();
    set3 = newSet();

    printf("Test 2 disjoint sets\n");
    printf("Set 1 :");
    insertArray(set1, ARRAY_12, ARRAY_12_LENGTH);
    printf("Set 2 :");
    insertArray(set2, ARRAY_15, ARRAY_15_LENGTH);
    printf("Set 3:");
    insertArray(set3, ARRAY_1, ARRAY_1_LENGTH);
    symmetricDifference = symmetricDifferenceOf(set1, set2);
    test("Symmetric Difference of set 1 and set 2 should equal set 3", areEqual(set3, symmetricDifference));


    printf("Reconstruct sets\n");
    deleteSet(set1);
    deleteSet(set2);
    deleteSet(set3);
    deleteSet(symmetricDifference);
    set1 = newSet();
    set2 = newSet();
    set3 = newSet();

    printf("Test 2 same sets\n");
    printf("Set 1 :");
    insertArray(set1, ARRAY_1, ARRAY_1_LENGTH);
    printf("Set 2 :");
    insertArray(set2, ARRAY_1, ARRAY_1_LENGTH);
    printf("Set 3: empty\n");
    symmetricDifference = symmetricDifferenceOf(set1, set2);
    test("Symmetric Difference of set 1 and set 2 should equal set 3", areEqual(set3, symmetricDifference));


    printf("Reconstruct sets\n");
    deleteSet(set1);
    deleteSet(set2);
    deleteSet(set3);
    deleteSet(symmetricDifference);
    set1 = newSet();
    set2 = newSet();
    set3 = newSet();

    printf("Test non-empty set with empty set\n");
    printf("Set 1 :");
    insertArray(set1, ARRAY_1, ARRAY_1_LENGTH);
    printf("Set 2 : empty\n");
    printf("Set 3:");
    insertArray(set3, ARRAY_1, ARRAY_1_LENGTH);
    symmetricDifference = symmetricDifferenceOf(set1, set2);
    test("Symmetric Difference of set 1 and set 2 should equal set 3", areEqual(set3, symmetricDifference));


    printf("Reconstruct sets\n");
    deleteSet(set1);
    deleteSet(set2);
    deleteSet(set3);
    deleteSet(symmetricDifference);
    set1 = newSet();
    set2 = newSet();
    set3 = newSet();

    printf("Test 2 empty sets\n");
    printf("Set 1 : empty\n");
    printf("Set 2 : empty\n");
    printf("Set 3 : empty\n");
    symmetricDifference = symmetricDifferenceOf(set1, set2);
    test("Symmetric Difference of set 1 and set 2 should equal set 3", areEqual(set3, symmetricDifference));


    deleteSet(set1);
    deleteSet(set2);
    deleteSet(set3);
}

void testScaffolding () {
    int i, j;
    Set *set1;

    printf("Insert and remove %d times\n", REPEAT_TIME);
    for (i = 1; i <= REPEAT_TIME; i ++) {
        printf("Insert and remove #%d\n", i);
        set1 = newSet();
        int array[i];

        for (j = 0; j < i; j ++) {
            array[j] = j;
        }

        insertArray(set1, array, i);
        removeArray(set1, array, i);
        deleteSet(set1);
    }

    printf("Construct, insert and deleteSet %d times\n", REPEAT_TIME);
    for (i = 1; i <= REPEAT_TIME; i ++) {
        printf("Construct, insert and deleteSet #%d\n", i);
        set1 = newSet();
        int array[i];

        for (j = 0; j < i; j ++) {
            array[j] = j;
        }

        insertArray(set1, array, i);
        removeArray(set1, array, i);
        deleteSet(set1);
    }   
}
