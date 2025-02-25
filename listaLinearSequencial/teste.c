#include "stdio.h"

typedef int TIPOCHAVE;

typedef struct{
    TIPOCHAVE chave;    
}REGISTRO;

int main(void){
TIPOCHAVE num1 = 10;
REGISTRO num2;
num2.chave = 10;
printf("%i \n",num2.chave);

    return 0;
}