#include "es1.h"

int msq_id=-1, msq_key;

int main(int argc, char* argv[]){

    msq_key = 100;
    msq_id = msgget(msq_key,S_IRUSR | S_IWUSR);

    msg messaggio = (msg) { .mtype=0, .code=1, .description="descrizione dell'ordine", .quantity=1, .email="email@email.com" };
    ssize_t size = sizeof(msg) - sizeof(long);

    if(msgsnd(msq_id,&messaggio,size,0) == -1 ){ perror("msgsnd"); exit(EXIT_FAILURE); }
    return 0;
}