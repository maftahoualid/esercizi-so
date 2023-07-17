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

int main(int argc, char * argv){
    int out = open("ciccio.txt", O_WRONLY);
    int err = open("drago.txt", O_WRONLY);

    dup2(out, 1);
    dup2(err, 3);

    execlp("ls", "ls", "-alr", "/", NULL);

    return 0;
}