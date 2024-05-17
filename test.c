#include <stdio.h>

int main() {
    short num = 1;
    char *ptr = &num;

    if (*ptr == 1) {
        printf("Little Endian\n");
    } else {
        printf("Big Endian\n");
    }

    return 0;
}