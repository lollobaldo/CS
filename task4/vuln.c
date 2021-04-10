#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void vuln(char *name, int index)
{
  char buf[1094] =  "Let's see if it works!?!!";
  printf("Old buffer: %s\n", buf);
  char *ptr = buf + index;
  strncpy(ptr, name, 128);
  printf("New buffer: %s\n", buf);
  printf("Fresh data: %s\n", ptr);
}

int main(int argc, char *argv[])
{
  setreuid(geteuid(), geteuid());
  if (argc < 3) { 
    printf("Please enter new data and offset");
    return 1;
  }
  vuln(argv[1], atoi(argv[2]));
  printf("Returned to main\n");
  return 0;
}
