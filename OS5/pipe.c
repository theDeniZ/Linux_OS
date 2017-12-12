#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
int main(){
        int fd[2], result;
	size_t size;
	char resstring[14];

   int semid;
   char pathname[] = "05-1a.c";
   key_t key;
   struct sembuf mybuf;
   if((key = ftok(pathname,0)) < 0){
      printf("Can\'t generate key\n");
      exit(-1); 
   }
   if((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0){ 
      printf("Can\'t get semid\n");
      exit(-1); 
   }

   


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
	    size = write(fd[1], "Hello, world!", 14);
	    if(size != 14){
		printf("Can\'t write all string\n");
		exit(-1);
	    }

   mybuf.sem_op = -1;
   mybuf.sem_flg = 0;
   mybuf.sem_num = 0;
   if(semop(semid, &mybuf, 1) < 0){
      printf("Can\'t wait for condition\n");
      exit(-1); 
   }
   printf("Condition is received\n");

	    size = write(fd[1], "Hello, son!!!", 14);
	    if(size != 14){
		printf("Can\'t write all string\n");
		exit(-1);
	    }
	    close(fd[1]);
	    printf("Parent exit\n");
	} else {
	    close(fd[1]);
	    size = read(fd[0], resstring, 14);
	    if(size < 0){
		printf("Can\'t read string\n");
		exit(-1);
	    }
	    printf("%s\n",resstring);

   mybuf.sem_op = 1;
   mybuf.sem_flg = 0;
   mybuf.sem_num = 0;
   if(semop(semid, &mybuf, 1) < 0){
      printf("Can\'t wait for condition\n");
      exit(-1); 
   }
   printf("Condition is set\n");

	    size = read(fd[0], resstring, 14);
	    if(size < 0){
		printf("Can\'t read string\n");
		exit(-1);
	    }
	    printf("%s\n",resstring);
	    close(fd[0]);
	}
	return 0; 
}
