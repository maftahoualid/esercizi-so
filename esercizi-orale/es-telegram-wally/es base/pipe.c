#include <stdio.h>
#include <unistd.h>

int main(){
        // messaggio
    char buf[20] = "Esercizio Pipe\n";

        // creo una pipe
    int fd[2];
    if(pipe(fd) == -1){
        perror("pipe");
    };

    // fork
    int pid = fork();
    if(pid == -1 ){
        perror("fork");
    }

    if (pid == 0) { // figlio
            // chiudo la lettura, scrittura aperta
        if (close(fd[0])){
            perror("close");
        };
            // scrivo su pipe un buffer
        write(fd[1],buf,sizeof(buf));
            // chiudo la scrittura
        if (close(fd[1])==-1){
            perror("close");
        };
    } else { // padre
            // lettura aperta, chiudo la scrittura
        if (close(fd[1])){
            perror("close");
        };
        ssize_t byte_letti;
        do {
                // leggo da pipe 1 byte alla volta
            byte_letti = read(fd[0], buf, 1);
                // scrivo su stdout 1 byte alla volta
            write(STDOUT_FILENO, buf, byte_letti);
                // finchè ho byte da leggere
        } while( byte_letti > 0 );
            // chiudo la lettura
        if (close(fd[0])){
            perror("close");
        };
    }
    return 0;
}