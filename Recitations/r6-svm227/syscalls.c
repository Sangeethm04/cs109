#include <sys/types.h>

#include <sys/stat.h>

#include <dirent.h>

#include <unistd.h>

#include <errno.h>       /* for errno */

#include <string.h>      /* for strerror */

#include <stdio.h>       /* for fprintf, fread, fwrite, fseek, ftell, fclose */

#include <stdlib.h>      /* for exit, system */
#include <time.h>

//wrapper function for fopen which returns a file pointer
FILE * Fopen(const char * path, const char * mode) {
    FILE * file = fopen(path, mode);
    if (file == NULL) {
        fprintf(stderr, "Fopen no work: erno(%d), stderror(%s)\n", errno, strerror(errno));
        exit(errno);
    }
    return file;
}

size_t Fread(void *ptr, size_t item_size, size_t num_items, FILE *fp) {
    size_t items = fread(ptr, item_size, num_items, fp);
    if(items != num_items) {
        fprintf(stderr, "Fread no work: erno(%d), stderror(%s)\n", errno, strerror(errno));
        exit(errno);
    }
    return items;
}

size_t Fwrite(const void *ptr, size_t item_size, size_t num_items, FILE *fp) {
    size_t items = fwrite(ptr, item_size, num_items, fp);
    if(items != num_items) {
        fprintf(stderr, "Fwrite no work: erno(%d), stderror(%s)\n", errno, strerror(errno));
        exit(errno);
    }
    return items;
}

int Fseek(FILE *fp, long offset, int whence) {
    int offsets = fseek(fp, offset, whence);
    if(offsets == -1) {
        fprintf(stderr, "Fseek no work: erno(%d), stderror(%s)\n", errno, strerror(errno));
        exit(errno);
    }
    return offsets;
}

long Ftell(FILE *fp) {
    long offset = ftell(fp);
    if(offset == -1) {
        fprintf(stderr, "ftell no work: erno(%d), stderror(%s)\n", errno, strerror(errno));
        exit(errno);
    }
    return offset;
}


int Fclose(FILE *fp) {
    int fileClose = fclose(fp);
    if(fileClose != 0) {
        fprintf(stderr, "Fclose no work: erno(%d), stderror(%s)\n", errno, strerror(errno));
        exit(errno);
    }
    return fileClose;
}





DIR * Opendir(const char * name) {
    DIR * dirp = opendir(name);
    if (dirp == NULL) {
        fprintf(stderr, "Opendir no work: erno(%d), stderror(%s)\n", errno, strerror(errno));
        exit(errno);
    }
    return dirp;
}

struct dirent * Readdir(DIR * dirp) {
    errno = 0;
    struct dirent * direntp = readdir(dirp);
    if (direntp == NULL && errno != 0) {
        fprintf(stderr, "Readdir no work: erno(%d), stderror(%s)\n", errno, strerror(errno));
        exit(errno);
    }
    return direntp;
}

int Closedir(DIR * dirp) {
    int closedirRet = closedir(dirp);
    if (closedirRet == -1) {
        fprintf(stderr, "Closedir no work: erno(%d), stderror(%s)\n", errno, strerror(errno));
        exit(errno);
    }
    return closedirRet;
}


void *Malloc(size_t size) {
    void* allo = (void*) (malloc(size));
    if (allo == NULL) {
        fprintf(stderr, "mallo returns error sir");
        exit(errno);
    }
    return allo;
}


int System(const char *command) {
    int status = system(command);
    if(status == -1) {
        fprintf(stderr, "System no work: erno(%d), stderror(%s)\n", errno, strerror(errno));
        exit(errno);
    }
    return status;
}

int Pipe(int * fd) {
    int id = pipe(fd);
    if (id == -1) {
        fprintf(stderr, "Stat no work: erno(%d), stderror(%s)\n", errno, strerror(errno));
        exit(errno);
    }
    return id;

}

int Nanosleep(const struct timespec *rqtp, struct timespec *rmtp) {
    int status = nanosleep(rqtp, rmtp);
    if(status == -1) {
        fprintf(stderr, "Nanosleep no work: erno(%d), stderror(%s)\n", errno, strerror(errno));
        exit(errno);
    }
    return status;
 }

 pid_t Fork() {
    pid_t pid = fork();
    if (pid == -1) {
        fprintf(stderr, "Fork no work: erno(%d), stderror(%s)\n", errno, strerror(errno));
        exit(errno);
    }
    return pid;
}

//wrap close
int Close(int fd) {
    int status = close(fd);
    if(status == -1) {
        fprintf(stderr, "Close no work: erno(%d), stderror(%s)\n", errno, strerror(errno));
        exit(errno);
    }
    return status;
}

//wrap read
ssize_t Read(int fd, void *buf, size_t count) {
    ssize_t status = read(fd, buf, count);
    if(status == -1) {
        fprintf(stderr, "Read no work: erno(%d), stderror(%s)\n", errno, strerror(errno));
        exit(errno);
    }
    return status;
}

//wrap write
ssize_t Write(int fd, const void *buf, size_t count) {
    ssize_t status = write(fd, buf, count);
    if(status == -1) {
        fprintf(stderr, "Write no work: erno(%d), stderror(%s)\n", errno, strerror(errno));
        exit(errno);
    }
    return status;
}
