#include <stdio.h>

int main(int argc, char *argv[]) {  /* or **argv */
  /* Some notes:
   * Refer to the latest slide deck to help you with this assignment.
   * In printf, you can use %p to print out a Pointer (i.e., an address) in hex format.
   * Recall, to access the Address of a variable, use the ampersand (e.g., int x = 5; int *xp = &x
        // xp points to x).
   * Recall, to access the Data stored in a pointer variable, use the asterisk (e.g., int y = *xp + 
        3 // y will equal 8).
   * Recall, a string in C is simply an array of char data types that is null-terminated (\0);
   */

  fprintf(stdout, "argc is stored at address %p and is storing the integer %d\n", &argc, argc);
  fprintf(stdout, "argv is stored at address %p and is storing the address %p\n\n", &argv, argv);
  for (int i = 0; i <= argc; i++) {
    fprintf(stdout, "argv[%d] is stored at address %p and is storing the address %p;\n", i, 
                     &argv[i], argv[i]);
    if (i != argc)
      fprintf(stdout, "        it is pointing to the start of the string: '%s'\n", argv[i]);
  }
  fprintf(stdout, "\n");

  return 0;
}


/* Answer the following questions.
 *
 * Q0: How many bytes apart is argc and argv? Why do you think this is the case?
 * A0: 12. It's possible the number can be different, but should be a multiple of 4. It is 
 *              compiler/processor-related. You can search on "Why are the addresses of argc 
 *              and argv 12 bytes apart" to learn more.
 *
 * Q1: How many bytes apart are the addresses (i.e., pointers) in the argv array? Why are there no gaps in
 *              memory between them?
 * A1: 8. There are no gaps because it is an array, and the program needs to be able to step through the 
 *              array by simply increasing the pointer value. Gaps in memory would waste space and lead to
 *              anarchy.
 *
 * Q2: How could we access the 3rd character in the first argument? (Hint: argv is like an array of arrays.) 
 *              Describe why we we need to access it this way.
 * A2: argv[0][2]; since argv is array of pointers to an array of characters, we first access the pointer of interest
 *              and then access the character of interest in the array of characters at the address the pointer is
 *              pointing to.
 */

