#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define TAM_LISTA 5

void leer_datos(int *a);
int busqueda_secuencial(int *b, int buscar);
void imprimir_fila(int *b, int inf, int mitad, int sup);

/*************LEER DATOS **************/

void leer_datos(int a[]){
    int i;
    
    printf("\n ingresaremos los 5 datos \n");
    for(i=0; i<TAM_LISTA; i++){
        printf(" dato[%d]: ", i);
        scanf("%d", (a+i));
    }
    system("cls");
}

/************BUSQUEDA BINARIA***********/
int busqueda_secuencial(int *a, int valor){
    int i;

    for(i=0; i<TAM_LISTA; i++){
        if(*(a+i) == valor){
            return i;
        }
    }
    return (-1);
}

/************ IMPRIMIR FILA ***********/
void imprimir_fila(int *b, int inf, int mitad, int sup){
	int i;
	
    printf("\n rango del arreglo: [");
    
    for (i = inf; i <= sup; i++){
    	
        if (i == mitad){
            printf("[%d]:%d, ",i, *(b + i));
        } else{
            printf("[%d]:%d, ",i,  *(b + i));
        }
    }
    
    printf("]\n");
}

int main(){
    int i = 0;
    int a[TAM_LISTA];
    int valor, resultado;

    system("cls");
    leer_datos(a);

    printf("valor a buscar: ");
    scanf("%d", &valor);

    resultado = busqueda_secuencial(a, valor);
    if(resultado != -1){
        printf("\n el numero %d ha sido encontrado en la posicion [%d] del arreglo!\n", valor, resultado);
    }else{
        printf("\n %d no encontrado\n");
        exit(-1);
    }
    
    printf("\n verificamos si el numero se encuentra en esta lista\n");
	imprimir_fila(a, 0, resultado, TAM_LISTA - 1);
	
    return 0;
}