#include <stdio.h>
#include <stdlib.h>

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int get_val(int *a, int *b)
{
    return (*a)*(*b);
}

void print_area(int(*p)(int *x, int *y), int *x, int *y)
{
    int t = p(x, y);
    printf("the val is %d\n", t);
}

int main()
{
   int a = 2;
   int b = 3;

   int (*p)(int *, int *);
   p = get_val;
   print_area(p, &a, &b);

   printf("before swap value a=%d, b =%d\n", a, b);
   swap(a, b);
   printf("after swap value a=%d, b=%d\n", a, b);
   return 0;
}
