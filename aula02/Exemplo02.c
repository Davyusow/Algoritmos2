#include "stdio.h"

int main(void)
{ // testes de ponteiro
    int x = 25;
    int *y = &x;
    *y = 30;
    printf("O valor atual de x é %i\n", x);
    return 0;
}