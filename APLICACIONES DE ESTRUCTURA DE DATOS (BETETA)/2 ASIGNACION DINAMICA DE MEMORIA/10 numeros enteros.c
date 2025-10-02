#include <stdio.h>

int main(){
    int *numeros;
    int i, menor, mayor;

    for(i=0; i<10; i++)
    {
        printf("ingresa el numero %d: ", i+1);
        scanf("%d", &numeros[i]);
    }

   numeros = (int *)malloc(10 * sizeof(int));
    if (numeros == NULL) {
        printf("error al asignarle memoria \n");
        return 1;
    }
   
    menor = numeros[0];
    mayor = numeros[0];

    for(i=0; i<10; i++)
    {
        if(numeros[i] < menor)
        {
            menor = numeros[i];
        }
        if(numeros[i] > mayor)
        {
            mayor = numeros[i];
        }
    }
    printf("el numero menor es: %d\n", menor);
    printf("el numero mayor es: %d\n", mayor);

    free(numeros);
    return 0;
}