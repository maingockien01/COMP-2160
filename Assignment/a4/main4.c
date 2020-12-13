#include "Object.h"
#include <stdio.h>

struct LUCKY
{
  int value1;
  int value2;
};

typedef struct LUCKY lucky;

void sub_tester( Object<lucky> obj )
{
  obj->value1 = 987;
  obj->value2 = 345;
}

void tester()
{
  Object<lucky> test;

  test->value1 = 456;
  test->value2 = 999;

  sub_tester( test );

  fprintf( stderr, "Is this right? %d %d\n", test->value1, test->value2 );
}

int main( int argc, char *argv[] )
{
  initPool();
  
  tester();

  destroyPool();
  
  return 0;
}
