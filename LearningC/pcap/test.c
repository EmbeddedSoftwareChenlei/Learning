#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a = 0X1234;
    int b = ntohs(a);
    printf("a==>%02X, b==>%02X", a, b);
}
