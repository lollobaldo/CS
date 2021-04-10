#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void read_secret() {
  FILE *fptr = fopen("/task2/secret.txt", "r");
  char secret[1024];
  fscanf(fptr, "%512s", secret);
  printf("Well done!\nThere you go, a wee reward: %s\n", secret);
  exit(0);
}

int fib(int n)
{
  if ( n == 0 )
    return 0;
  else if ( n == 1 )
    return 1;
  else
    return ( fib(n-1) + fib(n-2) );
} 

void vuln(char *name)
{
  int n = 20;
  char buf[1094];
  int f[n];
  int i;
  for (i=0; i<n; i++) {
    f[i] = fib(i);
  }
  strcpy(buf, name);
  printf("Welcome %s!\n", buf);
  for (i=0; i<20; i++) {
    printf("By the way, the %dth Fibonacci number might be %d\n", i, f[i]);
  } 
}


int main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("Tell me your names, tricksy hobbitses!\n");
    return 0;
  }
  
  // printf("main function at %p\n", main);
  // printf("read_secret function at %p\n", read_secret);
  vuln(argv[1]);
  return 0;
}
