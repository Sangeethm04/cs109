#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <string.h>


//new
#include <string>
#include <iostream>


#ifndef SYSCALLS_H
#define SYSCALLS_H

FILE * Fopen(const char * path, const char * mode);
size_t Fread(void *ptr, size_t item_size, size_t num_items, FILE *fp);
size_t Fwrite(const void *ptr, size_t item_size, size_t num_items, FILE *fp);
int Fseek(FILE *fp, long offset, int whence);
long Ftell(FILE *fp);
int Fclose(FILE *fp);
DIR * Opendir(const char * name);
struct dirent * Readdir(DIR * dirp);
int Closedir(DIR * dirp);
void *Malloc(size_t size);
int System(const char *command);
int Pipe(int * fd);
int Nanosleep(const struct timespec *rqtp, struct timespec *rmtp);
pid_t Fork(void);
ssize_t Read(int fd, void *buf, size_t count);
ssize_t Write(int fd, const void *buf, size_t count);
int Close(int fd);
int Socketpair(int domain, int type, int protocol, int socket_vector[2]);
pid_t Wait(int *stat_loc);

#endif

