#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <wait.h>
#include <time.h>

int main(int argc,char** argv){
    if(argc!=3){ printf("Usage: %s n m\n",argv[0]); return 0; }

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    printf("Il prodotto di %d e %d è : %d\n",n,m,(n*m) );

    return 0;
}