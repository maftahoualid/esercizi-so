#include "es1.h"

int msq_id, msq_key;

void sigHandler(int sig){
    switch (sig){
        case SIGTERM:
            if(msgctl(msq_id,IPC_RMID,NULL)==-1){ perror("msgctl ipc_rmid"); exit(EXIT_FAILURE); };
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
    }
}

int main(int argc, char* argv[]){

    sigset_t sigset;
    sigfillset(&sigset);
    sigdelset(&sigset,SIGTERM);
    sigprocmask(SIG_SETMASK,&sigset,NULL);
    signal(SIGTERM,sigHandler);

    msq_key = 100;
    msq_id = msgget(msq_key,IPC_CREAT | S_IRUSR | S_IWUSR);
    msg messaggio = (msg) { .mtype=0, .code=0, .description="", .quantity=0, .email="" };
    ssize_t size = sizeof(msg) - sizeof(long);

    while(1) {
        if(msgrcv(msq_id, &messaggio, size, (long) 0, 0)==-1) {
            perror("msgrcv");
        } else {
            printf("Messaggio ricevuto:\n");
            printf("mtype: %ld\n", messaggio.mtype);
            printf("code: %d\n", messaggio.code);
            printf("description: %s\n", messaggio.description);
            printf("quantity: %d\n", messaggio.quantity);
            printf("e-mail: %s\n", messaggio.email);
            printf("\n");
        }
    }

    return 0;
}