#include <stdio.h>
#include <stdlib.h>

typedef struct pila Pila;
struct pila {
	
    int digito;
    Pila *siguiente;
    
};
typedef Pila *PPila;

void push(PPila *pila, int digito);
void error();
int pop(PPila *pila);
void mostrarPila(PPila pila);
PPila copiarPila(PPila pila);

void push(PPila *pila, int digito) {
    PPila nuevoNodo = (PPila)malloc(sizeof(Pila));
    if (nuevoNodo == NULL) {
       error();
        exit(-1);
    }
    nuevoNodo->digito = digito;
    nuevoNodo->siguiente = *pila;
    *pila = nuevoNodo;
}

void error(){
	
	printf("error al asignar memoria\n");
	
}

int pop(PPila *pila) {
    if (*pila == NULL) {
        printf("error pila vacia\n");
        return -1;
    }

    int digito = (*pila)->digito;
    PPila auxiliar = *pila;
    *pila = (*pila)->siguiente;
    free(auxiliar);

    return digito;
}

PPila copiarPila(PPila pila) {
    PPila nuevaPila = NULL;
    PPila temp = NULL;

    while (pila != NULL) {
        push(&temp, pila->digito);
        pila = pila->siguiente;
    }

    while (temp != NULL) {
        push(&nuevaPila, pop(&temp));
    }

    return nuevaPila;
}

void mostrarPila(PPila pila) {
    PPila copia = copiarPila(pila);
    while (copia != NULL) {
        printf("%d", pop(&copia));
    }
    printf("\n");
}

int main() {
    int numero;
    printf("Introduzca un numero decimal: ");
    scanf("%d", &numero);

    PPila pila = NULL;

    while (numero > 0) {
        push(&pila, numero % 2);
        numero /= 2;
    }

    printf("El numero en binario es: ");
    mostrarPila(pila);

    return 0;
}
