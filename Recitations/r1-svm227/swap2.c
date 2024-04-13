#include <stdio.h>

void swap(int *, int *);
 
int main() {
  int *x = -1;    /* can have any value here */
  int *y =  1;    /* and here */
  fprintf(stdout, "Before swap: x = %d, y = %d\n", x, y); /* can use printf */
  swap(x, y);
  fprintf(stdout, "After swap:  x = %d, y = %d\n", x, y);
  return 0;
}

void swap(int *a, int *b) {
  int *tmp = a;  /* assign a to tmp */
  a = b;       /* assign b to a */
  b = tmp;      /* assign tmp to b */
  return;
}

/*
Q0: What was passed?
A0: the actual value was passed which is -1 and 1 in hexadecimal which is with the many fs to denote -1
Q1: Why did the code change x and y or why did it not change x and y?
A1: the code didn't change because it was passing in the pass the address because there is no address in pointer x or y.
*/
