#include <stdio.h>
#include <stdlib.h>
#include "mallocGlobals.h"    /* for macro constants and user-defined data types */
#include "syscalls.h"

int main(int argc, char *argv[]) {
  printf("%d, %p", argc, argv);
  char **memptr = Malloc(KILO * KILO * sizeof(char *));   /* no changes */
  for (int i = 0; i < KILO * KILO; i++) {                 /* no changes */
    /* do not add add'l statements to loop body until instructed */
    memptr[i] = Malloc(PAGE);                             /* no changes */
    memptr[i][KILO] = -1;                                 /* no changes */
    printf("pointer: %p\n", memptr[i]);

  }
  for(int i = 0; i< KILO * KILO; i++) {
  free(memptr[i]);

  } 
   free(memptr);
}
/* Don't you dare put your wrapped malloc function in this file! :-) */

/*
 * Q0: What does this program do? And what is the writing of -1 to memory about?
 * A0: Allocates memory of KILO*KILO amount with PAGE memory bytes in each.-1 just tells the program there is something allocated here which can be used later.
 *
 * Q1: Describe the changes you had to make to get the program to compile without any errors or warnings. 
 *     It is easier to to this if you document here each change you make as you make them.
 * A1: I had to add all the #includes that are necessary so the program knows where to find the header files. Also had to add the Malloc function in syscalls.c as 
 *     well as add the #endifs for header files. 
 *
 * Q2: How many bytes are between the pointers? (answer in decimal)
 * A2: 8 b/c it is a pointer which is always 8
 *
 * Q3: How many bytes are between what the pointers are pointing to? (answer in decimal)
 * A3: 1 byte
 *
 * Q4: Are these the amounts you expected? Why or why not?
 * A4: yes because these 
 *
 * Q5: Describe what you did to fix the valgrind error(s)?
 * A5: I further free the memory of the pointer to the table of pointers in addition to freeing each table.
 *
 */
