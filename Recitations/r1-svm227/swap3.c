#include <stdio.h>

void swap(int *, int *);
 
int main() {
  int x = -1;    /* can have any value here */
  int y =  1;    /* and here */
  fprintf(stdout, "Before swap: x = %d, y = %d\n", x, y); /* can use printf */
  swap(&x, &y);
  fprintf(stdout, "After swap:  x = %d, y = %d\n", x, y);
  return 0;
}

void swap(int *a, int *b) {
  int tmp = *a;  /* assign a to tmp */
  *a = *b;       /* assign b to a */
  *b = tmp;      /* assign tmp to b */
  return;
}

/*
Q0: What was passed?
A1: the address was passed to the method.
Q1: why did the code change x and y or why did it not change x and y:
Q2: it changed because the address was being passed it and therefore dereferncing it changed the actual value of x and y;
*/
