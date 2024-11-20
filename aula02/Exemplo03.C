#include "stdio.h"
#include "malloc.h"

int main(void)
{

    int *y = (int *)malloc(sizeof(int));
    *y = 20;
    int z = sizeof(int);
    printf(" *y = %i \n z = %i \n", *y, z);

    return 0;
}