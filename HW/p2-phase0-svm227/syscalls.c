#include <stdio.h>       /* for fprintf, fread, fwrite, fseek, ftell, fclose */
#include <stdlib.h>      /* for exit, system */
#include <unistd.h>      /* for read, write */
#include <errno.h>       /* for errno */
#include <string.h>      /* for strerror */

//wrapper function for read which returns the number of bytes read
ssize_t Read(int fd, void *buf, size_t nbyte) {
    ssize_t bytesRead = read(fd, buf, nbyte);
    if(bytesRead == -1) {
        fprintf(stderr, "Read no work filedis(%d),erno(%d), stderror(%s)\n", fd, errno, strerror(errno));
        exit(errno);
    }
    return bytesRead;
}

//wrapper function for write which returns the number of bytes written
ssize_t Write(int fd, const void * buffer, size_t nbyte) {
    ssize_t bytesWritten = write(fd, buffer, nbyte);
    if(bytesWritten == -1) {
        fprintf(stderr, "Write no work filedis(%d), errno(%d), stderror(%s)", fd, errno, strerror(errno));
        exit(errno);
    }
    return bytesWritten;
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

//wrapper function for fclose which returns 0 on success
int Fclose(FILE *fp) {
    int fileClose = fclose(fp);
    if(fileClose != 0) {
        fprintf(stderr, "Fclose no work: erno(%d), stderror(%s)\n", errno, strerror(errno));
        exit(errno);
    }
    return fileClose;
}

//wrapper function for fseek which returns 0 on success
int Fseek(FILE *fp, long offset, int whence) {
    int offsets = fseek(fp, offset, whence);
    if(offsets == -1) {
        fprintf(stderr, "Fseek no work: erno(%d), stderror(%s)\n", errno, strerror(errno));
        exit(errno);
    }
    return offsets;
}

//wrapper function for ftell which returns the current offset in the file
long Ftell(FILE *fp) {
    long offset = ftell(fp);
    if(offset == -1) {
        fprintf(stderr, "Fseek no work: erno(%d), stderror(%s)\n", errno, strerror(errno));
        exit(errno);
    }
    return offset;
}

//wrapper function for fread which returns the number of items read
size_t Fread(void *ptr, size_t item_size, size_t num_items, FILE *fp) {
    size_t items = fread(ptr, item_size, num_items, fp);
    if(items != num_items) {
        fprintf(stderr, "Fread no work: erno(%d), stderror(%s)\n", errno, strerror(errno));
        exit(errno);
    }
    return items;
}

//wrapper function for fwrite which returns the number of items written
size_t Fwrite(const void *ptr, size_t item_size, size_t num_items, FILE *fp) {
    size_t items = fwrite(ptr, item_size, num_items, fp);
    if(items != num_items) {
        fprintf(stderr, "Fwrite no work: erno(%d), stderror(%s)\n", errno, strerror(errno));
        exit(errno);
    }
    return items;
}

//wrapper function for system which returns the status of the command
int System(const char *command) {
    int status = system(command);
    if(status == -1) {
        fprintf(stderr, "System no work: erno(%d), stderror(%s)\n", errno, strerror(errno));
        exit(errno);
    }
    return status;
}









