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
    //creare pipe
    char buf[MAX];
    ssize_t nBys;
    //char mandato;
    //fd[0] legge
    //fd[1] scrive

    if(pipe(fd) == -1){
        printf("creazione pipe fallita\n");
    }
    //creare figlio
    pid_t figliolo = fork();
    if(figliolo == -1){
        printf("figlio non esiste\n");
    }else if(figliolo == 0){
        //chiudo la parte di lettura
        if(close(fd[0]) == -1){
            printf("chiusura lettura fallita\n");
        }
        //manda su pipe -> scrive
        if(dup2(fd[1], STDOUT_FILENO) == -1){
            printf("collegamento falito\n");
        }
        //figlio fa exec ls
        execlp("ls", "ls", NULL);
        if(close(fd[1]) == -1){
            printf("scrittura fallita\n");
        }
        exit(0);
        
    }
    
    int file = open("vaffanculodragodimerda.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
    //padre riceve da pipe -> nb si blocca qua
    if(close(fd[1]) == -1){
        printf("scrittura fallita\n");
    }
    nBys = read(fd[0], buf, sizeof(buf));
    buf[nBys] = '\0';
    printf("%s", buf);
    write(file, buf, sizeof(buf));
    
    close(fd);
    return 0;
}