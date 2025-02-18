#include "stdio.h"

typedef struct
{
    short peso;   // peso em kg
    short altura; // altura em cm
} PesoAltura;

#define alturaMaxima 255 // sempre que escrever "alturaMaxima" retorna 255

int main(void)
{

    PesoAltura pesssoa1;
    pesssoa1.peso = 80;
    pesssoa1.altura = 185;
    printf("Peso: %i \nAltura: %i\n", pesssoa1.peso, pesssoa1.altura);

    if (pesssoa1.altura < alturaMaxima)
    {
        printf("\nAltura abaixo da máxima\n");
    }
    else
    {
        printf("\nAltura acima da máxima\n");
    }

    return 0;
}