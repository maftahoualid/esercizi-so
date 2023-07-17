#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

./
/

int main(){
    char *path = "./myfifo";
    int ret = mkfifo(path, 0777);
    if( ret == -1) { printf("ERRORE MKFIFO"); }
    // STDIN STDOUT STDERR
    int fd = open(path, O_WRONLY);
    if(fd == -1) { printf("ERRORE OPEN"); }
    // STDIN STDOUT STDERR FD
    close(1);
    // STDIN -- STDERR FD
    dup(fd);
    // STDIN FD STDERR FD
    if(execl("/bin/ls", "ls", 0)==-1){
        perror("execl");
    };
    return 0;
}