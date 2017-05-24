#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char* hello = "abcdef";

void getMacAddr()
{
    unsigned char world[10];
    memcpy(world, hello, 6);

    printf("the str is %x\n", world);
    printf("the str is %s\n", world);
}

int main()
{
    getMacAddr();
    /*
    printf("the length is %d\n", strlen(world));
    int i =0;
    for (i; i < strlen(world); i++) {
        printf("the value of str is %02x\n", world[i]);
        printf("the value of str is %c\n", world[i]);
    }

    for (i = 0; i < strlen(hello); i++) {
        printf("the value of str is %02x\n", hello[i]);
    }
    */
    return 0;
}
