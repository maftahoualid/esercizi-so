
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX 9000
//ha una memoria condivisa, prende da input un intero e dentro la memoria condivisa ci saranno due array da 10 randomici
//il programma fa una fork dove dentro la fork il figlio fa la somma degli array all'indice dato da input
//poi viene passato tramite una fifo e un 'exec
//l'altro programma prende la somma dalla fifo e poi fa una fork e mette il risultato in ogni posizione degli array nell mem condivisa
int main(int argc, char * argv){
    key_t chiave = ftok("cicciogamer.txt", 'a');
    struct array{
        int a[10];
        int b[10];  
    };

    int shmid = shmget(chiave, sizeof(struct array), IPC_CREAT | S_IRUSR | S_IWUSR);
    if(shmid == -1){
        printf("shmget porcodio\n");
    }
    struct array * array = shmat(shmid, NULL, 0);
    int fif = open("cicciogamer2.txt", O_RDONLY);
    char buf[10];
    
    
    read(fif, buf, 10);
    
    for(int i = 0; i < 10; i++){
        array->a[i] = atoi(buf);
        array->b[i] = atoi(buf);
    }
    printf("array a: \n");
    for(int i = 0; i < 10; i++){
        printf("%i ", array->a[i]);
    }
    printf("\n");
    printf("array b: \n");
    for(int i = 0; i < 10; i++){
        printf("%i ", array->b[i]);
    }
    printf("\n");
    
}