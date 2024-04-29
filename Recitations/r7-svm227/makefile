CFLAGS=-g -c -Wall -Wextra -Wwrite-strings
LFLAGS=-g

socketpair: socketpair.o syscalls.o
	g++ ${LFLAGS} -o socketpair socketpair.o syscalls.o
socketpair.o: socketpair.cpp syscalls.h
	g++ ${CFLAGS} socketpair.cpp
syscalls.o: syscalls.c
	g++ ${CFLAGS} syscalls.c
clean:
	rm -f *.o
	rm -f socketpair
