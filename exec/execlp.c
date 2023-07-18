// EXECLP
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

    // stampo la variabile PATH
    // la variabile path contiene una lista di cartelle, separate da ":"
    printf("%s\n", getenv("PATH"));

    // qui uso file:"ls" e non path:"/bin/ls" perchè ls è un file dentro /bin
    // e /bin è una cartella contenuta nel PATH
    execlp("ls","ls","-a","-l",NULL);
}