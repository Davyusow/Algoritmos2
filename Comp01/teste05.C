#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"
#include "search.h"

bool Exemplo05(int idades[],int v[]){
    int tam = sizeof(idades)/sizeof(idades[0]);
    int menorIdade = 200;
    for(int i=0;i<tam;i++){     //O(N)
        if(idades[i]<menorIdade){
            menorIdade = idades[i];
        }
    }
    int cont = 0;
    for(int i=0;i<tam;i++){ //O(N)
        if(v[i]==menorIdade){
            cont++;
        }
    }
    return cont >1;
}
//complexidade : O(N) + O(N) = O(N)
void insertionSort(int x[],int tam){ //inicio da função, parametros x -> vetor, tam -> tamanho do vetor
    int i,j,chave; //i laço da primeira busca, j -> laço da ordenação, chave é o valor sendo comparado
    for(i = 0;i<tam-1;i++){   //percorre os valores do vetor, complexidade = O(N)
        if(x[i]>x[i+1]){    //se o valor atual for maior que o valor da frente
            chave = x[i+1]; //o novo item comparado é o i+1
            x[i+1] = x[i];  //o valor da frente volta
            x[i] = chave; //o valor comparavel vai pra posição atual
            j = i-1; //valor para a verificação da lista de maneira decrementativa
            while(j>=0){ //enquanto o j estiver no array, complexidade = O(N)
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
    //complexidade: O(N)*O(N) = O(N²)
}

bool exemplo06(int idades[]){
    insertionSort(idades,sizeof(idades)/sizeof(idades[0])); //complexidade = O(N²)
    return idades[0]==idades[1];
    //complexidade : O(N²)
}