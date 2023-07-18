#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// eseguire, su un altro terminale:
// kill -SIGKILL <pid>
// per terminare il processo

void sigintHandler(){ printf("CTRL-C non mi può fermare\n"); }

int main(int argc, char** argv){
    sigset_t sigset;
    sigfillset(&sigset);
    sigdelset(&sigset, SIGINT);
    sigprocmask(SIG_SETMASK,&sigset,NULL);
    if(signal(SIGINT,sigintHandler)==SIG_ERR){ perror("signal"); exit(EXIT_FAILURE); }

    while(1){
        printf("Ciao, io sono un processo in esecuzione (%d)\n", getpid());
        unsigned int t=5;
        while( t != 0 ){
            t = sleep(t);
        }
    }
}