#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include "cIncludesFuncs.h"
#include "cIncludesGlobals.h"


// call with argv[1] == "dork.h"; this should fail (rc=2)
// call with argv[1] == "/home/merle/yopapa"; this should fail (rc=2)
// call with argv[1] == "."; opendir works, but readdir should fail if user did not set errno=0 & check for !errno;
//                      if readdir was implemented correctly, closedir will fail (rc=22)

int main(int argc, char *argv[]) {
    //text file
    //getLine() - to read each line of file into buffer
    //then sscanf - to find #includes in the .h file
    //total = 0;
    FILE* cFile = NULL;
    DIR* dir = NULL;
    char cwd[1024];

IncludeFile includeFiles[5000]; // Array to store include files
 int total;
 int sum;

    //int total = 0;
    //check if its a file or directory using Stat if file just open it and call addFile else open the directory inside recursively 
    //and call addFile on each file
     
    parseArgsAndOpenFiles(argc, argv, &cFile, &dir, &total, &sum, includeFiles);
    addFile(cFile, &total, &sum, includeFiles);
    //printMode_t printMode = promptUserForSorting();
    //print all strings in the includeFiles array
    //printIncludeFiles(printMode);
    // for(int i  = 0; i < sum; i++) {
    //     printf("%s\n", includeFiles[i].filename);
    // }
    //addFile(cFile, &total); 
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
    } else {
       perror("getcwd() error");
       return 1;
    }
    //printf("%s/%s:%d\n", cwd, argv[2], sum);

    return 0;
}