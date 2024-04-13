#ifndef SYSCALLS_H
#define SYSCALLS_H

/* YOU SHOULD NOT NEED TO EDIT THIS FILE, BUT YOU CAN IF YOU WANT */

/* You must submit wrapped functions for all these prototypes */
ssize_t Read(int fd, void *buf, size_t nbyte);
ssize_t Write(int fd, const void *buf, size_t nbyte);
FILE *Fopen(const char *path, const char *mode);
int Fclose(FILE *fp);  /* ok to have this not return anything */
int Fseek(FILE *fp, long offset, int whence);
long Ftell(FILE *fp);
size_t Fread(void *ptr, size_t item_size, size_t num_items, FILE *fp);
size_t Fwrite(const void *ptr, size_t item_size, size_t num_items, FILE *fp); 
int System(const char *command);

#endif
