#include <stdio.h>
#include <stdlib.h>

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

int main( int argc, char *argv[] )
{
  // we really should check the input...
  int fibNum = atoi(argv[1]);
  
  printf("The %d Fibonacci number is %ld\n", fibNum, fib(fibNum));
  
  return EXIT_SUCCESS;
}
