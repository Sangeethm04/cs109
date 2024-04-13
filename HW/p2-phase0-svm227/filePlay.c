#include <stdio.h>              /* for FILE */
#include "filePlayGlobals.h"    /* for macro constants and user-defined data types */
#include "filePlayFuncs.h"      /* for functions */

int main(int argc, char** argv) {
  FILE* cFile = NULL;
  FILE* bFile = NULL;
  emode_t mode = AS_IS;
  message_t messages[4] = { 0 };
  
  mode = parseArgsAndOpenFiles(argc, argv, &cFile, &bFile);
  runCommands(cFile, bFile, messages); 
  //printPhrases(messages, mode);
  //closeFiles(cFile, bFile);
  
  return 0;
}

