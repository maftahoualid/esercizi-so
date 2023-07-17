/*
un binario che genera un numero casuale e lo ritorna come exit code.
Un altro programma che forka,fa exec del primo binario
e poi con la wait recupera il numero ritornato
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(){
    srand(time(0));
    int random = rand()%100;
    printf("Numero random : %d\n", random);
    printf("Pid : %d\n", getpid() );
    return random;
}

