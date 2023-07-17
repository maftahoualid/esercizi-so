/*
padre figlio con il figlio che fa "ls -alr /" e il padre scrive lo
stdout sul file e lo stderr su un altro file
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX 9000

int fd1[2];
int fd2[2];

int main(int argc, char * argv){
    pipe(fd1); //creazione pipe
    pipe(fd2);
    char buf1[MAX];
    char buf2[MAX];
    ssize_t bys1;
    ssize_t bys2;

    int figliolo = fork();
    if(figliolo == 0){
        close(fd1[0]);
        close(fd2[0]);
        dup2(fd1[1], 1); //out
        dup2(fd2[1], 2); //err
        execlp("ls", "ls", "-alr", "/", NULL);
        exit(0);
    }
    int fileout = open("fileOut.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
    int fileErr = open("fileErr.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
    
    wait(NULL);
    close(fd1[1]);
    close(fd2[1]);
    read(fd1[0], buf1, sizeof(buf1));
    read(fd2[0], buf2, sizeof(buf2));
    printf("%s\n", buf1);
    printf("%s\n", buf2);
    write(fileout, buf1, sizeof(buf1));
    write(fileErr, buf2, sizeof(buf2));
}