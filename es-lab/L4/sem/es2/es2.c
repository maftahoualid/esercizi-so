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

void printSemaphoreValues(int semid){
    unsigned short semValues[4];
    union semun arg;
    arg.array = semValues;

    if(semctl(semid,0,GETALL,arg)==-1){ perror("semctl getall"); exit(EXIT_FAILURE);}
    printf("semaphore set :\n");
    for(int i=0; i<4; i++){ printf("[%d] ",semValues[i]); }
    printf("\n");
}

void semOp( int semid, unsigned short sem_num, short sem_op ){
    struct sembuf sop = {.sem_num=sem_num, .sem_op=sem_op, .sem_flg=0};
    if(semop(semid,&sop,1)==-1){ perror("semop"); exit(EXIT_FAILURE); }
};

int main(int argc, char** argv){

    char *messages[] = { "C","B","A" };

    int semid = semget(IPC_PRIVATE, 4, S_IRUSR | S_IWUSR);
    if(semid==-1){ perror("semget"); exit(EXIT_FAILURE); }

    unsigned short semValues[] = {0,0,1,3};
    union semun arg;
    arg.array = semValues;
    if(semctl(semid,0,SETALL, arg)==-1){ perror("semctl setall"); exit(EXIT_FAILURE); }

    printSemaphoreValues(semid);

    for(int i=0;i<3;i++){
        pid_t pid = fork();
        if(pid==-1){ perror("fork"); exit(EXIT_FAILURE); }
        else if(pid==0) {
            // sem[i]--
            semOp(semid, (unsigned short) i, -1);
            // messages[i]
            printf("%s\n", messages[i]);
            fflush(stdout);
            // sem[3]--
            semOp(semid, 3, -1);
            // sem[i-1]++
            if (i > 0) { semOp(semid, (unsigned short) (i - 1), +1); }
            // wait sem[3] to be 0
            semOp(semid, 3, 0);
            printf("Done!\n");
            exit(EXIT_SUCCESS);
        }
    }

    while(wait(NULL)!=-1);
    printSemaphoreValues(semid);
    if(semctl(semid,0,IPC_RMID)==-1){ perror("semctl ipcrmid"); exit(EXIT_FAILURE); }

    return 0;
}