#include "stdio.h"

typedef struct aux{
    int cpf;
    int idade;
    struct aux* conjugue;
}Pessoa;


int main (void){
    Pessoa p1;
    Pessoa p2;
    return 0;
}