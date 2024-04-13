#include <stdio.h>       /* for fprintf */
#include <unistd.h>      /* for STDIN_FILENO and STDOUT_FILENO file descriptors */
#include <time.h>        /* for clock function and clock_t data type */
#include "syscalls.h"    /* for Read and Write */

int main() {
  int numBytesRead = 0; /* don't modify */
  char buffer[BUFFSIZE]; /* don't modify */
  double elapsedTime = 0; /* don't modify */

  /* declare a clock_t variable to hold the beginning clock cycle count time;
   * set the variable by calling the clock function (no arguments)
   */
  clock_t start = clock();
  /* create a loop that reads stdin BUFFSIZE bytes at a time using your wrapped 
   * read() function; after each read, write to stdout the number of bytes read;
   * this loop is what we are interested in timing; we should see that as the 
   * buffer size is increased, the time to read and write decreases (to a limit)
   */

  //void Read(int fildes, void *buffer, size_t nbytes){
  //void Write(int fildes, const void *buffer, size_t nbytes)
  while ((numBytesRead = Read(STDIN_FILENO, buffer, BUFFSIZE)) > 0) {

    Write(STDOUT_FILENO, buffer, numBytesRead);
  }
  /* declare another clock_t variable and set it to the return value of a clock
   * function call; this will hold the ending clock cycle count
   */
  clock_t end = clock();
  /* now, subtract the beginning clock cycle count from the ending clock cycle 
   * count and divide by the CLOCKS_PER_SEC (this value is set in time.h); 
   * you will want to perform this operation as a double FP operation, so you 
   * will need to cast to double
   */
   elapsedTime = (double)(end - start);
  elapsedTime = elapsedTime/CLOCKS_PER_SEC;
  
  fprintf(stderr, "%6d - %f\n", BUFFSIZE, elapsedTime); /* don't modify */
  return 0; /* don't modify */
}