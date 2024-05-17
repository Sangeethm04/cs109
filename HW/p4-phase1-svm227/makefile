CFLAGS=-g -c -Wall -Wextra -Wwrite-strings
LFLAGS=-g

procInfo: procInfo.o syscalls.o Process.o
	g++ ${LFLAGS} -o procInfo procInfo.o syscalls.o Process.o
procInfo.o: procInfo.cpp Process.h syscalls.h
	g++ ${CFLAGS} procInfo.cpp
Process.o: Process.cpp Process.h syscalls.h
	g++ ${CFLAGS} Process.cpp
syscalls.o: syscalls.c
	g++ ${CFLAGS} syscalls.c
clean:
	rm -f *.o
	rm -f procInfo
