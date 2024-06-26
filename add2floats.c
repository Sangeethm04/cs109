#include <stdio.h>   /* for fprintf */

#include <stdint.h>  /* for uintX_t */

#include <stdlib.h>  /* for exit */

#include <stdbool.h> /* for booleans */

/* do not change prototypes */
bool parseArgs(int, char ** );
float readHex(char * );
void genHex(float, char * );

typedef union {
  float f;
  uint32_t i;
}
floatss;

int main(int argc, char ** argv) {
  bool testMode = parseArgs(argc, argv);
  floatss f0, f1, f2;
  if (testMode) {
    /* insert code here; ok to use floating-point addition available in C (e.g., f2 = f0 + f1) */
    if (sscanf(argv[3], "%f", & f1) != 1) {
      printf("invalid2");
    }
    if (sscanf(argv[2], "%f", & f0) != 1) {
      printf("invalid3");
    }
    f2.f = f0.f + f1.f;
    fprintf(stdout, "%e + %e = %e\n", f0, f1, f2); /* do not change */
  } else {
    /* insert code here; MUST perform floating-point addition manually by aligning mantissas based on exponent values */
    f0.f = readHex(argv[2]);
    f1.f = readHex(argv[3]);

    int f0exp = ((f0.i & 0x7F800000) >> 23);
    int f1exp = ((f1.i & 0x7F800000) >> 23);


    printf("f0: %f\n", f0.f);
    printf("f1 :  %f\n", f1.f);
    printf("f0exp:%i\n", f0exp);
    printf("f1exp: %i\n", f1exp);

    uint32_t mantf0 = (f0.i & 0x7FFFFF) | 0x800000;
    uint32_t mantf1 = (f1.i & 0x7FFFFF) | 0x800000;



    printf("f0: %i\n", mantf0);
    printf("f1: %i\n", mantf1);



    //aligning mantisses
    if (f0exp > f1exp) {
      mantf1 >>= (f0exp - f1exp);
      f1exp = f0exp;
    } else {
      mantf1 = mantf1 >> (f1exp - f0exp);
      f0exp = f1exp;
    }

    uint32_t mantf2 = mantf0 + mantf1; //adding mants
    int f2exp;
    if (mantf2 & 0x1000000) {
      mantf2 >>= 1;
      f2exp = f0exp + 1;
    } else {
      f2exp = f0exp;
    }


    //comb the sign bit and expo
    f2.i = ((f0.i & 0x80000000) | (f2exp << 23) | (mantf2 & 0x7FFFFF));




    printf("f2: %f\n", f2.f);


    char str[9] = {
      0
    }; /* do not change */
    genHex(f2.i, str); /* do not change */
    fprintf(stdout, "%s + %s = %s\n", argv[2], argv[3], str); /* do not change */
  }
  return 0;
}

/* supporting functions */

bool parseArgs(int argc, char ** argv) {
  /* insert code here */
  if (argc == 4) {
    if (argv[1][1] == 't' || argv[1][1] == 'T') {
      return true;
    } else if (argv[1][1] == 'x' || argv[1][1] == 'X') {
      return false;
    } else {
      printf("Hello");
      exit(97);
    }
  }
  exit(99);

}

float readHex(char * str) {
  union {
    float f;
    uint8_t b[4];
  }
  u;
  char c;
  char d;
  char e;
  int count = 3;
  for (int i = 0; i < 8; i++) {
    if (str[i] >= '0' && str[i] <= '9') {
      c = str[i] - '0';
    } else if (str[i] >= 'A' && str[i] <= 'F') {
      c = str[i] - 'A' + 10;
    } else if (str[i] >= 'a' && str[i] <= 'f') {
      c = str[i] - 'a' + 10;
    } else {
      exit(98);
    }

    if (i % 2 == 0) {
      c <<= 4;
      d = c;
    } else {
      e = c | d;
      u.b[count--] = e;
    }
  }
  /* insert code here */
  return u.f; /* do not change */
}

void genHex(float f, char * str) {
  union {
    float f;
    uint8_t b[4];
  }
  u;
  /* insert code here */

  u.f = f;
  for (int i = 0; i < 4; i++) {
    int a = u.b[i] >> 4;
    int b = u.b[i] & 0x0F;
    if (a >= 0 && a <= 9) {
      str[i * 2] = a + '0';
    } else {
      str[i * 2] = a + 'A' - 10;
    }
    if (b >= 0 && b <= 9) {
      str[i * 2 + 1] = b + '0';
    } else {
      str[i * 2 + 1] = b + 'A' - 10;
    }
  }
}