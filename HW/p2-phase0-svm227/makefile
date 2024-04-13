CFLAGS=-g -c -Wall -Wextra -Wwrite-strings
LFLAGS=-g

filePlay: filePlay.o filePlayFuncs.o syscalls.o
	gcc ${LFLAGS} -o filePlay filePlay.o filePlayFuncs.o syscalls.o
filePlay.o: filePlay.c filePlayFuncs.h filePlayGlobals.h
	gcc ${CFLAGS} filePlay.c
filePlayFuncs.o: filePlayFuncs.c syscalls.h filePlayGlobals.h
	gcc ${CFLAGS} filePlayFuncs.c
syscalls.o: syscalls.c
	gcc ${CFLAGS} syscalls.c
clean:
	rm -f *.o
	rm -f malloc
