#include <stdio.h>

#include "test.h"
#include "set.h"

//----------------------------------------------------------
// PROTOTYPES
//----------------------------------------------------------

void testValidateMemUse ();

void testInsert ();

void testRemoveItems ();

void testDeleteSet ();

void testAreEqual ();

void testAreDisjoint ();

void testUnionOf ();

void testSymmetricDifferenceOf ();

void testDelete ();

void insertArray (int *array, int length);
void removeArray (int *array, int length);



//----------------------------------------------------------
// IMPLEMENTATION
//----------------------------------------------------------

int main () {
    testCase("ValidateMemUse with newSet and deleteSet", testValidateMemUse);
}

void testValidateMemUse () {

}
