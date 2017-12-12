#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
int main(int argc, char *argv[]){
        int fd[2], result;
	size_t size;
	int magicNumber = 0;
	char resstring[255];


	if ( argc != 3) {
		printf("Wrong params\n");
		exit(-1);
	}

	while (argv[1][magicNumber] != '\0' ) { magicNumber += 1; }
magicNumber += 1;
	//printf("Count = %d", magicNumber);

	if(pipe(fd) < 0){
	    printf("Can\'t create pipe\n");
	    exit(-1);
	}

	result = fork();
	if(result == -1){

	printf("Can\'t fork child\n");
	exit(-1);

	} else if (result > 0) {
	    close(fd[0]);
	    size = write(fd[1], argv[1], magicNumber);
	    if(size != magicNumber){
		printf("Can\'t write all string\n");
		exit(-1);
	    }
	    close(fd[1]);
	    printf("Parent exit\n");
	} else {
	    close(fd[1]);
	    size = read(fd[0], resstring, magicNumber);
	    if(size < 0){
		printf("Can\'t read string\n");
		exit(-1);
	    }

	    //printf("%s\n",resstring);
	    close(fd[0]);
	    execl(resstring, resstring, argv[2], NULL);
	    
	}
	return 0; 
}
