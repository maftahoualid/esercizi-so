#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

void sigalrmHandler(){ printf("Che bella dormita\n"); }

int main(int argc, char** argv) {

    if(argc!=2){
        printf("Usage: %s <seconds>\n",argv[0]);
        return 1;
    }
    int sleepFor = atoi(argv[1]);
    if( sleepFor <= 0){ return 1; }

    if(signal(SIGALRM,sigalrmHandler)==SIG_ERR){ perror("signal"); exit(EXIT_FAILURE); }

    alarm(sleepFor);
    pause();

    return 0;
}