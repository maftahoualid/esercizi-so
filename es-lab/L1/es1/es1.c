#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SZ 10
char buffer[BUFFER_SZ + 1];

int main(int argc, char** argv){
    // per ogni parametro
    for(int i=1; i<argc; i++ ){
        // apri il file
        int fd = open(argv[i],O_RDONLY);
        if(fd==-1){ perror("errore"); continue; }

        ssize_t br;
        do {
            // leggi "BUFFER_SZ" byte e salvali in "buffer"
            br = read(fd, buffer, BUFFER_SZ);
            // se non ci sono caratteri da leggere
            if(br>0) {
                // aggiungi il terminatore dopo i byte letti
                buffer[br] = '\0';
                // stampa il buffer
                printf("%s", buffer);
            }
        // finchè ci sono byte da leggere
        } while(br>0);
        printf("\n");


        close(fd);
    }
    return 0;
}