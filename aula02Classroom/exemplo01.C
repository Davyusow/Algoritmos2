//somatória de arrays com retorno em forma de raíz
#include "stdio.h"
#include "math.h"

double Norma(int x[], int tam){ //array como parâmetro
    double soma = 0;   //inicializando variável da soma
    for(int i = 1 ;i < tam ; i++){ 
        soma+=x[i]*x[i]; // soma + x[i]²
    }
return sqrt(soma); //retorna a raiz do total
}

int main(void){
    int x[] ={2,3,4,5,6};
    int tam = sizeof(x)/sizeof(x[0]); 
    double teste = Norma(x,tam);
    printf("Teste %lf",teste); //%lf é pra imprimir um double
    return 0;
}