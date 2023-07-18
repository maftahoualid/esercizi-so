#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "errExit.h"

#define BUFFER_SZ 100
char buffer[BUFFER_SZ + 1];

int main (int argc, char *argv[]) {

    // Check command line arguments
    if (argc != 3 && argc != 4) {
        printf("Usage: %s [option] <sourceFile> <destinationFile>\n", argv[0]);
        printf("option:\n");
        printf("-a: append\t<sourceFile> to <destinationFile>\n");
        printf("-s: overwrite\t<destinationFile> with <sourceFile>\n");
        return 1;
    }

    // flag variable, which is used to store either the option -a, or -s
    char *flag = NULL;
    // the pathnames to the source and destination file
    char *fileSource, *fileDestination;

    // if argc is 4, then my_cp <flag> <source> <destination>
    if (argc == 4) {
        flag = argv[1];
        fileSource = argv[2];
        fileDestination = argv[3];
    // if argc is 3, then my_cp <source> <destination>
    } else {
        fileSource = argv[1];
        fileDestination = argv[2];
    }

    // open the source file for only reading
    int fileS = open(fileSource, O_RDONLY);
    if (fileS == -1)
        errExit("open failed");

    int fileD = -1;
    //if flag is NULL, then no flag was provided as input argument
    if (flag == NULL) {
        // check if the destination file already exists
        if (access(/*...*/) == 0) {
            printf("Il file %s gia' esiste!\n", fileDestination);
            return 1;
        }
        // create and open the destination file for only writing
        // N.B. we must be sure we created the file (O_EXCL)
        fileD = open(/*...*/);
    // if flag is "-s", then we have to overwrite the destination file
    } else if (strcmp(flag, "-s") == 0) {
        // Open new or existing file for only writing. If the file
        // destination already exists, truncate it to zero bytes
        fileD = open(/*...*/);
    // if flag is "-a", then we have to append file source to the bottom of
    // file destination
    } else if (strcmp(flag, "-a") == 0) {
        // check if source and destination are different.
        if (strcmp(fileSource, fileDestination) == 0) {
            printf("<sourceFile> and <destinationFile> must be different\n");
            return 1;
        }
        // check if the destination file exists and can be written
        if (access(/*...*/) != 0) {
            printf("Il file %s non esiste, o non puo' essere scritto!\n",
                   fileDestination);
            return 1;
        }
        // open the destination file for only writing
        fileD = open(/*...*/);
        // movet the current offset to the bottom of destination file
        if (fileD != -1 && lseek(/*...*/) == -1)
            errExit("lssek failed");
    } else {
        printf("The flag %s is not recognized!\n", flag);
        return 1;
    }
    // if fileD is -1, then something went wrong with the open system call
    if (fileD == -1)
        errExit("open failed");

    ssize_t bR;
    do {
        // read a chunk of bytes from file source
        bR = //....
        // check if read completed successfully
        if (bR == -1)
            errExit("read failed");
        // check if write completed successfully
        if (bR > 0 && write(/*...*/) != /*...*/)
                errExit("write failed");
    // inter. until end-of-file is reached
    } while (bR > 0);

    // close file descriptors
    //...

    return 0;
}
