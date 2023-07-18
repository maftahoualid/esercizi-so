#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <wait.h>
#include <time.h>

int main(int argc,char** argv){
    if(argc<=1){
        printf("usage: %s <cmd> <arg>\n", argv[0]);
        return 0;
    }

    pid_t pid = fork();
    if(pid==-1){ perror("fork"); exit(EXIT_FAILURE); }
    else if(pid==0){
        int fd = open("file.txt", O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
        if(!fd){ perror("open"); }
        dup2(fd, 1);
        dup2(fd, 2);
        execvp(argv[1], &argv[1]);
        perror("execvp"); exit(EXIT_FAILURE);
    }
    int status;
    if(!wait(&status)){ perror("wait"); exit(EXIT_FAILURE); }
    printf("Command %s exited with status %d\n",argv[1], WEXITSTATUS(status));
    return 0;
}