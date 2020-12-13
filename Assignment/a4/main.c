//------------------------------------------------------
// NAME: Kien Mai
// STUDENT NUMBER: 7876083
// COURSE: COMP 2160
// INSTRUCTOR Dr. Eskicioglu
// ASSIGNMENT: #4
//
// REMARKS: Test suits provied by Kien Mai.
//------------------------------------------------------


#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#include "ObjectManager.h"
#include "test.h"

Ref id1, id2, id3, id4;

//Tests

void testInsert ();
void testRetrieve ();
void testDestroy ();
void testDump ();
void testDestroyObject ();
void testCompact ();
void testCompactPartlyFull ();

//Helpers

int main () {
    testCase("test insert", testInsert);
    testCase("test retrieve", testRetrieve);
    testCase("test destroy", testDestroy);
    testCase("test dump", testDump);
    testCase("test refCount and destroyObject", testDestroyObject);
    testCase("test compact and insert", testCompact);
    testCase("test compact and insert: defragment partially", testCompactPartlyFull);

    reportTest ();
}


void testInsert () {

    initPool ();
    id1 = insertObject(1 + MEMORY_SIZE);
    test("Insert more than memeory size, should return NULL_REF", id1 == NULL_REF);
    id2 = insertObject(-1);
    test("Insert negative size, should return NULL_REF", id2 == NULL_REF);
    id3 = insertObject(100);
    test("Insert first object", id3 == 1);
    id4 = insertObject(100);
    test("Insert second object", id4 == 2);
    id1 = insertObject(MEMORY_SIZE);
    test("Insert new object beyond the available space, should retur NULL_REF", id1 == NULL_REF);

    destroyPool();
}

void testRetrieve () {
    initPool();

    id3 = insertObject(100);
    test("Insert first object", id3 == 1);
    id4 = insertObject(100);
    test("Insert second object", id4 == 2);
    
    char *object1 = (char *) retrieveObject(id3);
    test("object1 should not be NULL", object1 != NULL);
    char *object2 = (char*) retrieveObject(id4);
    test("object2 should not be NULL", object2 != NULL);

    test("address of object2 - object1 should equal 100 (the size of object1)", object2-object1 == 100);

    char *object3 = (char *) retrieveObject(id1);
    test("object3 should be NULL because id is NULL_REF", object3 == NULL);

    char *object4 = (char *) retrieveObject(-1);
    test("retrieve invalid ref, object4 should be NULL", object4 == NULL);

    destroyPool ();
}

void testDestroy () {
    initPool();

    id3 = insertObject(100);
    test("Insert first object", id3 == 1);
    id4 = insertObject(100);
    test("Insert second object", id4 == 2);

    printf("Before destroyPool\n");
    char *object1 = (char *) retrieveObject(id3);
    test("object1 should not be NULL before pool was destroyed", object1 != NULL);
    
    char *object2 = (char *) retrieveObject(id4);
    test("object2 should not be NULL before pool was destroyed", object2 != NULL);

    printf("---destroyPool---\n");
    destroyPool ();

    printf("After destroyPool\n");

    object1 = (char *) retrieveObject(id3);
    test("object1 was not NULL but should be NULL after pool was destroyed", object1 == NULL);
    
    object2 = (char *) retrieveObject(id4);
    test("object2 was not NULL but should be NULL after pool was destroyed", object2 == NULL);

    object2 = (char *) retrieveObject(5);
    test("object2 was not NULL but should be NULL after pool was destroyed", object2 == NULL);

}

void testDump () {
    initPool ();
    printf("Should print no object!\n");
    dumpPool ();
    printf("Add some objects\n");
    id1 = insertObject(1);
    id2 = insertObject(100);
    printf("Should print a list of objects!\n");
    dumpPool ();

    printf("---Destroy Pool---\n");
    destroyPool ();
    printf("dumpPool should print empty list\n");
    dumpPool ();
}

void testDestroyObject () {
    initPool ();
    printf("insert some objects\n");
    id1 = insertObject(100);
    id2 = insertObject(1000);
    id3 = insertObject(1);
    
    char *object1 = (char *) retrieveObject(id1);
    char *object2 = (char *) retrieveObject(id2);
    char *object3 = (char *) retrieveObject(id3);

    test("All objects retrieved should be not NULL", object1 != NULL && object2 != NULL && object3 != NULL);

    printf("delete 1 ref from object1, object1 should have 0 ref and be collected now\n");
    dropReference(id1);
    object1 = (char *) retrieveObject(id1);
    test("Object1 should be NULL when retrieving now", object1 == NULL);

    printf("addRef object2\n");
    addReference(id2);
    printf("dropRef object2\n");
    dropReference(id2);

    printf("object2 should be NOT NULL\n");
    object2 = (char *) retrieveObject(id2);
    test("Object2 should NOT be NULL when retrieving now", object2 != NULL);
    
    printf("dropRef object2, object2 should be collected after this\n");
    dropReference(id2);
    object2 = (char *) retrieveObject(id2);
    test("Object2 should be NULL when retrieving now", object2 == NULL);

    destroyPool ();
}

void testCompact () {
    initPool ();
    printf("Insert object that cover all memory of buffer\n");
    id1 = insertObject(MEMORY_SIZE);
    char *object1 = (char *) retrieveObject(id1);
    test("object should be inserted successfully", id1 == 1 && object1 != NULL);

    printf("Insert second object\n");
    id2 = insertObject(100);
    char *object2 = (char *) retrieveObject(id2);

    test("object2 should be inserted unsuccessfully", id2 == NULL_REF && object2 == NULL);

    printf("dropRef to object1 to destroy object 1\n");
    dropReference(id1);

    dumpPool ();

    printf("try to insert object2, should be successfully now because object1 was destroyed\nObjectManager should call compact\n");
    id2 = insertObject(100);
    object2 = (char *) retrieveObject(id2);

    test("object2 should be inserted successfully", id2 != NULL_REF && object2 != NULL);

    dumpPool ();

    destroyPool ();
}

void testCompactPartlyFull () {
    int i;

    initPool ();
    printf("Insert object1 - 100, object2 - 100, object3 - 100\nThen dropRef object2 to delete\nInsert object4 - MEMORY_SIZE-200 should be successful\n");
    id1 = insertObject(100);
    id2 = insertObject(100);
    id3 = insertObject(100);

    printf("Fill up object3\n");

    char *object3 = (char *) retrieveObject(id3);

    for (i = 0; i < 100; i ++) {
        object3[i] = 'A' + (i % 26);
    }

    dumpPool();

    printf("\nDrop ref of object -> destroy object2\n");
    dropReference(id2);

    dumpPool();

    printf("\nInsert object4\n");
    id4 = insertObject(MEMORY_SIZE-200);

    dumpPool();

    test("Object4 should be inserted successfully", id4 != NULL_REF);

    char *object4 = (char *) retrieveObject(id4);

    test("Object4 should be retrieved successfully", object4 != NULL);

    bool isSame = true;

    char *object3After = (char *) retrieveObject(id3);

    for (i = 0; i < 100; i ++) {
        isSame = isSame && (object3[i] = object3After[i]);
    }

    test("Object3 should be the same as before compact", isSame);

    destroyPool ();
}


