#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include "syscalls.h"

// call with argv[1] == "dork.h"; this should fail (rc=2)
// call with argv[1] == "/home/merle/yopapa"; this should fail (rc=2)
// call with argv[1] == "."; opendir works, but readdir should fail if user did not set errno=0 & check for !errno;
//                      if readdir was implemented correctly, closedir will fail (rc=22)

int main(int argc, char** argv) {
  (void)argc;
  fprintf(stderr, "argv[1] = %s\n", argv[1]);

  if (strcmp(argv[1], "dork.h") == 0) {
    struct stat* statbuf = malloc(sizeof(struct stat));
    if (statbuf) {
      Stat(argv[1], statbuf);
      free(statbuf);
    }
    return 0;
  }
  DIR* dirPtr = NULL;
  dirPtr = Opendir(argv[1]);
  errno = 99;
  while (Readdir(dirPtr)); // this will error out if wrapped function does not zero out errno
  errno = 0;
  dirPtr = NULL;
  Closedir(dirPtr);

  return 0;
}
