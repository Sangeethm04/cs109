#ifndef FILEPLAYGLOBALS_H
#define FILEPLAYGLOBALS_H

#define FILE_SIZE  1048576
#define NUM_MSGS   4
#define MSG_LENGTH 16

typedef enum {
  AS_IS,
  LOWER,
  UPPER
} emode_t;

typedef union {
  unsigned short var[MSG_LENGTH>>1];
  char str[MSG_LENGTH];
} message_t;

#endif
