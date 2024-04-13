#include <stdio.h>

#include <stdlib.h>

#include "filePlayGlobals.h"    /* for macro constants and user-defined data types */

#include "syscalls.h"






//- check if the user has provided a binary file within the command line
//- use our wrapped Fopen() function to open the command file
//- read in the command file to check if we want to read or write to the binary file
//- use Fopen()'s 'a' mode to create a new file
//- use system("dev/urandom/") to create random text within bFile
//1MBbinaryFile
emode_t parseArgsAndOpenFiles(int argc, char ** argv, FILE ** cFile, FILE ** bFile) {
  char chrac[100];
  if (argc == 4) {
    * cFile = Fopen(argv[2], "r+");
    * bFile = Fopen(argv[3], "r+");
    //Fopen("1MBfile.in", "rb+");
    if (argv[1][1] == 'U' || argv[1][1] == 'u' || argv[1][1] == 'a' || argv[1][1] == 'A' || argv[1][1] == 'l' || argv[1][1] == 'L') {
      switch (argv[1][1]) {
        case 'u':
        case 'U':
          for (int i = 0; chrac[i] != '\0'; i++) {
            if (chrac[i] >= 'a' && chrac[i] <= 'z') {
              chrac[i] = chrac[i] - 32;
            }
          }
          fprintf(stdout, "%s\n", chrac);
          //printf(stdout, "%c", word[1]);

          break;
        case 'l':
        case 'L':
          for (int i = 0; chrac[i] != '\0'; i++) {
            if (chrac[i] >= 'A' && chrac[i] <= 'Z') {
              chrac[i] = chrac[i] + 32;
            }
          }
          fprintf(stdout, "%s\n", chrac);
          //printf(stdout, "%c", word[1]);

          break;
        case 'a':
        case 'A':
          fprintf(stdout, "%s\n", chrac);
          //fprintf(stdout, "R");
          break;
      }
    } else if (argc == 3) {
      * cFile = Fopen(argv[2], "r");
      System("dd if=/dev/urandom of=1MBbinaryFile bs=1M count=1");
      * bFile = Fopen("1MBbinaryFile", "r+");

      /* if (argv[1][1] == 'U' || argv[1][1] == 'u' || argv[1][1] == 'a' || argv[1][1] == 'A' || argv[1][1] == 'l' || argv[1][1] == 'L') {
         printf("correct letter input");
       } else {
         exit(97);
       }*/

    } else {
      fprintf(stdout, "hello there");
      exit(97);
    }
    return AS_IS;
  }
}

//acce[ts pointer to binary file
//r0
//reads
//getLine
//scanf
//reading from cFile line by line with getline
//scanf
void runCommands(FILE * cFile, FILE * bFile, message_t messages[]) {
  char * buffer = NULL;
  size_t length = 0;
  size_t chars_read = 1;
  char c = 0;
  char chrac[100];
  int num2 = 0;
  int num3 = 0;
  int scanreturn = 0;
  //use sscanf to read in the command file
  //printf("%c, %d %d", & c, & num2, & num3);

  //w 28786  # write this short into the file at the current location
  //s 0 435362  # seek to offset 435362
  //r 1 2  # read two bytes and place into messages[1] starting at byte offset 4
  //# to see "rp", use GDB! print messages[1].str[4] <== should return 'r'; str[5] should have 'p'
  if ((c == 'w' || c == 'W') && scanreturn != 2) {
    fprintf(stderr, "Error: w command requires 2 arguments\n");
  } else if ((c == 's' || c == 'S') && scanreturn != 3) {
    fprintf(stderr, "Error: s command requires 3 arguments\n");
  } else if ((c == 'r' || c == 'R') && scanreturn != 3) {
    fprintf(stderr, "Error: r command requires 3 arguments\n");
  }
  while (getline( & buffer, & length, cFile) != -1) {
    scanreturn = sscanf(buffer, "%c %d %d", & c, & num2, & num3);
    //use switch statement to check for the command
    switch (c) {
      case 's':
      case 'S':
        scanreturn = sscanf(buffer, "%c %d", & c, & num2);
        Ftell(bFile);
        // commmand used - s 435362  # seek to offset 435362
        Fseek(bFile, num3,num2);
        

        break;
      case 'w':
      case 'W':
        scanreturn = sscanf(buffer, "%c %d", & c, & num2);
        Ftell(bFile);
        // commmand used - w 28786  # write this short into the bfile at the current location
        // Fseek(bFile, num2);
        short data = num2;
        Fwrite( & data, sizeof(short), 1, bFile);
        break;
      case 'r':
      case 'R':
        scanreturn = sscanf(buffer, "%c %d %d", & c, & num2, & num2);
        Fread( & (messages[num2].var[num3]), sizeof(short), num3, bFile);
        break;
    }
  }
}


void printPhrases(message_t messages[4], emode_t mode) {
  for (int i = 0; i < 4; i++) {
    switch (mode) {
      case AS_IS:
        fprintf(stdout, "%s\n", messages[i].str);
        break;
      case LOWER:
        for (int j = 0; messages[i].str[j] != '\0'; j++) {
          if (messages[i].str[j] >= 'A' && messages[i].str[j] <= 'Z') {
            messages[i].str[j] = messages[i].str[j] + 32;
          }
        }
        fprintf(stdout, "%s\n", messages[i].str);
        break;
      case UPPER:
        for (int j = 0; messages[i].str[j] != '\0'; j++) {
          if (messages[i].str[j] >= 'a' && messages[i].str[j] <= 'z') {
            messages[i].str[j] = messages[i].str[j] - 32;
          }
        }
        fprintf(stdout, "%s\n", messages[i].str);
        break;
    }
  }

}

void closeFiles(FILE * cFile, FILE * bFile) {
  Fclose(cFile);
  Fclose(bFile);

}