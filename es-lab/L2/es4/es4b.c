#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <wait.h>
#include <time.h>

#define MAX 100

int main(int argc,char** argv){

    srand(time(NULL));

    int n = rand()%MAX; // (int)(( (double)rand()/RAND_MAX) * MAX)
    int m = rand()%MAX;// (int)(( (double)rand()/RAND_MAX) * MAX)

    char n_str[100];
    char m_str[100];

    sprintf(n_str,"%d",n);
    sprintf(m_str,"%d",m);

    execl("es4a", "es4a", n_str, m_str, NULL);
    perror("execl");
    return 1;
}