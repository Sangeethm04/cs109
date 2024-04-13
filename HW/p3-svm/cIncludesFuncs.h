#include "cIncludesGlobals.h"
#ifndef CINCLUDESFUNCS_H
#define CINCLUDESFUNCS_H


void parseArgsAndOpenFiles(int argc, char** argv, FILE** cFile, DIR** dir, int* total, int *sum, IncludeFile ** headerFiles);
void addFile(FILE* cFile, int *total, int *sum, IncludeFile ** headerFiles);
void addIncludeFile(const char * filename);
int compareIncludeFiles(const void *a, const void *b);
void printData(printMode_t printMode, int numHeaders, IncludeFile ** headerFiles);



#endif


