#include <stdio.h>
#include <stdlib.h>

#define UNCALCULATED -1

long getFib (int n);

/**
long fib(int n)
{
  long result;
  
  if (n==0)
    result = 0;
  else if (n==1 || n==2)
    result = 1;
  else
    result = fib(n-1) + fib(n-2);
  
  return result;
}
*/

int main( int argc, char *argv[] )
{

  // we really should check the input...
  int fibNum = atoi(argv[1]);
  
  printf("The %d Fibonacci number is %ld\n", fibNum, getFib(fibNum+1));
  
  return EXIT_SUCCESS;
}


long getFib (int n) {
    int i;
    long cache[n];
    for (i = 0; i < n; i ++) {
        cache[i] = UNCALCULATED;
    }
    cache[0] = 0;
    cache[1] = 1;
    for (i = 2; i < n; i ++) {
        cache[i] = cache[i-1] + cache[i-2];
    }

    return cache[n-1];
}
