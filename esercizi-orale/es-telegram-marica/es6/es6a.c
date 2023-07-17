
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
#include <string.h>

#define MAX 9000
//ha una memoria condivisa, prende da input un intero e dentro la memoria condivisa ci saranno due array da 10 randomici
//il programma fa una fork dove dentro la fork il figlio fa la somma degli array all'indice dato da input
//poi viene passato tramite una fifo e un 'exec
//l'altro programma prende la somma dalla fifo e poi fa una fork e mette il risultato in ogni posizione degli array nell mem condivisa
int main(int argc, char * argv[]){
    key_t chiave = ftok("cicciogamer2.txt", 'a');
    int r = atoi(argv[1]);
    struct array{
        int a[10];
        int b[10];  
    };
    struct array * array;
    srand(time(NULL));
    ssize_t size = sizeof(struct array);
    int shmid = shmget(chiave, size, IPC_CREAT | S_IRUSR | S_IWUSR);
    if(shmid == -1){
        printf("shmget porcodio\n");
    }
    printf("porcodio\n");
    array = shmat(shmid, NULL, 0);
    for(int i = 0; i < 10; i++){ //memoria condivisa creata e allocata
        array->a[i] = rand() % 10 + 1;
        array->b[i] = rand() % 10 + 1;
    }
    for(int i = 0; i < 10; i++){
        printf("%i ", array->a[i]);
    }
    int fif = mkfifo("cicciogamer2.txt", S_IWUSR | S_IRUSR);
    int wr = open("cicciogamer2.txt", O_WRONLY);
    printf("porcodio\n");
    pid_t figliolo = fork();
    if(figliolo == 0){
        int sum = array->a[r] + array->b[r];
        printf("%i\n", sum);
        exit(sum);
    }
    int status;
    wait(&status);
    char buff[10];
    printf("porcodio\n");
    sprintf(buff, "%d", WEXITSTATUS(status));
    printf("%s\n", buff);
    write(wr, buff, strlen(buff));
    execl("./marco2", "./marco2", argv[1], NULL);
    printf("porcodio\n");
    printf("Programma terminato\n");
    shmdt(array);
    shmctl(shmid, IPC_RMID, 0);
}