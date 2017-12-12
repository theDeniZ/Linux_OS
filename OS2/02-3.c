#include <stdio.h>
int main(int argc, char *argv[], char *envp[])
{
	int i = 0;
    printf("argc = %d\n", argc);
	while (i < argc){
		printf("argv[%d] = '%s'\n", i, argv[i]);
		i += 1;
	}
	i = 0;
	while (envp[i] != NULL){
		printf("envp[%d] = '%s'\n", i, envp[i]);
		i += 1;
	}
    return 0; 
}
