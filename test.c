#include <stdio.h>

void modifyValue(int ptr) {
    ptr = 10;  // Modifying the value at the memory location pointed to by ptr
}

int main() {
   int num;
   char chars;

    printf("Enter an integer: ");
    scanf("%d %c", &num, &chars);  // Reads an integer from standard input
    num = 45;
    printf("You entered: %d\n", num);
    printf("You entered: %c\n", chars);

    return 0;

}