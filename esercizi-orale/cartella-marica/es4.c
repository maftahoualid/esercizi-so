/*
ESERCIZI
principalmente sulle pipe/fifo e sulla fork/exec/wait 
visto che non erano richieste nell'elaborato. Di seguito alcuni dei possibili esercizi. 


stesso esercizio ma con una fifo e facendo due binari separati. 
Quello che esegue ls e quello che legge e scrive su file

un binario che genera un numero casuale e lo ritorna come exit code. 
Un altro programma che forka, fa exec del primo binario e poi con la wait recupera il numero ritornato

"modifica" al progetto scrivendo un programma che si collega alla memoria 
condivisa e fa da "spettatore" leggendo la memoria condivisa e stampando la griglia. la chiave della shm si
può passare da riga di comando

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
    int fif = mkfifo("dragogay.txt", S_IRUSR | S_IWUSR);
    int fd = open("dragogay.txt", O_RDONLY);
    char buf[MAX];
    int file = open("cicciogamer.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
    read(fd, buf, sizeof(buf));
    write(file, buf, sizeof(buf));
    printf("%s", buf);
    printf("\n");
    close(file);
    close(fd);
}