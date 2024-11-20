#include "stdio.h"
#include "stdlib.h"

void imprimir(char *w)
{
    printf("\nw0 = %i, w1 = %i, w1 = %i\n", w[0], w[1], w[2]);
    printf(" &w = %p, w = %p, *w =%i ", &w, w, *w);
    w[0] = 21;
    w[1] = 23;
    w[2] = 25;
}

int main(void)
{
    char tamX = 3;
    char x[tamX] = {1, 2, 7};
    imprimir(x);
    // criação de variável tipo arranjo/matriz com 3 espaços de memória
    // OBS char vai de 0 a 255, logo armmazena menos memória que o short, int, long, float e String!
    // use char como um número para diminuir o custo de memória
    printf("\nx0 = %i, x1 = %i, x1 = %i\n", x[0], x[1], x[2]);
    printf(" &x = %p, x = %p, *x =%i \n", &x, x, *x);

    return 0;
}