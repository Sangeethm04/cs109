
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
/*ssize_t getLine(char **lineptr, size_t *n, FILE *stream*/
/*int sscanf(const char *str, const char *format, ...);*/
int main() {
ssize_t numChars = 0;
char *buffer = NULL; /*will hold address of memoryy created by getline*/
size_t length = 0;/*an unsigned integer*/
while(munChars = getline(buffer,length ,stdin)!=-1){
fprintf(stderr, "numChars = %d\n", numChars);
fprintf(stderr, "length = %d\n", length);
fprintf(stderr, "buffer length = %zu \n", strlen(buffer);
}
return 0;

}
