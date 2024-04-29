#include <stdio.h>

void flipSign(float *);

int main() {
  float f = 33.33;
  flipSign(&f);
  fprintf(stdout, "%f\n", f);
  return 0; 
}

void flipSign(float *f) {
    float z = -1.0;
    *f = *f * z;
}