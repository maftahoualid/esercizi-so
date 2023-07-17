#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#define SIZE 1

int main(){
    ssize_t byte_letti;
    char buf[SIZE];
    char *path= "./myfifo";
    // STDIN STDOUT STDERR
    // mkfifo(path, 0);
    int fd = open(path, O_RDONLY);
    if(fd == -1) { printf("ERRORE OPEN"); }
    // STDIN STDOUT STDERR FD
    int file_d = open("./file.txt", O_CREAT | O_WRONLY );
    do {
        byte_letti = read(fd, buf, 1);
        if(file_d == -1) { printf("ERRORE OPEN"); }
        write(file_d, buf, 1);
    } while (byte_letti>0);
    return 0;
}