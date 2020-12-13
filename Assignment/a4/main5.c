#include "Object.h"
#include <stdio.h>

#define OBJECTS 1000

struct LUCKY
{
  int value1;
  int value2;
};

typedef struct LUCKY lucky;

struct ALF
{
  double value;
  double day;
  char buffer[256];
};

typedef struct ALF alf;


void subTester( Object<alf>& obj, Object<lucky> objects[] )
{
  int i;
  Object<alf> more[OBJECTS/4];

  for ( i=0 ; i<OBJECTS ; i++ )
    fprintf( stderr, "lucky object %d: %d %d\n", i, objects[i]->value1, objects[i]->value2 );

  obj->value = 2.71719;
}

void tester( int stdPrint )
{
  int i;
  Object<alf> test;
  Object<lucky> objects[OBJECTS];

  for ( i=0 ; i<OBJECTS ; i++ )
  {
    objects[i]->value1 = i;
    objects[i]->value2 = i*2;
  }

  test->value = 3.14159;
  
  if ( stdPrint )
    fprintf( stdout, "before: %2.5f\n", test->value );
  else
    fprintf( stderr, "before: %2.5f\n", test->value );

  subTester( test, objects );

  if ( stdPrint )
    fprintf( stdout, "after: %2.5f\n", test->value );
  else
    fprintf( stderr, "after: %2.5f\n", test->value );
}

void initialTester()
{
  int i;
  // lets keep a bunch of object around for a while...
  Object<alf> objects[OBJECTS];

  for ( i=0 ; i<5 ; i++ )
    tester( (i==4) );
}

int main( int argc, char *argv[] )
{
  int i;
  
  initPool();

  for ( i=0 ; i<4 ; i++ )
  {
    initialTester();
  }
  
  destroyPool();
  
  return 0;
}
