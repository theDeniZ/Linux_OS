#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
int main()
{
    pid_t pid, ppid, neww;

    int a = 0;
    neww = fork();

    if ( neww == -1){
	printf("Error");
    } else if (neww == 0){
 	printf("Child!\t");
	a += 2;
    } else {
	printf("Parent, new child's name is %d\t", neww);
    }
    a = a+1;

    pid = getpid();
    
    ppid = getppid();

    printf("My pid = %d, my ppid = %d, result = %d\n", (int)pid, (int)ppid, a);
    return 0; 
}
