#include "stdio.h"
#include "malloc.h"

typedef struct aux{
    int cpf;
    int idade;
    struct aux* conjugue;   //posso linkar uma pessoa a outra
}Pessoa;

void imprimirCpf(Pessoa pessoa){
    if(pessoa.conjugue != NULL ){
        printf("Cpf's: %i x %i \n",pessoa.cpf,pessoa.conjugue->cpf);    //um ótimo exemplo é pedir informações de uma pessa apartir de outra
    }else{
        printf("Cpf: %i\n",pessoa.cpf);
    }
}
void imprimirIdade(Pessoa pessoa){
    if(pessoa.conjugue != NULL ){
        printf("Idades: %i x %i \n",pessoa.idade,pessoa.conjugue->idade);    //um ótimo exemplo é pedir informações de uma pessa apartir de outra
    }else{
        printf("idade: %i\n",pessoa.idade);
    }
}

void envelhecer1(Pessoa pessoa){    //muda apenas variável local
    pessoa.idade++;
}
void envelhecer2(Pessoa* pessoa){
    pessoa->idade++;
}
void envelhecer3(Pessoa pessoa){
    if(pessoa.conjugue != NULL ){
        pessoa.conjugue->idade++;
    }
}
void envelhecer4(Pessoa* pessoa){
    if(pessoa->conjugue != NULL ){
        pessoa->conjugue->idade++;
    }
}

int main (void){
    Pessoa p1;
    Pessoa p2;
    Pessoa p3;  //solteira
    p1.cpf = 123123123;
    p1.idade = 20;

    p2.cpf = 321312321;
    p2.idade = 21;

    p3.cpf = 456456456;
    p3.idade = 19;

    p1.conjugue = &p2;
    p2.conjugue = &p1;
    p3.conjugue = NULL;
    imprimirCpf(p1);
    imprimirCpf(p2);
    imprimirCpf(p3);
    
    printf("\n\n");
    imprimirIdade(p1);
    envelhecer1(p1);
    imprimirIdade(p1);
    envelhecer2(&p1);
    imprimirIdade(p1);
    envelhecer3(p1);
    imprimirIdade(p1);
    envelhecer4(&p1);
    imprimirIdade(p1);
    
    return 0;
}