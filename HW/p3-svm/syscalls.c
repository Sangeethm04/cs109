#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>       /* for errno */
#include <string.h>      /* for strerror */
#include <stdio.h>       /* for fprintf, fread, fwrite, fseek, ftell, fclose */
#include <stdlib.h>      /* for exit, system */

DIR *Opendir(const char *name) {
    DIR *dirp = opendir(name);
    if(dirp == NULL) {
        fprintf(stderr, "Opendir no work: erno(%d), stderror(%s)\n", errno, strerror(errno));
        exit(errno);
    }
    return dirp;
}

struct dirent *Readdir(DIR *dirp) {
    errno = 0;
    struct dirent *direntp = readdir(dirp);
    if(direntp == NULL && errno != 0) {
        fprintf(stderr, "Readdir no work: erno(%d), stderror(%s)\n", errno, strerror(errno));
        exit(errno);
    }
    return direntp;
}

int Closedir(DIR *dirp) {
  int closedirRet = closedir(dirp);
    if(closedirRet == -1) {
        fprintf(stderr, "Closedir no work: erno(%d), stderror(%s)\n", errno, strerror(errno));
        exit(errno);
    }
    return closedirRet;
}

int Stat(const char *restrict path, struct stat *restrict buf) {
    int statRet = stat(path, buf);
    if(statRet == -1) {
        fprintf(stderr, "Stat no work: erno(%d), stderror(%s)\n", errno, strerror(errno));
        exit(errno);
    }
    return statRet;
}

//wrapper function for fopen which returns a file pointer
FILE *Fopen(const char *path, const char *mode) {
    FILE* file = fopen(path, mode);
    if(file == NULL) {
        fprintf(stderr, "Fopen no work: erno(%d), stderror(%s)\n", errno, strerror(errno));
        exit(errno);
    }
    return file;
}