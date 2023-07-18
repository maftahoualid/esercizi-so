#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define BUFFER_SZ 128

int main(){

    char* username = getenv("USER");
    if(!username){ username = "unknown"; }

    char* homedir = getenv("HOME");
    if(!homedir){ perror("getenv home"); }

    char buffer[BUFFER_SZ];
    if(!getcwd(buffer, sizeof(buffer))){ perror("getcwd"); }

    int is_subdir = strncmp(buffer, homedir, strlen(homedir));
    //int is_subdir = ( strstr(buffer, homedir) == buffer )?1:0;

    if(!is_subdir){
        printf("%s, la \"cwd\" è sottodirectory di \"home\".\n",username);
        printf("buffer : %s\n",buffer);
        printf("home : %s\n",homedir);
    } else {
        if(chdir(homedir)) { perror("chdir"); }
        int fd = open("file.txt",O_CREAT | O_TRUNC | O_RDWR , S_IRUSR | S_IWUSR );
        if(!fd) { perror("open"); }
        if(!close(fd)) { perror("close"); }
        printf("%s, ora sono nella \"home\"\n",username);
    }

    return 0;
}