#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <errno.h>
int main()
{
int *array;
int shmid;
int new = 1;
char pathname[]="shm-a.c";
key_t key;

   int semid;
   char pathname_sh[] = "shm-a.c";
   key_t key_sh;
   struct sembuf mybuf;
   if((key_sh = ftok(pathname_sh,0)) < 0){
      printf("Can\'t generate key\n");
      exit(-1); 
   }
   if((semid = semget(key_sh, 1, 0666 | IPC_CREAT)) < 0){ 
      printf("Can\'t get semid\n");
      exit(-1); 
   }

if((key=ftok(pathname,0)) < 0){
printf("Can\'t generate key\n");
exit(-1);
}

if((shmid=shmget(key,3*sizeof(int),0666|IPC_CREAT))<0){
if(errno!=EEXIST){
printf("Can\'t create shared memory\n");
exit(-1);
}
}
if((array=(int*)shmat(shmid,NULL,0))==(int*)(-1)){
printf("Can't attach shared memory\n");
exit(-1);
}

printf("%d %d %d ",array[0],array[1],array[2]);

   mybuf.sem_op = 1;
   mybuf.sem_flg = 0;
   mybuf.sem_num = 0;
   if(semop(semid, &mybuf, 1) < 0){
      printf("Can\'t wait for condition\n");
      exit(-1); 
   }

   mybuf.sem_op = -1;
   mybuf.sem_flg = 0;
   mybuf.sem_num = 0;
   if(semop(semid, &mybuf, 1) < 0){
      printf("Can\'t wait for condition\n");
      exit(-1); 
   }

printf("%d %d %d ",array[0],array[1],array[2]);

if(shmdt(array)<0){
printf("Can't detach shared memory\n");
exit(-1);
}
return 0;
}
