#ifndef FILEPLAYFUNCS_H
#define FILEPLAYFUNCS_H

emode_t parseArgsAndOpenFiles(int argc, char** argv, FILE** cFile, FILE** bFile);
void runCommands(FILE* cFile, FILE* bFile, message_t message[]);
void printPhrases(message_t message[], emode_t mode);
void closeFiles(FILE* cFile, FILE* bFile);

#endif
