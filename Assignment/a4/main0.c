/*
 * main0.c
 * COMP 2160 Programming Practices
 * Assignment 4 
 */
 
#include "ObjectManager.h"
#include <stdio.h>
#include <assert.h>

int main(int argc, char *argv[])
{
  char *ptr;
  int i;
  Ref id1,id2,id3;
  initPool();
  
  id1= insertObject(100);
  printf("id1 = %lu\n", id1);
  ptr = (char*)retrieveObject(id1);
  for (i = 0; i < 100; i++) {
    ptr[i] = (char)(i%26 + 'A');
    printf("Kien");
  }
  assert(ptr[0] == 'A');
  
  id2 = insertObject(4000);
  id3 = insertObject(20200);
  dropReference(id3);
  addReference(id2);
  id3 = insertObject(10);
  
  ptr = (char*)retrieveObject(id1);
  assert(ptr != NULL);
  for (i = 0; i < 100; i++)
    fprintf(stdout,"%c",ptr[i]);
  fprintf(stdout,"\n");
  
  dumpPool();
  destroyPool();
  fprintf(stdout,"---\n");
  return 0;
}

