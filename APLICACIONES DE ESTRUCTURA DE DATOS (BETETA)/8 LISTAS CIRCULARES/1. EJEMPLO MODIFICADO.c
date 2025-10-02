#include <stdlib.h>
#include <stdio.h>

typedef struct _nodo {
    int valor;
    struct _nodo *siguiente;
} tipoNodo;

typedef tipoNodo *pNodo;
typedef tipoNodo *Lista;

void Insertar(Lista *l, int v);
void error();
void Borrar(Lista *l, int v);
void BorrarLista(Lista *);
void MostrarLista(Lista l);
void Menu();

void Insertar(Lista *lista, int v) {
    pNodo nodo;
    nodo = (pNodo)malloc(sizeof(tipoNodo));
	if(nodo == NULL)
	{
    	error();
    	exit(-1);
	}
    nodo->valor = v;

    if(*lista == NULL) {
        *lista = nodo;
        nodo->siguiente = nodo;
    } else {
        nodo->siguiente = (*lista)->siguiente;
        (*lista)->siguiente = nodo;
    }
}

void error(){
	printf("error al asignar memoria\n");
}

void Borrar(Lista *lista, int v) {
    pNodo nodo;
    nodo = *lista;

    do {
        if((*lista)->siguiente->valor != v)
            *lista = (*lista)->siguiente;
    } while((*lista)->siguiente->valor != v && *lista != nodo);

    if((*lista)->siguiente->valor == v) {
        if(*lista == (*lista)->siguiente) {
            free(*lista);
            *lista = NULL;
        } else {
            nodo = (*lista)->siguiente;
            (*lista)->siguiente = nodo->siguiente;
            free(nodo);
        }
    }
}

void BorrarLista(Lista *lista) {
    pNodo nodo;

    while((*lista)->siguiente != *lista) {
        nodo = (*lista)->siguiente;
        (*lista)->siguiente = nodo->siguiente;
        free(nodo);
    }

    free(*lista);
    *lista = NULL;
}

void MostrarLista(Lista lista) {
    pNodo nodo = lista;
    if (lista == NULL) {
        printf("\n lo sentimos, la lista esta vacia");
        printf(", puedes agregar datos desde la primera opcion\n\n");
        return;
    }
    printf("\n>Mostrar lista:\n");
    do {
        printf("%d -> ", nodo->valor);
        nodo = nodo->siguiente;
    } while(nodo != lista);
    printf("\n");
}

void Menu() {
    printf("\n--- MENU OPCIONE ---\n");
    printf("1. Insertar \n");
    printf("2. Borrar \n");
    printf("3. Mostrar lista \n");
    printf("4. Borrar lista \n");
    printf("5. Salir\n");
}


int main() {
    Lista lista = NULL;
    int opcion, valor;

    do {
        Menu();
        
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        system("pause");
        system("cls");

        switch(opcion) {
            case 1:
                printf("\n opcion 1 'CREAR LISTA INGRESANDO VALORES'\n");
                printf("valor: ");
                scanf("%d", &valor);
                Insertar(&lista, valor);
                system("pause");
        		system("cls");
                break;
            case 2:
            	printf("opcion 2 'BORRAR UN VALOR DE LA LISTA'\n");
                printf("Ingrese un valor a borrar: ");
                scanf("%d", &valor);
                Borrar(&lista, valor);
                system("pause");
        		system("cls");
                break;
            case 3:
            	printf("opcion 3 'MOSTRAR LISTAS'\n");
                MostrarLista(lista);
                system("pause");
        		system("cls");
                break;
            case 4:
            	printf("borrando todos los datos...\n");
            	printf("cerrando programa... \n");
                BorrarLista(&lista);
                exit(-1);
                break;
            case 5:
                printf("Saliendo...\n");
                break;
            default:
                printf("upps, opcion invalida... ingresa un numero valido que este dentro del menu de opciones \n\n");
                system("pause");
                system("cls");
        }
    } while(opcion != 5);

    return 0;
}