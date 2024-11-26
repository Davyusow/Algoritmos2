//insertion-sort
#include "stdio.h"

void insertionSort(int x[],int tam){ //inicio da função, parametros x -> vetor, tam -> tamanho do vetor
    int i,j,chave; //i laço da primeira busca, j -> laço da ordenação, chave é o valor sendo comparado
    for(i = 0;i<tam-1;i++){   //percorre os valores do vetor
        if(x[i]>x[i+1]){    //se o valor atual for maior que o valor da frente
            chave = x[i+1]; //o novo item comparado é o i+1
            x[i+1] = x[i];  //o valor da frente volta
            x[i] = chave; //o valor comparavel vai pra posição atual
            j = i-1; //valor para a verificação da lista de maneira decrementativa
            while(j>=0){ //enquanto o j estiver no array
                if(chave<x[j]){ //se o valor comparado é menor que o de trás
                    x[j+1] = x[j]; //então troca
                    x[j] = chave; //então troca
                }else{  //senão
                    break; //termina a verificação
                }
                j=j-1;  //compara com o anterior
            }
        }
    }
}

int main(void){
    int x[] ={9,8,7,6,5,4,3,2,1};
    int tam = sizeof(x)/sizeof(x[0]);
    insertionSort(x,tam);
    for(int i=0;i<tam+1;i++){
        printf("x[%i] = %i \n",i,x[i]);
    }
    return 0;
}