CFLAGS=-g -c -Wall -Wextra -Wwrite-strings
LFLAGS=-g

procInfo: procInfo.o syscalls.o
	g++ ${LFLAGS} -o procInfo procInfo.o syscalls.o
procInfo.o: procInfo.cpp Process.h syscalls.h
	g++ ${CFLAGS} procInfo.cpp
syscalls.o: syscalls.c
	g++ ${CFLAGS} syscalls.c
clean:
	rm -f *.o
	rm -f procInfo
