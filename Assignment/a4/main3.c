#include "Object.h"
#include <stdio.h>

struct ALF
{
  int value;
  double d;
};

typedef struct ALF alf;

void tester()
{
  Object<alf> test;
  Object<alf> test2;
  Object<alf> test3;

  test->value = 5;
  test2->value = 10;
  fprintf( stdout, "%d\n", test->value );
  test = test2;
  fprintf( stdout, "%d\n", test->value );
  test2 = NULL;
  fprintf( stdout, "%d\n", test2->value );
}

int main( int argc, char *argv[] )
{
  int i;
  
  initPool();

  for ( i=0 ; i<100 ; i++ )
    tester();

  destroyPool();
  
  return 0;
}
