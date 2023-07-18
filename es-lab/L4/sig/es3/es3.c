#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <wait.h>

pid_t pid1,pid2;

void sigHandlerParent(int sig){
    switch (sig) {
        case SIGUSR1:
            printf("<parent> SIGUSR1 ricevuto!\n");
            printf("<parent> invio SIGUSR1 a <figlio2>\n\n");
            kill(pid2,SIGUSR1);
            break;
        case SIGUSR2:
            printf("<parent> SIGUSR2 ricevuto!\n");
            printf("<parent> invio SIGUSR2 a <figlio1>\n\n");
            kill(pid1,SIGUSR2);
            break;
        default:
            break;
    }
}
void sigHandlerChild1(int sig){
    switch (sig) {
        case SIGUSR2:
            printf("<figlio1> SIGUSR2 ricevuto!\n\n");
            break;
        default:
            break;
    }
}
void sigHandlerChild2(int sig){
    switch (sig) {
        case SIGUSR1:
            printf("<figlio2> SIGUSR1 ricevuto!\n");
            printf("<figlio2> invio SIGUSR2 a <parent>\n\n");
            kill(getppid(),SIGUSR2);
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
    }
}

int main(){

    sigset_t sigset;
    sigfillset(&sigset);
    sigdelset(&sigset,SIGUSR1);
    sigdelset(&sigset,SIGUSR2);
    sigprocmask(SIG_SETMASK,&sigset,NULL);
    signal(SIGUSR1,sigHandlerParent);
    signal(SIGUSR2,sigHandlerParent);

    pid1 = fork();
    if(pid1==-1){ perror("fork"); exit(EXIT_FAILURE); }

    if(pid1==0){
        signal(SIGUSR1,sigHandlerChild1);
        signal(SIGUSR2,sigHandlerChild1);

        printf("<figlio1> invio SIGUSR1 a <parent>\n\n");
        kill(getppid(),SIGUSR1);
    }

    pid2 = fork();
    if(pid2==-1){ perror("fork"); exit(EXIT_FAILURE); }

    if(pid2==0){
        signal(SIGUSR1,sigHandlerChild2);
        signal(SIGUSR2,sigHandlerChild2);
    }

    while(wait(NULL)==-1){
        pause();
    }

    return 0;
}
