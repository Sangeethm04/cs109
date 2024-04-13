#include <stdio.h>   /* for fprintf */
#include <stdlib.h>  /* for malloc */
#include <errno.h>   /* for errno */
#include <string.h>  /* for strerror */


void *Malloc(size_t size) {
    void* allo = (void*) (malloc(size));
    if (allo == NULL) {
        fprintf(stderr, "mallo returns error sir");
        exit(errno);
    }
    return allo;
}
