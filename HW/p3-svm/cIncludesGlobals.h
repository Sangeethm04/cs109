#ifndef CINCLUDESGLOBALS_H
#define CINCLUDESGLOBALS_H


typedef enum {
  ASIS,
  STRFWD,
  STRREV,
  NUMFWD,
  NUMREV,
} printMode_t;


typedef struct {
    char filename[256];
    int incCount;
} IncludeFile;

IncludeFile includeFiles[5000]; // Array to store include files
int total;
int sum;

#endif
