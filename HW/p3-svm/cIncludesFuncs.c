#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "syscalls.h"

#include "cIncludesGlobals.h"

#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

// 1) parsing the arguments and set one or more flags depicting the desired operation
// 2) determine if reading a header file or a directory
// 3) if a directory, open and read a directory's contents
// 4) scan a file
// 5) sort
// 6) print


//text file
//getLine() - to read each line of file into buffer
//then sscanf - to find #includes in the .h file
void addFile(FILE * cFile, int * total, int *sum);

//void addIncludeFile(const char * filename);

void parseArgsAndOpenFiles(int argc, char ** argv, FILE ** cFile, DIR ** dir, int * total, int *sum) {
    //printMode_t printMode = ASIS;
    if (argc > 1 && argv[1][0] == '-' && argv[1][1] != 'd'  && argv[1][1] != 'n' ) {
        fprintf(stderr, "sIncorrect number ofs args!: %s <filename>\n", argv[0]);
        exit(1);
    }

    //take the sorting mode from the args[1] or if there is only two args then
    //check if its a file or directory using Stat if file just open it and call addFile else open directory recursively 
    //and call addFile on each file
    struct stat buf;
    char *filePath = argv[2];  // Store argv[2] in filePath
    char cwd[1024];

    if (Stat(filePath, & buf) != -1) {
        if (S_ISREG(buf.st_mode)) {
            * cFile = Fopen(filePath, "r");
             char path[1024];
            strcpy(path, argv[2]);
            addFile( * cFile,  total, sum);

           char cwd[1024];
                if (getcwd(cwd, sizeof(cwd)) != NULL) {
                    strcat(cwd, "/");
                    strcat(cwd, path);
                } else {
                    perror("getcwd() error");
                }
                printf("%s:%d\n", cwd, *total);
                //test
        } else if(S_ISDIR(buf.st_mode)) {
            * dir = Opendir(filePath);
            struct dirent * entity;
            //open the directory inside the directory recursively and call addFile on each file
            while ((entity = Readdir( * dir)) != NULL ) {
                if (strstr(entity->d_name, ".h") != NULL) {  // Check if the file name ends with .h
                char path[1024];
                strcpy(path, argv[2]);
                strcat(path, "/");
                strcat(path, entity -> d_name);
                * cFile = Fopen(path, "r");
                addFile( * cFile,  total, sum);
                //add each file to the includeFiles array
                //addIncludeFile(path);
                
                char cwd[1024];
                if (getcwd(cwd, sizeof(cwd)) != NULL) {
                    strcat(cwd, "/");
                    strcat(cwd, path);
                } else {
                    perror("getcwd() error");
                }
                 if(path[0]=='/') {
                    printf("%s:%d\n", path, *total);
                } else {
                    printf("%s:%d\n", cwd, *total);
                }  
    
                } else if (entity -> d_type == DT_DIR) {
                    if (strcmp(entity->d_name, ".") == 0 || strcmp(entity->d_name, "..") == 0) {
                        continue;  // skip the . and .. entries
                    }
                    char path[1024];
                    strcpy(path, argv[2]);
                    strcat(path, "/");
                    strcat(path, entity -> d_name);
                    DIR * dir2 = Opendir(path);
                    struct dirent * entity2;
                    while ((entity2 = Readdir(dir2)) != NULL) {
                        if (entity2 -> d_type == DT_REG) {
                            char path2[1024];
                            strcpy(path2, path);
                            strcat(path2, "/");
                            strcat(path2, entity2 -> d_name);
                            printf("*****path=%s\n", path2);
                            * cFile = Fopen(path2, "r");
                            addFile( * cFile,  total, sum);
                            //add each file to the includeFiles array
                            //addIncludeFile(path2);
                            //print out the whole path to the file each time
                            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                            } else {
                            perror("getcwd() error");
                            }
                            printf("%s/%s:%d\n", cwd, path, *total);
                        }
                    }
                    Closedir(dir2);
                }
            }
        }
    } 
}



// int compareIncludeFiles(const void *a, const void *b) {
//     // Cast the pointers to the correct type
//     const IncludeFile *fileA = *(const IncludeFile **)a;
//     const IncludeFile *fileB = *(const IncludeFile **)b;

//     // Compare the files based on their incCount
//     return fileA->incCount - fileB->incCount;
// }

// void printData(printMode_t printMode, int numHeaders, IncludeFile ** headerFiles) {
//   switch (printMode) {
//     case ASIS:    
//       for (int i = 0; i < numHeaders; i++) fprintf(stdout, "%s:%d\n", headerFiles[i]->filename, headerFiles[i]->incCount);
//       break;
//     case STRFWD:     
//     //use qsort to sort the array of include files by the number of includes
//         qsort(headerFiles, numHeaders, sizeof(IncludeFile *), compareIncludeFiles);
//         //print array
//         for (int i = 0; i < numHeaders; i++) fprintf(stdout, "%s:%d\n", headerFiles[i]->filename, headerFiles[i]->incCount);
//       break;
//     case STRREV: 
//     //use qsort to sort the array of include files by the number of includes
//         qsort(headerFiles, numHeaders, sizeof(IncludeFile *), compareIncludeFiles);
//         //reverse the array
//         for (int i = 0; i < numHeaders / 2; i++) {
//             IncludeFile * temp = headerFiles[i];
//             headerFiles[i] = headerFiles[numHeaders - i - 1];
//             headerFiles[numHeaders - i - 1] = temp;
//         }
//         //print array
//         for (int i = 0; i < numHeaders; i++) fprintf(stdout, "%s:%d\n", headerFiles[i]->filename, headerFiles[i]->incCount);
//       break;
//     case NUMFWD:      
//     //use qsort to sort the array of include files by the number of includes in ascending order
//         qsort(headerFiles, numHeaders, sizeof(IncludeFile *), compareIncludeFiles);
//         //print array
//         for (int i = 0; i < numHeaders; i++) fprintf(stdout, "%s:%d\n", headerFiles[i]->filename, headerFiles[i]->incCount);
//       break;
//     case NUMREV:  
//       //use qsort to sort the array of include files by the number of includes in descending order
//         qsort(headerFiles, numHeaders, sizeof(IncludeFile *), compareIncludeFiles);
//         //reverse the array
//         for (int i = 0; i < numHeaders / 2; i++) {
//             IncludeFile * temp = headerFiles[i];
//             headerFiles[i] = headerFiles[numHeaders - i - 1];
//             headerFiles[numHeaders - i - 1] = temp;
//         }
//         //print array
//         for (int i = 0; i < numHeaders; i++) fprintf(stdout, "%s:%d\n", headerFiles[i]->filename, headerFiles[i]->incCount);
//       break;
//   }
// }

//Function to add an include file
// void addIncludeFile(const char * filename) {
//     strcpy(includeFiles[total].filename, filename);
// }

//text file
//getLine() - to read each line of file into buffer
//then sscanf - to find the number of #includes in the .h file in the current directory
void addFile(FILE * cFile, int * total, int *sum) {
    *total = 0;
    //use getLine
    char buffer[1024];
    while (fgets(buffer, 1024, cFile) != NULL) {
        char * pound = strstr(buffer, "#include");
        if (pound != NULL) {
            //print out the file path and the number of includes each time
            ( * total) ++;
            (*sum) ++;
            //printf("%s:%d\n", buffer, *total);
        }
    }
}