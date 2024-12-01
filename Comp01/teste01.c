#include "stdio.h"
#include "stdbool.h"

bool Exemplo(int v[], int x)
{
    int tam = sizeof(v)/sizeof(v[0]); //constante, logo, complexidade: O(n1);
    for (int i = 0; i < tam; i++) //unica repetição logo, complexidade: como vai de um valor inicial até um indertemindado, logo, complexidade: O(n);
    {
        if (v[i] == x)  
        {
            return true; 
        }
        
    }
    return false;
}
//complexidade final O(N);