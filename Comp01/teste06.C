#include "stdio.h"

void inverterLista(int v[],int tam){
    --tam;
    int limite = tam/2; 
    int chave = 0;
    for(int i = 0;i<limite;i++){
        chave = v[i];
        v[i] = v[tam-i];
        v[tam-i] = chave;
    }
}


int main(void){
    int v[]={1,2,3,4,5,6,7,8,9};
    int tam = sizeof(v); 
    printf("tam = %i \n\n",tam);
    tam = sizeof(v)/sizeof(v[0]); 
    printf("tam = %i \n\n",tam);
    for(int i = 0;i<tam;i++){
        printf("\n v[%i] = %i \n",i,v[i]);
    }
    inverterLista(v,tam);
    
    for(int i = 0;i<tam;i++){
        printf("v[%i] = %i \n",i,v[i]);
    }
    return 0;
}