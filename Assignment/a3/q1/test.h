#include "table.h"

#ifndef _TEST_H
#define _TEST_H
void testCase(char *desc, void (*testFunction)());
void test (char *desc, Boolean expectTrue);
Boolean expectEqual (int expect, int actual);
Boolean expectNull (void* value);
Boolean expectNotNull (void *value);

void reportTest ();
#endif
