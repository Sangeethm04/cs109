#include <dirent.h>
#include <sys/stat.h>


#ifndef SYSCALLS_H
#define SYSCALLS_H

DIR *Opendir(const char *name);
struct dirent *Readdir(DIR *dirp);
int Closedir(DIR *dirp);
int Stat(const char *restrict path, struct stat *restrict buf);
FILE *Fopen(const char *path, const char *mode);



#endif

