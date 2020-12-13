#include "Object.h"
#include <stdlib.h>
#include <stdio.h>

#define OBJECTS 2000L

struct ALF
{
  int value;
  double d;
  char buffer[1024];
};

typedef struct ALF alf;

void tester( int stdPrint )
{
  double x;
  Object<alf> test;
  static Object<alf> me;

  test->value = rand();
  fprintf( stderr, "%d\n", test->value );
  x = test->d;

  if ( stdPrint )
    fprintf( stdout, "%f\n", x );
  else
    fprintf( stderr, "%f\n", x );
}

int main( int argc, char *argv[] )
{
  long i;

  initPool();
  
  for ( i=0 ; i<OBJECTS ; i++ )
    tester( i==(OBJECTS-1) );

  destroyPool();
  
  return 0;
}
