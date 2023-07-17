/*
ESERCIZI
principalmente sulle pipe/fifo e sulla fork/exec/wait 
visto che non erano richieste nell'elaborato. Di seguito alcuni dei possibili esercizi. 

"modifica" al progetto scrivendo un programma che si collega alla memoria 
condivisa e fa da "spettatore" leggendo la memoria condivisa e stampando la griglia. 
la chiave della shm si può passare da riga di comando

padre figlio con il figlio che fa "ls -alr /" e il padre scrive lo
stdout sul file e lo stderr su un altro file
*/

/*
padre e figlio collegati da una pipe. Il figlio esegue exec("ls") 
e il padre scrive il risultato su un file
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
#include <fcntl.h>

#define MAX 100

int fd[2];

int main(int argc, char * argv){
    int fd = open("dragogay.txt", O_WRONLY);
    dup2(fd, STDOUT_FILENO); //cambio gli out e sa che è in lettura con la flag
    execlp("ls", "ls", NULL);

    printf("CIAO\n");
}