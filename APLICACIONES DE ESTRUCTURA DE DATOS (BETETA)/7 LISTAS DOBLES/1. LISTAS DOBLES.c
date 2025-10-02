#include <stdio.h>
#include <stdlib.h>

// Definicion de la estructura del nodo
struct nodo {
    int data;
    struct nodo *anterior;
    struct nodo *siguiente;
};

typedef struct nodo Nodo;
Nodo *inicio = NULL;
Nodo *fin = NULL;

void nodo_nuevo(int data);
void mostrarLista();
void invertirLista();

int main() {

    nodo_nuevo(1);
    nodo_nuevo(2);
    nodo_nuevo(3);
	nodo_nuevo(4);
    nodo_nuevo(5);
    nodo_nuevo(6);
    nodo_nuevo(7);
	nodo_nuevo(8);
	nodo_nuevo(9);
    nodo_nuevo(0);

    printf("lista original:\n");
    mostrarLista();

    invertirLista();

    printf("\nlista invertida:\n");
    mostrarLista();

    return 0;
}

void nodo_nuevo(int data) {
    Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
    if(nuevo == NULL){
    	printf("error al asignar memoria\n");
    	exit(-1);
	}
    nuevo->data = data;
    nuevo->anterior = NULL;
    nuevo->siguiente = NULL;

    if (inicio == NULL) {
        inicio = fin = nuevo;
    } else {
        fin->siguiente = nuevo;
        nuevo->anterior = fin;
        fin = nuevo;
    }
}

void mostrarLista() {
    Nodo *actual = inicio;
    while (actual != NULL) {
        printf("%d ", actual->data);
        actual = actual->siguiente;
    }
    printf("\n");
}

void invertirLista() {
    Nodo *actual = inicio;
    Nodo *temp = NULL;

    while (actual != NULL) {
        temp = actual->anterior;
        actual->anterior = actual->siguiente;
        actual->siguiente = temp;
        actual = actual->anterior;
    }

    if (temp != NULL) {
        inicio = temp->anterior;
    }
}
