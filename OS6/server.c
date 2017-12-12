#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define LAST_MESSAGE 255
int main()
{
    int i;
    int msqid;
    char pathname[] = "server.c";
    key_t key;
    int len, maxlen; 

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
i = 0;
    while(1)
    {
        maxlen = 255+sizeof(int);
	if((len = msgrcv(msqid,(struct msgbuf *) &mybuf, maxlen, 1, 0)) < 0)
        {
	    printf("Can\'t receive message from queue\n");
            exit(-1);
        }
        
	if (mybuf.mtype == 1) 
	{
	    mybuf.mtype = mybuf.info.pid;
	    sprintf(mybuf.info.strInfo, "Msg %d Client PID: %d Server PID: %d\n ", i+=1, mybuf.info.pid, getpid());
	    mybuf.info.pid = getpid();	    
	    if((len = msgsnd(msqid,(struct msgbuf *) &mybuf, len, 0)) < 0)
	    {
                printf("Can\'t send message from queue\n");
                exit(-1);
            }
        }

        
    }
    return 0;
}
