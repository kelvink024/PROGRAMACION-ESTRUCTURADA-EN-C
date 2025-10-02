#include <stdio.h>
#include <stdlib.h>

struct nodo {
    int data;
    struct nodo *anterior;
    struct nodo *siguiente;
};

typedef struct nodo Nodo;
Nodo *inicio = NULL;
Nodo *fin = NULL;

void crear_nodo(int data);
void agregar_nodo();
int buscar_dato(int data);
void dato_obtenido(int valor, int resultado);

void crear_nodo(int data) {
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


void agregar_nodo() {
    int data, contador;
    char opcion;
    do {
        printf("Ingrese el valor para el nodo [%d]: ", contador + 1);
        scanf("%d", &data);
        crear_nodo(data);

        printf("desea agregar otro nodo s/n :  ");
        scanf(" %c", &opcion);
        
        contador++;
        
    } while(opcion != 'N' && opcion != 'n');
}

int buscar_dato(int data) {
    Nodo *actual = inicio;
    int contador = 0;

    while (actual != NULL) {
	
        if (actual->data == data) {
            contador++;
        }
        actual = actual->siguiente;
    }

    return contador;
}


void dato_obtenido(int valor, int resultado) {
    if (resultado > 0) {
        printf("El dato [%d] se encuentra %d! ves en la lista\n", valor, resultado);
    } else {
        printf("El dato [%d] no fue encontrado en la lista.\n", valor);
    }
}

int main() {
    int valor, resultado;
    
    agregar_nodo();

    printf("ingrese el valor que desee buscar en lista: ");
    scanf("%d", &valor);

    resultado = buscar_dato(valor);
    dato_obtenido(valor, resultado);

    return 0;
}