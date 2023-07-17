/*
un binario che genera un numero casuale e lo ritorna come exit code.
Un altro programma che forka,fa exec del primo binario
e poi con la wait recupera il numero ritornato
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

    pid_t pid = fork();
    if(pid == -1 ){
        perror("fork");
    } else if(pid == 0){ // figlio
        execl("./exit_code", "exit_code", NULL);
    } else { // padre
        int status;
        wait( &status );
        printf("Numero ritornato %d\n", WEXITSTATUS(status));
    }

    return 0;
}