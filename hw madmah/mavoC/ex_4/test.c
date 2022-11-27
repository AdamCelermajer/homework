#include <stdio.h>

void getA(int *a)
{
    a[0] = 512;
    printf("getA %d", a[0]);
}

int main()
{

    int a[5] = {1234, 2, 3, 4, 5};

    getA(a);

    printf("getA %d\n", a[0]);
}