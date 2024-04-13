CFLAGS=-g -c -Wall -Wextra -Wwrite-strings
LFLAGS=-g

pipe: pipe.o syscalls.o
	gcc ${LFLAGS} -o pipe pipe.o syscalls.o
pipe.o: pipe.c syscalls.h
	gcc ${CFLAGS} pipe.c
syscalls.o: syscalls.c
	gcc ${CFLAGS} syscalls.c
clean:
	rm -f *.o
	rm -f pipe
