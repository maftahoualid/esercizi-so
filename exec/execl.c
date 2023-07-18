// EXECL
#include <unistd.h>

int main(){
    /* versione 1 estesa

    const char* path = "/bin/ls";
    const char* arg0 = "ls";
    const char* arg1 = "-a";
    const char* arg2 = "-l";

    execl(path,arg0,arg1,NULL);
     */

    // versione 2 compatta
    execl("/bin/ls","ls", "-a","-l",NULL);
    printf("errore\n");
}