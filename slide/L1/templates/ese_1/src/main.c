#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "errExit.h"

#define BUFFER_SZ 100
char buffer[BUFFER_SZ + 1];

int main (int argc, char *argv[]) {

    // For each file provided as input argument
    for (int i = 1; i < argc; ++i) {
        // open the file in read only mode
        int file = //....
        // check error of open system call
        if (/*...*/) {
            printf("File %s does not exist\n", argv[i]);
            continue;
        }

        ssize_t bR = 0;
        do {
            // read the file in chunks of BUFFER_SZ
            bR = // ...
            // check error of read system call
            if (/*...*/) {
                // add the character '\0' to let printf know where a
                // string ends
                buffer[bR] = '\0';
                printf("%s", buffer);
            }
        // inter. until we read something from file
        } while (/*...*/);

        // close the file descriptor
        //.....
    }

    return 0;
}
