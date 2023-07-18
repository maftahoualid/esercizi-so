// EXECLP
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    char* const vettore[] = {"ls", "-a", "-l", NULL};
    char* const _envp[] = {
            // "nome=valore"
            "HOME=/home/wally/",
            "USER=wally",
            NULL,
    };

    execve("/bin/ls",vettore,_envp);
    perror("");
}