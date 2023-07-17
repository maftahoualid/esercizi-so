/*
un binario che genera un numero casuale e lo ritorna come exit code. 
Un altro programma che forka, fa exec del primo binario e poi con la wait recupera il numero ritornato
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
    //genera numero casuale
    srand(time(NULL));
    int n = rand() % 100 + 1;
    printf("%i\n", n);
    return n;
}