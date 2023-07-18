#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <wait.h>

/**
 * figlio1: ogni 3s stampa ...
 * figlio2: invia SIGSTOP ogni 10s a figlio1
 * parent: check ogni 15s
 *
 * check : se figlio1 è stoppato, parent manda SIGCONT
 * se utente manda SIGINT a parent: parent termina figlio1 e figlio2 con SIGTERM, poi termina
 */

pid_t pid1,pid2,pid3;

void sigHandlerParent(int sig){
    switch (sig) {
        case SIGINT:
            printf("SIGINT");
            kill(pid1, SIGTERM);
            kill(pid2, SIGTERM);
            exit(0);
            break;
        default:
            break;
    }
}
void sigHandlerChild(int sig){
    switch (sig) {
        case SIGTERM:
            exit(0);
            break;
        default:
            break;
    }
}

void check(){
    int status;
    pid_t pid = waitpid(pid1,&status,WNOHANG | WUNTRACED);
    if(pid==-1){ perror("waitpid"); exit(EXIT_FAILURE); }

    if(pid!=0 && WIFSTOPPED(status)){
        printf("\n<parent> resuming <figlio1>\n");
        if( kill(pid1, SIGCONT)==-1 ) { perror("kill sigcont"); exit(EXIT_FAILURE); }
    }
}

int main(){

    sigset_t sigset;
    sigfillset(&sigset);

    pid1 = fork();
    if(pid1==-1){ perror("fork"); exit(EXIT_FAILURE); }

    if(pid1==0) {
        sigdelset(&sigset, SIGTERM);
        signal(SIGTERM, sigHandlerChild);
        sigprocmask(SIG_SETMASK,&sigset,NULL);
        while(1){
            printf("\n<figlio1> working\n");
            sleep(3);
        }
    }

    pid2 = fork();
    if(pid2==-1){ perror("fork"); exit(EXIT_FAILURE); }

    if(pid2==0){
        sigdelset(&sigset, SIGTERM);
        signal(SIGTERM, sigHandlerChild);
        sigprocmask(SIG_SETMASK,&sigset,NULL);
        while(1){
            printf("\n<figlio2> stopping <figlio1>\n");
            kill(pid1,SIGSTOP);
            sleep(10);
        }
    }

    pid3 = fork();
    if(pid3==-1){ perror("fork"); exit(EXIT_FAILURE); }

    if(pid3==0){
        while(1) {
            static int i=1;
            printf("%d ",i);
            fflush(stdout);
            sleep(1);
            i++;
        }
    }

    sigdelset(&sigset, SIGINT);
    signal(SIGINT, sigHandlerParent);
    sigprocmask(SIG_SETMASK,&sigset,NULL);

    while(1){
        check();
        sleep(15);
    }

    return 0;
}
