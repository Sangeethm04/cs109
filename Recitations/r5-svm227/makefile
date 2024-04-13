CFLAGS=-g -c -Wall -Wextra -Wwrite-strings
LFLAGS=-g

malloc: malloc.o syscalls.o
	gcc ${LFLAGS} -o malloc malloc.o syscalls.o
malloc.o: malloc.c mallocGlobals.h syscalls.h
	gcc ${CFLAGS} malloc.c
syscalls.o: syscalls.c
	gcc ${CFLAGS} syscalls.c
clean:
	rm -f *.o
	rm -f malloc
