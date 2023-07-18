// EXECLE
#include <stdio.h>
#include <unistd.h>

extern char** environ;

int main(int argc, char *argv[], char* envp[]) {

    int i = 0;
    do {
        // stampa le variabili di ambiente del processo corrente

        // modo 1:
        printf("%s\n", envp[i]);
        // modo 2:
        // printf("%s\n", environ[i]);
        i++;
    // modo 1:
    } while (envp[i] != NULL);
    // modo 2:
    /*} while (environ[i] != NULL);*/

    const char* _envp[] = {
            // "nome=valore"
            "HOME=/home/",
            "USER=wally",
            NULL,
    };

    execle("/bin/ls","ls","-a","-l",NULL,_envp);
    printf("errore\n");
}