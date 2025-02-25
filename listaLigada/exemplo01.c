#include "stdio.h"
#include "malloc.h"
#include "stdbool.h"

#pragma region //structs
typedef int TIPOCHAVE; //tipo chave é um apelido de int

typedef struct{
    TIPOCHAVE chave;    //REGISTRO é um id de da chave
}REGISTRO;

typedef struct aux{     
    REGISTRO registro;   
    struct aux* prox; //endereçp do próximo elemento;
}ELEMENTO;

typedef ELEMENTO* PONTEIRO; //ṕmteiro de um elemento

typedef struct{
    PONTEIRO inicio;    //ponteiro de um elemento inicial;
}LISTA; 
#pragma endregion

void inicializar(LISTA* lista){ 
    lista->inicio = NULL;
}

int tamanho(LISTA* lista){
    PONTEIRO endereco = lista->inicio;
    int tam = 0;
    while(endereco != NULL){
        tam++;
        endereco = endereco->prox;    
    }
    return tam;
}

void exibirLista(LISTA* lista){
    PONTEIRO endereço = lista->inicio;
    printf("Lista : \n");
    while(endereço != NULL){
        printf("%i",endereço->registro);
    }
    printf("\n");
}

PONTEIRO buscaSequencial(LISTA* lista,TIPOCHAVE chave){
    PONTEIRO pos = lista->inicio;
    while(pos != NULL){
        if(pos->registro.chave == chave ){return pos;}
        pos = pos->prox;
    }
    return NULL;
}

PONTEIRO buscaSequencialOrdenada(LISTA* lista, TIPOCHAVE chave){
   PONTEIRO pos = lista->inicio;
   while(pos != NULL && pos->registro.chave < chave) pos = pos->prox;{
    if(pos != NULL && pos->registro.chave == chave){return pos;}
   }
   return NULL;
}

PONTEIRO buscaSequencialExc(LISTA* lista,TIPOCHAVE chave,PONTEIRO* anterior){
    *anterior = NULL;
    PONTEIRO atual = lista->inicio;
    while(atual != NULL && atual->registro.chave < chave){
        *anterior =  atual;
        atual = atual->prox;
    }
    if(atual != NULL && atual->registro.chave == chave){return atual;}
    return NULL;
}

bool inserirElementoListaOrdenada(LISTA* lista,REGISTRO registro){
    TIPOCHAVE chave = registro.chave;
    PONTEIRO anterior, i;
    i = buscaSequencialExc(lista,chave,&anterior);
    if(i != NULL){return false;}
    i = (PONTEIRO) malloc(ELEMENTO);
    i->registro = registro;
    if(anterior == NULL){
        i->prox = lista->inicio;
        lista->inicio = i;
    }
}

int main (void){

    return 0;
}