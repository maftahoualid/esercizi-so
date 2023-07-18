#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <wait.h>
#include <time.h>

#define BUFFER_SZ 128

int main(int argc,char** argv){
    srand(time(NULL));

    if(argc!=2){ printf("usage: %s <num sub processes>\n",argv[0]); return 0; }
    int n = atoi(argv[1]);
    if(n<0){ printf("<num sub processes> > 0 !!\n"); return 1; }

    srand(time(NULL));

    pid_t pid;
    for(int i=0; i<n; i++) {
        int code = (int)( ((double)rand() / RAND_MAX) * 255 );
        pid = fork();
        if(pid==-1){ printf("child %d not created\n",i); }
        else if(pid==0){
            printf("pid: %d - parent pid: %d - code: %d\n",getpid(),getppid(),code);
            exit(code);
        }
    }

    int status, ret;
    do{
        ret = waitpid(pid,&status,WNOHANG);
        if(ret==-1){ perror("waitpid"); }
    } while (ret==0);

    printf("Child %d exited, with status: %d\n",pid, WEXITSTATUS(status));
    return 0;
}