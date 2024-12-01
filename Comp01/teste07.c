#include "stdio.h"
#include "math.h"

int main(void){
    int a1 = 1000*1 +9000;
    int a2 = 0;
    int a3 = 0;
    int i = 1;
    do
    {
        a2=0;
        a1 = 1000*i +9000;
        a2 = pow(i,2) + 15*i;
    } while (a2<a1);
    printf("para chegar em a1 o a2 precisou de n = %i",i);
    i=1;
    do
    {
        a3 = 0;
        a1 = 1000*i +9000;
        a3 = pow(10,i) + 100*i;
    } while (a3<a1);
    printf("para chegar em a1 o a3 precisou de n = %i",i);
    
    return 0;
}