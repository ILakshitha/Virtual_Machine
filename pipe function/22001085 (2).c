#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {

    int fd[2];

    int pipeId = pipe(fd);
    if(pipeId == -1) {
        printf("Error: Failed pipe\n");
        return 1;
    } 
    
    int id = fork();
    if (id == -1) {
        printf("Error: Failed fork\n");
        return 2;
    }

    if (id == 0) {
        close(fd[1]);
        char y[20];
        read(fd[0], y, sizeof(y));
        printf("%s\n", y);
        close(fd[0]);
    }
    else {
        close(fd[0]);
        char x[20] = "Hello, from parent";
        write(fd[1], x, sizeof(x));
        close(fd[1]);
    }
    return 0;
}
