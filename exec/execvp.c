// EXECVP
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    char* const vettore[] = {"ls", "-a", "-l", NULL};
    // ls e non /bin/ls perchè /bin è nel PATH
    execvp("ls",vettore);
}