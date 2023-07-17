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
    char bufOut[MAX];
    char bufErr[MAX];
    int fif1 = mkfifo("ciccio.txt",  S_IRUSR | S_IWUSR);
    int fif2 = mkfifo("drago.txt",   S_IRUSR | S_IWUSR);
    
    int out = open("ciccio.txt", O_RDONLY);
    int err = open("drago.txt", O_RDONLY);
    
    int fdOut = open("fileout.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
    int fdErr = open("fileERR.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
    
    read(out, bufOut, sizeof(bufOut));
    read(err, bufErr, sizeof(bufErr));
    write(fdOut, bufOut, sizeof(bufOut));
    write(fdErr, bufErr, sizeof(bufErr));
}