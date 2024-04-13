#ifndef SYSCALLS_H
#define SYSCALLS_H
 
ssize_t Read(int fildes, void *buffer, size_t nbytes);
ssize_t Write(int fildes, const void *buffer, size_t nbytes);

#endif
