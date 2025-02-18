#include "stdio.h"
#include "stdlib.h"

int main(void)
{
    int x[3];
    x[0]= 1 ;
    x[1]= 2 ;
    x[2]= 7 ;
    
    int* y= (int*) malloc(sizeof(int)*3);
    y[0] = 4;
    y[1] = 5;
    y[2] = 6;

    *y=*x;
    free(y);

    return 0;
}