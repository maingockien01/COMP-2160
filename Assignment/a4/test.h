#ifndef _TEST_H
#define _TEST_H
#include<stdbool.h>

void testCase(char const * desc, void (*testFunction)());
void test (char const * desc, bool expectTrue);
bool expectEqual (int expect, int actual);
bool expectNull (void* value);
bool expectNotNull (void *value);

void reportTest ();
#endif
