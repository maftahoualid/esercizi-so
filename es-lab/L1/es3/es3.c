#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv){

    int ret;
    char c;

    char* fileSource = argv[1];
    char* fileDestination = argv[2];
    char* charSearch = argv[3];
    char* charReplace = argv[4];

    int fileS = open(fileSource, O_RDONLY);
    if(fileS==-1){ perror(""); }

    if(access(fileDestination,F_OK)==0){ printf("Il file esiste già\n"); return 1; }

    int fileD = open(fileDestination, O_CREAT | O_EXCL | O_WRONLY, S_IRUSR | S_IWUSR);
    if(fileD==-1){ perror(""); }

    ssize_t br,bw;
    do {
        br = read(fileS, &c, sizeof(char));
        if(br==-1){ perror(""); }
        printf("%c", c);
        if(c==*charSearch){ c = *charReplace; }
        if(br>0) {
            bw = write(fileD, &c, sizeof(char));
            if( bw != sizeof(char) ){ perror(""); }
        }
    } while(br > 0);

    ret = close(fileS);
    if(ret==-1){ perror(""); }
    ret = close(fileD);
    if(ret==-1){ perror(""); }

    return 0;
}