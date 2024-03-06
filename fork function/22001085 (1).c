#include<stdio.h>
#include<unistd.h>

int main(){
    printf("PARENT\n");
    printf("parent process ID =%d\n",getpid());

    int PID;
    PID = fork();
    if(PID==0){
        printf("CHILD 1\n");
        printf("first child process ID = %d\t",getpid());
        printf("parent process ID =%d\n", getppid());

    }else{
        PID = fork();
        if(PID==0){
            printf("CHILD 2\n");
            printf("second child process ID = %d\t",getpid());
            printf("parent process ID =%d\n", getppid());
        }
    }
    return 0;
}