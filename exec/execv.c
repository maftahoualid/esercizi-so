// EXECV
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    const char* path = "/bin/ls";
    char* const vettore[] = {"ls", "-a", "-l", NULL};
    execv(path,vettore);
    printf("errore\n");
}