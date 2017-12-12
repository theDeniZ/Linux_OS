#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define LAST_MESSAGE 255 
int main()
{
    int msqid; 
    char pathname[] = "server.c"; 
    key_t key; 
    int i,len; 

    struct mymsgbuf
    {
        long mtype;
	struct info
{      
        int pid;
	char strInfo[255];
}info;	  
    } mybuf;

    if((key = ftok(pathname,0)) < 0){
        printf("Can\'t generate key\n");
        exit(-1); 
    }
    if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
        printf("Can\'t get msqid\n");
        exit(-1); 
    }
    
        
        mybuf.mtype = 1;
	mybuf.info.pid = getpid();
	
        len = sizeof(int)+255;
        
        if (msgsnd(msqid, (struct msgbuf *) &mybuf,
            len, 0) < 0){
            printf("Can\'t send message to queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(-1);
        } 
    
	if((len = msgrcv(msqid,(struct msgbuf *) &mybuf, len, getpid(), 0)) < 0){
            printf("Can\'t receive message from queue\n");
            exit(-1);
        }
    printf("%s", mybuf.info.strInfo);
    return 0; 
}
