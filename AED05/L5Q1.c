
#include "stdio.h"  //bibliotecas
#include "stdbool.h"
#include "stdlib.h"

#pragma region // strutcs e constantes

#define MAX 50  //constante

typedef int TIPOCHAVE;  //tipo chave agora também pode ser chamado de inteiro, algo como um apelido, ou seja, declara variáveis inteiras

typedef struct{     //estrutura da árvoee
    TIPOCHAVE chave;    //id do valor
    struct no *esquerda, *direita;   //valores do nó, sendo esquerda direita e meio
}No;    

typedef No* PONT;


#pragma endregion

#pragma region  //funções


PONT busca(TIPOCHAVE chave, PONT raiz){ //buca pelo nó específico da árvore
    if(raiz == NULL || raiz->chave == chave){return raiz;}  //se a raiz for nula ou a raiz for igual a chave, retorne a raiz
    if(raiz->chave > chave){return busca(chave,raiz->esquerda);} //se a raiz for maior que a chave, então busque n 
    return busca(chave, raiz->direita);  
}

PONT inserir(TIPOCHAVE chave, PONT raiz){   //ponteiro que insere o valor chave na árvore
    if(raiz == NULL){   //se a raiz for nula
        PONT novo = malloc(sizeof(No)); //aloca um novo espaço de memória para o nó
        novo->chave = chave;    //a chave do ponteiro recebe o valor do argumento
        novo->esquerda = novo->direita = NULL;   //e os valores esquerdos e direitos do nó são inicializados como nulos
        return novo;    //retorna o novo nó
    }
    if(chave < raiz->chave){raiz->esquerda = inserir(chave,raiz->esquerda);} //caso a raiz seja menor que a chave, então o valor é inserido à esquerda da raíz
    else if(chave > raiz->chave) {raiz->direita = inserir(chave,raiz->direita);} //caso a raiz seja maior que a chave então o valor é inserido à direita da raíz
    return raiz;    //se nenhuma condição se cumprir, então é retornado a raiz;
}

PONT sucessor(PONT raiz){   
    PONT atual = raiz;  //ponteiro atual é o valor dado no argumento
    while(atual && atual->esquerda != NULL){atual = atual->esquerda;}   //equanto o nó atual e a esquerda do nó direito forem diferentes de nulo, o nó atual passa a ser a esquerda dele até não ter mais um nó esquerdo
    return atual;   //no final retorna o nó mais a esquerda da árvore
}

PONT remover(TIPOCHAVE chave, PONT raiz){
    if(raiz == NULL){return raiz;}      //se a raiz for nula retorne ela mesma
    if(chave < raiz->chave){raiz->esquerda = remover(chave, raiz->esquerda);}   //se a chave for menor ue 
    else if(chave > raiz->chave){raiz->direita = remover(chave,raiz->direita);}
    else{
        if(raiz->direita == NULL){
            PONT temp = raiz->direita;
            free(raiz);
            return temp;
        }
        else if(raiz->direita == NULL){
            PONT temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        PONT temp = sucessor(raiz->direita);
        raiz->chave = temp->chave;
        raiz->direita = remover(raiz->chave, raiz->direita);
    }
    return raiz;
}

#pragma endregion

int main(void){ //tarefa de casa terminar a interface cli
    
    int escolha = 0;
    int chave = 0;
    PONT raiz,resultado = NULL;
    int cond = 0;
    
    do{
    printf("Escolha a sua opção: \n");
    printf("1. Busca um item na árvore\n");
    printf("2. Inserir item na árvore\n");
    printf("3. Sucessor de item na árvore\n");
    printf("4. Remover um elemento da árvore\n");
    printf("5. Para sair do programa\n\n");
    scanf(" %i",&escolha);
    getchar();

    switch(escolha){    //1.busca , 2.inserção, 3.sucessor, 4.remoção
    
        case 1:
        system("clear");
        printf("1. Busca \n\n");
        printf("Digite aqui o valor que deseja encontrar: ");
        scanf("%i",&chave);
        printf("\n");
        resultado = busca(chave,raiz);
        if(resultado!=NULL){
            printf("\nO valor %i foi encontrado!",resultado->chave);
        }else{printf("O valor %i não esta presente na lista!",chave);}
        break;

        case 2:
        system("clear");
        printf("2. Inserir item na lista\n\n");
        printf("Digite aqui o valor que deseja inserir: ");
        scanf("%i",&chave);
        raiz = inserir(chave, raiz);
        break;

        case 3:
        system("clear");
        printf("3. Sucessor de item na lista\n\n");
        printf("Digite aqui o item que seŕa o sucessor na lista: ");
        scanf("%i",&chave);
        resultado = busca(chave,raiz);
        if(resultado!=NULL){
            PONT proximo = sucessor(resultado->direita);
            if(proximo != NULL){
                printf("O sucessor de %i é %i\n",chave,proximo->chave);
            } else {
                printf("O sucessor de %i não foi encontrado \n ",chave);
            }
        }else{
            printf("O valor %i não esta presente na árvore",chave);
        }
        break;

        case 4:
        system("clear");
        printf("4. Remover um elemento da lista\n\n");
        printf("Digite aqui o valor que deseja remover: ");
        scanf("%i",&chave);
        raiz = remover(chave,raiz); 
        break;

        case 5:
        system("clear");
        printf("\nSaindo do programa");
        cond+=1;
        break;

    }
}while(cond==0);
    return 0;
}