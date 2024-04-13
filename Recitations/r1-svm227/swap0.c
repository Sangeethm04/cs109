#include <stdio.h>

void swap(int, int);
 
int main() {
  int x = -1;    /* can have any value here */
  int y =  1;    /* and here */
  fprintf(stdout, "Before swap: x = %d, y = %d\n", x, y); /* can use printf */
  swap(x, y);
  fprintf(stdout, "After swap:  x = %d, y = %d\n", x, y);
  return 0;
}

void swap(int a, int b) {
  int tmp = a;  /* assign a to tmp */
  a = b;        /* assign b to a */
  b = tmp;      /* assign tmp to b */
  return;
}

/*
Q0: What was passed?
A0:The actual number was passed so it was pass by value not the address
Q1:Why did the code change x and y or why did it not change x and y?
A1:the code did not change x or y because the actual value is being changed for a and b not the reference to x or y. 
*/
