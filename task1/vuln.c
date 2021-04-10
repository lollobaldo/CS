#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv){
  volatile unsigned int pidgeon = 0xe0e5b330;
  unsigned int correct_pwd = 0;

   char pwd[170];
  volatile unsigned int rooster = 0x43ff88e4;
   char entered_pwd[170];

  FILE *fptr = fopen("/task1/password.txt", "r");

  if(fptr == NULL){
    printf("Error opening password vault!\n");
    exit(1);
  }

  fscanf(fptr, "%s", pwd);
  fclose(fptr);

  scanf("%s", entered_pwd);

  sleep(1);
  if(strcmp(entered_pwd, pwd)){
    printf("Incorrect password\n");
  }
  else{
    correct_pwd = 1;
    printf("Correct password\n");
  }

  if (pidgeon != 0xe0e5b330|| rooster != 0x43ff88e4) {
    printf("Stack smashing detected!!");
    return 0;
  }
  else if(correct_pwd) {
    printf("\nYou are now authenticated, you deserve a cookie!\n");
    fptr = fopen("/task1/secret.txt", "r");
    if (fptr == NULL) {
        printf("But the cookie jar is broken...\n");
    }
    char secret[1024];
    fscanf(fptr, "%s", secret);
    fclose(fptr);
    printf("%s", secret);
  }
  return 0;
}
