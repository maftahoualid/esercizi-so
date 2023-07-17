
/*
due vettori di 10 interi casuali in memoria condivisa.
il padre genera 10 figli ed ognuno si connette alla memoria e fa la somma dell'elemento i-esimo e lo ritorna come exit code.
il padre intercetta il valore di ritorno dei figli e lo salva in un vettore risultato
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>

struct vettori{
    int a[10];
    int b[10];
};

//struct vettori * vettori;

int main(int argc, char * argv){
    int res[10];
    struct vettori * vettori;
    int sum;
    srand(time(NULL));
    //creo la memoria condivisa
    int chiave = ftok("chaivemem.txt", 'a');
    int shmid = shmget(IPC_PRIVATE, sizeof(vettori), IPC_CREAT | S_IRUSR | S_IWUSR);
    vettori = (struct vettori *)shmat(shmid, NULL, 0);

    for(int i = 0; i < 10; i++){
        vettori->a[i] = rand() % 100 + 1;
        vettori->b[i] = rand() % 100 + 1;
    }
    pid_t figliolo;
    //generazione processi figli
    for(int i = 0; i < 10; i++){
        figliolo = fork();
        
        if(figliolo == -1){
            printf("figlio non nato\n");
        }else if(figliolo == 0){
            sum = vettori->a[i] + vettori->b[i];
            shmdt(vettori);
            exit(sum);
        }
        int status;
        wait(&status);
        if(WIFEXITED(status))
            res[i] = WEXITSTATUS(status);
    }
    
    
    printf("matrice a: ");
    for(int i = 0; i < 10; i++){
        printf("%i ", vettori->a[i]);
    }
    printf("\n");
    printf("matrice b: ");
    for(int i = 0; i < 10; i++){
        printf("%i ", vettori->b[i]);
    }
    printf("\n");
    printf("matrice somma: ");
    for(int i = 0; i < 10; i++){
        printf("%i ", res[i]);
    }
    printf("\n");

    //detach e rimozione memoria condivisa
    if(shmdt(vettori) == -1){
        printf("detach fallito\n");
    }
    if(shmctl(shmid, IPC_RMID, 0) == -1){
        printf("rimozione memoria fallita\n");
    }
    return 0;
}