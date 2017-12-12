#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[], char *envp[]){

execle("./1.out", "./1.out", "02-4.c", NULL, envp); 
printf("Error on program start\n");
exit(-1);
return 0;
}
