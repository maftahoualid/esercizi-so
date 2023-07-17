/**
 * padre e figlio collegati da una pipe. 
 * Il figlio esegue exec("ls") 
 * e il padre scrive il risultato su un file
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define SIZE 1

int main(){
    char buf[SIZE]; // buffer di lettura e scrittura
    ssize_t byte_letti; // caratteri letti
    int pipefd[2]; // fd della pipe
    int pid; // pid di padre e figlio
    int ret;
    int file_d; // fd del file di testo

    ret = pipe(pipefd);
    if( ret == -1){ perror("pipe"); };

    pid = fork();
    if(pid == -1){
        perror("fork");
    }

    if (pid == 0) {
        // [ 0, 1, 2, fd[0], fd[1] ]
        ret = close(pipefd[0]);
        if(ret == -1){
            perror("close");
        };
        // [ 0, 1, 2, -, fd[1] ]
        ret = dup2(pipefd[1], STDOUT_FILENO);
        if(ret == -1){
            perror("dup2");
        };
        // [ 0, fd[1], 2, -, fd[1] ]
        ret = close(pipefd[1]);
        if(ret == -1){
            perror("close");
        };
        // [ 0, fd[1], 2, -, - ]
        ret = execl("/bin/ls", "ls", 0);
        if(ret == -1) {
            perror("execl");
        };
    }

    else {
        // [ 0, 1, 2, fd[0], fd[1] ]
        ret = close(pipefd[1]);
        if(ret == -1){
            perror("close");
        };
        // [ 0, 1, 2, fd[0], - ]
        file_d = open("./file.txt", O_CREAT | O_WRONLY | 0777 );
        if(file_d == -1){
            perror("open");
        };
        // [ 0, 1, 2, fd[0], file_d ]
        do {
            byte_letti = read(pipefd[0], buf, SIZE);
            if(byte_letti == -1){
                perror("read");
            };
            write(file_d, buf, byte_letti);
            if(ret == -1){
                perror("write");
            };
        } while( byte_letti != 0 );
    }
    return 0;
}