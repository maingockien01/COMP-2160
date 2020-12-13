#include "Object.h"
#include <stdio.h>

#define OBJECTS 1000UL

struct ALF
{
  int value;
  double d;
  char buffer[1024*128];
};

typedef struct ALF alf;

int main( int argc, char *argv[] )
{
  initPool();

  Object<alf> obj1;
  Object<alf> obj2;
  Object<alf> obj3;
  Object<alf> obj4;
  Object<alf> obj5;
  Object<alf> obj6;

  destroyPool();

  return 0;
}
