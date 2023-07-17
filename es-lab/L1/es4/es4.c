#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv) {

    if (argc == 3) {

        char* source = argv[1];
        char* destination = argv[2];

        if(access(source,F_OK)==0){ perror("1"); }

        int fd1 = open(source, O_RDONLY);
        if(fd1==-1){ perror("2"); }

        int fd2 = open(destination, O_CREAT | O_EXCL | O_RDONLY, 0666 );
        if(fd2==-1){ perror("3"); }

        char buffer[100+1];
        ssize_t br,bw;

        br = read(fd1,&buffer, 100);
        if(br==-1){ perror("4"); }

        else if(br>0){
            bw = write(fd2,&buffer,100);
            if(bw==-1){ perror("6"); }
        }
    }
    else if (argc == 4) {
        if (strcmp(argv[1], "-s") == 0) { printf("-s"); }
        else if (strcmp(argv[1], "-a") == 0){ printf("-a"); }
    }



}