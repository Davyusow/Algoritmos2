#include "stdio.h"
#include "stdbool.h"

bool exemplo04(int v[], int w[]){
    int tamV = sizeof(v)/sizeof(v[0]);
    int tamW = sizeof(w)/sizeof(w[0]);
    for(int i = 0;i<tamV;i++){  //O(N)
        for(int j=0;j<tamW;j++){ //O(M)
            if(v[i] == v[j]){
                return true;
            }
        }
    }
    return false;
}
//complexidade: O(N)*O(M) 