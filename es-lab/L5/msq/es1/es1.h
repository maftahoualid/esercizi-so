#ifndef ES_LAB_ES1_H
#define ES_LAB_ES1_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <wait.h>
#include <time.h>
#include <sys/msg.h>

typedef struct {
    long mtype;
    unsigned int code;
    char description[100];
    unsigned int quantity;
    char email[100];
} msg;

#endif //ES_LAB_ES1_H
