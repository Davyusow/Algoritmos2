#include "stdio.h"

int exemplo03(int v[]){
    int tam = sizeof(v)/sizeof(v[0]);
    int bla = 0;
    for(int i=0;i<tam;i++){ // O(N)
        for(int j=0;j<tam;j++){ //O(N)
            if(v[i]==v[j]){
                bla++;
            }
        }
    }
    //O(N)*O(N) = O(N²)
    int ble = 0;
    for(int i = 0;i<tam;i++){   // O(N)
        if(v[i]==10){
            ble*=2;
        }
    }
    //complexidade = O(N²)+O(N)
    int bli = 0;
    for(int i = 0;i<tam;i++){   // O(N)
        if(v[i]==5){
            bli+=5;
        }
    }
    return bla+ble+bli;
    //complexidade = O(N²)+O(N)+O(N) = O(N²)+2*O(N) --> 2 é constante
    //complexidade = O(N²)+O(N) --> O(N) é linear
    //complexidade = O(N²) 
}

