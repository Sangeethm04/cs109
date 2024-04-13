#include <stdio.h>       /* for fprintf */
#include <stdlib.h>      /* for exit */
#include <errno.h>       /* for errno */
#include <string.h>      /* for strerror */
#include <unistd.h>


void Read(int fildes, void * buffer, size_t nbytes) {
    nbytes = read(fildes, buffer, nbytes);
    size_t num = -1;
    if (nbytes == num) {
        fprintf(stderr, "nothing was read filedis(%d),erno-%d stderror-%s ", fildes, errno, strerror(errno));
        exit(errno);
    }
}

void Write(int fildes, const void * buffer, size_t nbytes) {
    nbytes = write(fildes, buffer, nbytes);
    size_t nums = -1;
    if (nbytes == nums) {
        fprintf(stderr, "error file dis(%d), erno-%d stderror-%s", fildes, errno, strerror(errno));
        exit(errno);
    }
}