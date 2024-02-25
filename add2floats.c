#include <stdio.h>   /* for fprintf */

#include <stdint.h>  /* for uintX_t */

#include <stdlib.h>  /* for exit */

#include <stdbool.h> /* for booleans */

/* do not change prototypes */
bool parseArgs(int, char ** );
float readHex(char * );
void genHex(float, char * );

int main(int argc, char ** argv) {
  bool testMode = parseArgs(argc, argv);
  float f0 = 0, f1 = 0, f2 = 0;
  if (testMode) {
    /* insert code here; ok to use floating-point addition available in C (e.g., f2 = f0 + f1) */
    if (sscanf(argv[3], "%f", & f1) != 1) {
      printf("invalid2");
    }
    if (sscanf(argv[2], "%f", & f0) != 1) {
      printf("invalid3");
    }
    f2 = f0 + f1;
    fprintf(stdout, "%e + %e = %e\n", f0, f1, f2); /* do not change */
  } else {
    /* insert code here; MUST perform floating-point addition manually by aligning mantissas based on exponent values */
    f0 = readHex(argv[2]);
    f1 = readHex(argv[3]);

   
    
    char str[9] = {
      0
    }; /* do not change */
    genHex(f2, str); /* do not change */
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
    }
    else if (str[i] >= 'a' && str[i] <= 'f') {
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
  }u;
  (void)u;
  /* insert code here */
}