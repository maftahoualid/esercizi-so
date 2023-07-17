#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv){
    off_t offset;
    ssize_t byte_letti;
    ssize_t byte_scritti;
    char c;
    int fd;

    // per ogni parametro
    for(int i=1; i<argc; i++){
        // apri il file
        fd = open(argv[i],O_RDONLY);
        if(fd==-1){
            perror("errore"); continue;
        }
        // vai a fine file
        offset = lseek(fd, -1, SEEK_END);
        do {
            // leggi un byte (offset va avanti di uno)
            byte_letti = read(fd, &c, sizeof(char));
            if(byte_letti!= sizeof(char)) {
                perror("errore");
            } else {
                // scrivi il byte su stdout
                byte_scritti = write(STDOUT_FILENO, &c, sizeof(char));
                if(byte_scritti!=sizeof(char)){ perror("errore"); }
            }
            // offset va indietro di due
            offset = lseek(fd, -2, SEEK_CUR);
        } while (offset>=0);
        printf("\n");
        close(fd);
    }
    return 0;
}