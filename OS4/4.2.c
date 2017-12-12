#include <pthread.h>
#include <stdio.h>
int a=0;
void *mythread(void *dummy)
{
pthread_t mythid;
mythid=pthread_self();
a=a+1;
printf("Thread %d, Calculation result = %d\n",mythid,a);
return NULL;
}

void *mysecondthread(void *dummy)
{
pthread_t mythid;
mythid=pthread_self();
a=a+10;
printf("Thread %d, Calculation result = %d\n",mythid,a);
return NULL;
}

int main()
{
pthread_t thid, thid2, mythid;
int result;
result=pthread_create(&thid,(pthread_attr_t *)NULL,mythread,NULL);
if(result!=0){
printf("Error on thread create, return value = %d\n",result);
exit(-1);
}
printf("Thread created, thid = %d\n",thid);

result=pthread_create(&thid2,(pthread_attr_t *)NULL,mysecondthread,NULL);
if(result!=0){
printf("Error on thread create, return value = %d\n",result);
exit(-1);
}
printf("Thread created, thid = %d\n",thid2);

mythid=pthread_self();
a=a+1;

pthread_join(thid, (void **)NULL);
pthread_join(thid2, (void **)NULL);
printf("Thread %d, Calculation result = %d\n",mythid,a);
return 0;
}
