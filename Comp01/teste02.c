#include "stdio.h"
#include "stdbool.h"

bool exemplo02(int v[])
{
    int tam = sizeof(v) / sizeof(v[0]);
    for (int i = 0; i < tam; i++) // O(N)
    {
        for (int j = 0; j < tam; j++) //O(N)
        {
            if (i != j && v[i] == v[j])
            {
                return true;
            }
        }
    }
    return false;
}
//complexidade O(N)*O(N) = O(N²)