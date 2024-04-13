CFLAGS=-g -c -Wall -Wextra -Wwrite-strings
LFLAGS=-g

buffSize: buffSize.o syscalls.o
	gcc ${LFLAGS} -o buffSize syscalls.o buffSize.o
buffSize.o: syscalls.h buffSize.c
	gcc ${CFLAGS} -DBUFFSIZE=${BUFFSIZE} buffSize.c
syscalls.o: syscalls.c
	gcc ${CFLAGS} syscalls.c
clean:
	rm -f *.o
	rm -f buffSize
