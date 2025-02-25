
#include "stdio.h"  //bibliotecas
#include "stdbool.h"
#include "stdlib.h"

#define MAX 50  //constante

#pragma region // strutcs

typedef int TIPOCHAVE;  //tipo chave agora também pode ser chamado de inteiro, algo como um apelido, ou seja, declara variáveis inteiras

typedef struct{         //registro.chave retorna um inteiro
    TIPOCHAVE chave;    //int chave
}REGISTRO;              //esta variável foi feita em formato de struct para facilitar encontrar seu id;

typedef struct{     //array dos registros
    REGISTRO A[MAX+1];  
    int numElem;
}LISTA;

#pragma endregion

#pragma region  //funções

void inicializaLista(LISTA* lista){ //iicializa a lista zerando o número de valores
    lista->numElem = 0;
}

int tamanhoLista(LISTA* lista){    //retorna o tamanho da lista
    return lista->numElem;
}

void exibirLista(LISTA* lista){    //exibe todos os valores da lista
    printf("Lista: \n");
    for(int i = 0;i < lista->numElem;i++){
        printf("%i ",lista->A[i].chave);    //A[i] aponta para um registro, enquanto A[i].chave aponta para o que o registro guarda
    }
    printf("\n");
}

int buscaSequencial(LISTA* lista, TIPOCHAVE chave){ //busca um valor na lista de 1 em 1 nos indíces
    int i = 0;
    int tam = tamanhoLista(lista);  
    while(i < tam){   //enquanto o i for menor que o tamanho da lista
        if(chave == lista->A[i].chave){return i;}   //se a busca for sucedida, isto é, o valor chave esta incluso na lista, então retorne o indíce
        else{i++;} //senão cheque o próximo indíce
    }
    return -1;  //caso não seja encontrado, retorne -1, significando que o valor não esta na busca
}

int buscaSentinela(LISTA* lista, TIPOCHAVE chave){  //usa um indíce cache para buscar a chave
    int i = 0;
    lista->A[lista->numElem].chave = chave; //o ultimo elemento da lista é o valor que esta sendo buscado
    while(lista->A[i].chave != chave) i++;{ //enquanto o indíce que esta sendo buscado(incrementado de um em um a cada chamada) se a chave da lista no indíce for diferente da chave de busca
        if(i == lista->numElem){return -1;} //se o indíce for igual ao tamanho da lista, retorne falso
        else{return i;}     //senão, no caso se encontrou o indíce que o valor esta presente, retorne o indíce do valor
    }
}

bool inserirElemLista(LISTA* lista,REGISTRO registro,int i){    //empurra a lista para trás e insere o valor no indice escolhido
    if(lista->numElem == MAX || i < 0 || i > lista->numElem){return false;} //se a o tamanho da lista for igual ao máximo, o indíce for 0 ou o indíce for maior que o número de elementos não seŕa permitada a inserção de elementos
    for (int j = lista->numElem; j > i; j--) { //para cada j menor que o indíce novo
        lista->A[j] = lista->A[j - 1];  //passe o elemnto do indíce j para a direita
    }   //após isso deve sobrar um espaço no indíce i
    lista->A[i] = registro; //elemento do indíce 1 recebe o valor pedido pelo usuário;
    lista->numElem++;   //incrementa em 1 o número de elementos da lista
    return true;    //retorna verdadeiro
}

bool excluirElemLista(TIPOCHAVE chave,LISTA* lista){    //
    int pos;        //varíavel que armazena a posição do valor a ser removido
    pos = buscaBinaria(lista,chave);    //busca o valor para descobrir se existe
    if(pos==-1){return false;}  //caso não seja encontrado a remoção é cancelada
    for(int i = pos;i< lista->numElem;i++){ //para cada indíce existente na lista
        lista->A[i] = lista->A[i+1];    //passe ele cima do elemento que deseja excluir, encolhendo a lista
        lista->numElem--;   //diminui a lista
        return true;    //retorna verdadeiro
    }
}

void reinicializarLista(LISTA* lista){  //simplesmente zera todos os valores da lista
    lista->numElem = 0;
}

bool inserirElemListaOrd(LISTA* lista,REGISTRO registro){   
    if(lista->numElem >= MAX){return false;}    //se o número de elementos for maior ou igual ao máximo retorne falso
    int pos = lista->numElem;   //a posição é o numero de elementos
    while(pos > 0 && lista->A[pos-1].chave > registro.chave){   //enquanto a posição for maior que 0 e a chave da posição anterior for maior que a chave
        lista->A[pos] = lista->A[pos-1];    //a chave da posição é passada para a esquerda
        pos--;  //e a posição passa para a esquerda
    }
    lista->A[pos] = registro;   //após a organização, a posição recebe a chave desejada
    lista->numElem++; //e a lista aumenta de tamanho
}

int buscaBinaria(LISTA* lista,TIPOCHAVE chave){
    int esq,dir,meio;   //cria três posições chaves
    esq = 0;    //a esquerda é o primeiro indíce
    dir = lista->numElem-1; //a direita é o ultimo índice
    while(esq<=dir){    //enquanto a esquerda for menor ou igual à direita
        meio = (esq + dir) / 2; //o meio a média aritmética da esquerda e direita
        if(lista->A[meio].chave == chave){return meio;} //se o índice do meio tiver a mesma chave que a chave da busca, retorne o meio
        else if (lista->A[meio].chave < chave){esq = meio +1;} //senão se o meio tiver a chave menor, aumente em um o meio
        else{dir = meio -1;}    //se não se o meio tiver uma chave maior, diminue em 1 o meio
    }
    return -1;  //caso não seja encontrado retorne falso
}

#pragma endregion

int main(void){ //tarefa de casa terminar a interface cli
    LISTA lista01;
    inicializaLista(&lista01);
    char escolha = '/';
    int chave = 0;
    REGISTRO teste;
    int resultado = 0;
    switch(escolha){
        case '1':
        system("clear");
        printf("1. Exibir o tamanho da lista\n\n");
        tamanhoLista(&lista01);
        break;

        case '2':
        system("clear");
        printf("2. Exibir todos os valores da lista\n\n");
        exibirLista(&lista01);
        break;

        case '3':
        system("clear");
        printf("3. Busca sequencial \n\n");
        printf("Digite aqui o valor que deseja encontrar: ");
        scanf("%i",&chave);
        printf("\n");
        resultado = buscaSequencial(&lista01,chave);
        if(resultado > 0){
            printf("\nO valor %i foi encontrado!, está presente no indíce %i da lista :",lista01.A[resultado],resultado);
        }else{printf("O valor %i não esta presente na lista!",chave);}
        break;

        case '4':
        system("clear");
        printf("4. Busca sentinela \n\n");
        printf("Digite aqui o valor que deseja encontrar: ");
        scanf("%i",&chave);
        printf("\n");
        resultado = buscaSentinela(&lista01,chave);
        if(resultado > 0){
            printf("\nO valor %i foi encontrado!, está presente no indíce %i da lista :",lista01.A[resultado],resultado);
        }else{printf("O valor %i não esta presente na lista!",chave);}
        break;
        
        case '5':
        system("clear");
        printf("5. Inserir item na lista\n\n");
        printf("Digite aqui o valor que deseja inserir: ");
        scanf("%i",&teste.chave);
        inserirElemLista(&lista01,teste,tamanhoLista(&lista01));
        break;

        case '6':
        system("clear");
        printf("6. Remover um elemento da lista\n\n");
        printf("Digite aqui o valor que deseja remover: ");
        scanf("%i",&chave);
        if(excluirElemLista(chave,&lista01)){printf("\nElemento %i removido com sucesso!",chave);}
        else{printf("\nElemento não existe na lista!");}
        break;

        case '7':
        system("clear");
        printf("7. Reinicializar a lista\n\n");
        reinicializarLista(&lista01);
        printf("Lista renicializada com sucesso!");
        break;
        default:
        printf("Escolha inválida! \n");
        break;

        case '8':
        system("clear");
        printf("8. Inserir ordenamente\n\n");
        printf("Digite aqui o valor que deseja inserir: ");
        scanf("%i",&teste);
        if(inserirElemListaOrd(&lista01,teste)){printf("\nElemento %i inserido ordenamente com sucesso!",teste.chave);}
        else{printf("\nUm erro ocorreu durante a inserção!");}
        break;

        case '9':
        system("clear");
        printf("9. Busca binária \n\n");
        printf("Digite aqui o valor que deseja buscar: ");
        scanf("%i",&chave);
        resultado = buscaBinaria(&lista01,chave);
        if(resultado>0){printf("O valor foi encontrado no índice %i da lista!",resultado);}
        else{printf("O valor %i não foi encontrado!",chave);}
    }
    return 0;
}