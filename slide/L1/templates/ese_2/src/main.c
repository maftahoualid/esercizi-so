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
        int file = // ....
        // check error of open system call
        if (/* ... */) {
            printf("File %s does not exist\n", argv[i]);
            continue;
        }
        // move the offset location to the end of the file
        off_t currentOffset = lseek(/*...*/);
        char c;
        while (currentOffset >= 0) {
            // read a char from the file
            ssize_t bR = //
            // write the read char on standard output
            if (bR == sizeof(char)) {
                // write on standard output the char
                if (write(/*...*/)
                    errExit("write failed");
            }
            // move backwards the fie offset
            currentOffset = lseek(/*...*/);
        }
        // close the file descriptor
        //....

        // print a new line before starting the next file
        c = '\n';
        write(/*....*/);
    }

    return 0;
}
