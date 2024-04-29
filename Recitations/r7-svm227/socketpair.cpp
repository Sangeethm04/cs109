#include <string.h>
#include <iostream>
#include "syscalls.h"    /* for wrapped system calls */


#define MSGLEN 64

/* global variable (don't modify) */
static char const key[] = "91AcZ4l0nX39)e.xm2l'gu20wsx87s4K7&-*C1Y%>?11niO0=~bzN,}x[$vZ2/5q"; /* pretend both processes have this secret key */

/* prototype (don't modify) */
void crypto(char *buffer);

/* main - only need to make 6 edits here; replace C++-style comments (i.e., "//") with function calls */
int main(void) {
  pid_t pid;
  int sockd[2]; /* the pair of socket descriptors */

  Socketpair(AF_UNIX, SOCK_STREAM, 0, sockd);  /* creates an unnamed pair of connected sockets: sockd[0] and sockd[1] */

  /* In the code below, imagine that the parent process and the child process are two entirely
   * different running programs that want to communicate... perhaps the parent is a server and 
   * the child is a client. The calls to the crypto function are demonstrating how information 
   * can be encrytped for transmission (and should be encrypted if communicating over an insecure
   * network.
   */
  if ((pid = Fork()) != 0) {  // make a call to Fork() to create a child
    /* parent code in here */
    // add a call to Close() to close one end of the socket
    Close(sockd[0]);
    char message[MSGLEN];
    // add a call to Read() to read MSGLEN bytes from sockd[1] into message array
    Read(sockd[1], message, MSGLEN);
        std::cout << "parent: received encrypted message => '" << message << "'" << std:: endl;

    crypto(message);  /* decrypt message from parent */
    std::cout << "\nparent: decrypted message          =>  '" << message << "'" << std:: endl;
    strcpy(message, "That doesn't surprise me!"); 
    crypto(message);    /* encrypt reply to child */
    // add a call to Write() to write the MSGLEN bytes in message array to sockd[1]
    Write(sockd[1], message, MSGLEN);
    // add a call to Wait() to wait for child to die (sounds sad, but it's not) */
    Wait(NULL);
    // add a call to Close() to close the other end of the socket now that we're done
    Close(sockd[1]);
  } else {
    /* child code in here */
    // add a call to Close() to close the other end of the socket (the end being used by the parent)
    Close(sockd[1]);
    char message[MSGLEN] = "Professor Erle has a \"MOM\" tattoo and wears a wig.";
    crypto(message);  /* encrypt message before sending to child */
    // add a call to Write() to write MSGLEN bytes in message array to sockd[0]
    Write(sockd[0], message, MSGLEN);
    // add a call to Read() to read MSGLEN bytes from sockd[0] into message array 
    Read(sockd[0], message, MSGLEN);
    std::cout << "child:  received encrypted reply   => '" << message << std:: endl;
    crypto(message);  /* decrypt reply from parent */
    std::cout << "child:  decrypted reply            => '" << message << "'" << std::endl;    // add a call to Close() to close the other end of the socket now that we're done
    Close(sockd[0]);
  }

  return 0;
}

/* add functionality to crypto function here */

void crypto(char *buffer) {
  for(int i = 0; i < MSGLEN; i++) {
    buffer[i] = buffer[i] ^ key[i];
  }
}


/*
 * Q0: What are two attributes of socketpair()? This is called a "gimme", when someone gives you an easy question.
 * A0: the two attributes of a socketpair are the domain and the type of the socket. in addition to the protocol and file descriptors.
 *     
 *
 * Q1: Creating sockets with socketpair() is SO much easier than the whole socket()/bind()/listen()/connect()/accept() 
 *     process. Why don't we always just use socketpair() for all communications? Hint: read 'man 3p socketpair'... 
 *     which refers you to 'man 2 socketpair'.
 * A1: not meant for communiction across the network. mostly used to interprocess communication.
 *
 * Q2: What is the purpose of the wait system call? Hint: read 'man 3p wait'... which refers you to 'man 2 wait'.
 * A2:  The wait() function suspends execution of its calling process until
 * stat_loc information is available for a terminated child process, or a signal is received. 
 *     
 * Q3: Wait a minute, why are there man pages for these system calls in chapter 3p and chapter 2? In fact, check out 
 *     'man -a socket'... all the chapters with pages on "socket" will be displayed one after the other. (Just hit 'q' 
 *     to move on to the next man page.) When do we use which chapter? Hint: 'man man' may help with some of this answer; 
 *     but you'll probably want to access the ol' Internet.
 * A3: section 2 of manual is for system calls and section 3 is for library functions. there are two three man pages for these system calls because
 * Chapter 3p contains man pages for functions that adhere to the POSIX standard. 
 *
 * Q4: Why is the encrypted message received by the parent so short? And why is the encrypted message received by the 
 *     child split over two lines?
 * A4: this may be due to it only reading a fixed number of bytes from the socket where there may be more. the child process also may read in chunks making it split into new lines as well. 
 *
 * Q5: In the parent (line 33), why didn't we simply assign "That doesn't surprise me!" to the message array variable? 
 *     I.e., why not do the following? message = "That doesn't surprise me!";                                                                                                             
 * A5: beacuse it is an array not a pointer with a fixed size of bytes. therfore we would have to use a strcopy function to copy the message to the array.
 *
 * Q6: Why is it that we can use the same crypto() function to both encrypt and decrypt?
 * A6:  we can use crypto() function to both encrypt and decrypt because the function is using the same key to encrypt and decrypt the message.
 *
 * Q7: After the fork, if the parent process runs before the child, how does the program work given the Read would execute
 *     before the Write?
 * A7: the parent process will wait for the child process to write to socket before reading from it.
 */
