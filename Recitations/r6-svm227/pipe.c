#include "syscalls.h"    /* for wrapped calls */
#include <unistd.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <string.h>
#include <sched.h>
#include <time.h>


int main(void) {
  int pfd[2]; /* for pipe file descriptors (pfd); need 2 file descripts b/c pipe has 2 ends! */
  pid_t pid = 0; /* for PID from fork() */
  char string[] = "Mind over mattresssss!\n"; /* for testing */
  char buffer[80]; /* hold string read from pipe */
  ssize_t numBytes; /* count of bytes written or read */
  /* Insert here some variables needed by nanosleep */
  struct timespec rqtp;

  /* In this program, you will write to file descriptor pfd[1] and read from file descriptor pfd[0] */
  /* Insert here a call to your wrapped pipe() command to for communication from child to parent */
  Pipe(pfd);
  if (Fork() == 0) {
    /* call wrapped fork() command, use return value to determine if executing in child */

    /* close the unneeded "read" end of the pipe */
    Close(pfd[0]);
    /* Use fprintf to print to stdout the process ID of the child and the process ID of its parent */
    fprintf(stdout, "CHILD: My PID is %d, my parent's PID is %d\n", getpid(), getppid());
    /* Replace following 6 lines with 2 lines: a call to wrapped write() & the fprintf call to stdout */
    if ((numBytes = Write(pfd[1], string, (strlen(string) + 1))) == -1) {
      /* send string "down" the pipe */
      fprintf(stderr, "CHILD: write error (%d): %s\n", errno, strerror(errno));
      exit(errno);
    } else {
      fprintf(stdout, "CHILD: I wrote %ld bytes on file descriptor %d\n", numBytes, pfd[1]);
    }

    /* close the "write" end of the pipe */
    Close(pfd[1]);
  } else {
    /* parent code in here */

    /* close the unneeded "write" end of the pipe */
    Close(pfd[1]);
    /* Use fprintf to print to stdout the pid of the child, its own pid, and the pid of its parent */
    fprintf(stdout, "PARENT: My PID is %d, my child's PID is %d, my parent's PID is %d\n", getpid(), pid, getppid());
    /* Replace following 6 lines with 2 lines: a call to wrapped read() & the fprintf call to stdout */
    if ((numBytes = Read(pfd[0], buffer, sizeof(buffer))) == 0) {
      /* read in the string from the pipe */
      fprintf(stderr, "PARENT: read error (%d): %s\n", errno, strerror(errno));
      exit(errno);
    } else {
      fprintf(stdout, "PARENT: I read %ld bytes from file descriptor %d\n", numBytes, pfd[0]);
    }

    fprintf(stdout, "PARENT: I redceived a message: %s", buffer);

    /* close the "read" end of the pipe */
    Close(pfd[0]);
  }

  /* Here, set your variables for call to wrapped nanosleep (for 9.5 seconds) and then call it */
  rqtp.tv_sec = 9;
  rqtp.tv_nsec = 500000000;
  Nanosleep( & rqtp, NULL);


  return 0;
}

/*
 *  Q0: Describe what the pipe() function does?
 *  A0: the pipe function creates a pipe, a unidirectional data channel that can be used for interprocess communication
 *
 *  Q1: What did you observe when you executed "pstree $$" on the command line while your program was 
 *      running?
 *  A1: I got back a tree graph with the pid of the processes which are running which is useful to understand running programs. 
 *  
 *  Q2: Why are we specifying "strlen(string) + 1" in the write function call? I.e., why not just 
 *      "strlen(string)"?
 *  A2:   we need to add 1 to the length of the string to include null terminator character
 *  
 *  Q3: Using the time command, what was the real amount of time your program ran? (If your real time 
 *      is not greater than or equal to 9.5 seconds, you need to change the values you set for nanosleep.)
 *  A3: 9.502 seconds
 *  
 *  Q4: What is user time and sys time? Why do you think these do not sum up to the real time?
 *  A4: 0.001. the user and sys time are just time spent by the cpu executing the program wheres 
 *  the real time is the time it takes to run the program which is much longer
 *
 *  Q5: If a function, such as close() or pipe(), only returns 0 or -1, do you really need to store its 
 *      return value in your Stevens-style wrapper OR could you just hardcode "return 0", knowing that 
 *      a check for -1 would result in an exit from the wrapper?
 *  A5: yes you could just hardcode return 0 beacuse the if would return -1 and exit if it fails
 */