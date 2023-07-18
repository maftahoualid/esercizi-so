#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <wait.h>
#include <time.h>
#include <sys/sem.h>

union semun {
    int val;
    struct semid_ds* buf;
    unsigned short* array;
};

void semOp( int semid, unsigned short sem_num, short sem_op ){
    struct sembuf sop = {.sem_num=sem_num, .sem_op=sem_op, .sem_flg=0};
    if(semop(semid,&sop,1)==-1){ perror("semop"); exit(EXIT_FAILURE); }
};

char* messages[] = { "Operativi\n", "Sistemi ", " di ", "Corso" };

int main(int argc, char** argv){

    if(argc!=2){ printf("usage: %s <num>\n",argv[0]); exit(EXIT_FAILURE); }

    int n = atoi(argv[1]);
    if(n<0){ printf("n>0 !!\n"); exit(EXIT_FAILURE); }

    int semid = semget(IPC_PRIVATE, 4, S_IRUSR | S_IWUSR );
    if(!semid) { perror("semid"); exit(EXIT_FAILURE); }

    unsigned short sem_init_val[] = {0,0,0,1};
    union semun arg;
    arg.array = sem_init_val;

    if(semctl(semid,0,SETALL,arg)==-1){ perror("semctl setall"); exit(EXIT_FAILURE); }

    for(int i=0; i<4; i++){
        pid_t pid = fork();
        if(pid == 0){
            for(int j=0; j<n; j++){
                semOp(semid,(unsigned short)i,-1);
                printf("%s", messages[i]); fflush(stdout);
                semOp(semid, (unsigned short)(i==0)?3:i-1, 1);
            }
            exit(0);
        }
    }

    while(!wait(NULL)){
        if(!semctl(semid,0,IPC_RMID,NULL)){ perror("semctl ipc_rmid"); exit(EXIT_FAILURE); }
    }

    return 0;
}

