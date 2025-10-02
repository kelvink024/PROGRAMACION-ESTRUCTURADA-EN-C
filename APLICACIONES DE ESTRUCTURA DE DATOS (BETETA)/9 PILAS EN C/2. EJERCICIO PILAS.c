#include <stdio.h>
#include <stdlib.h>

typedef struct datos {
    int dato;
    struct datos *siguiente;
} Pila;


// prototipos de funciones
void push(Pila **top, int valor);
void error();
int pop(Pila **top);
void mensaje();
void liberarPila(Pila **top);
void mostrarPila(Pila *top);
void fibonacci(Pila **top, int n);


void push(Pila **top, int valor) {
	
    Pila *nuevo = (Pila *)malloc(sizeof(Pila));
    if (nuevo == NULL) {
    	
        error();
        exit(1);
        
    }
    nuevo->dato = valor;
    nuevo->siguiente = *top;
    *top = nuevo;
}

void error(){
	
	printf("error al asignar memoria\n");
	
}


int pop(Pila **top) {
	
	int valor; 
	
    if (*top == NULL) {
    	
        mensaje();
        return -1;
        
    }
    
    Pila *temp = *top;
	valor = temp->dato;
    *top = temp->siguiente;
    free(temp);
    
    return valor;
}

void mensaje(){
	
	printf("la lista esta vacia\n");
	
}

void liberarPila(Pila **top) {
	
    while (*top != NULL) {
        pop(top);
    }
}

void mostrarPila(Pila *top) {
    Pila *temp = top;
    int elementos[100];
    int contador = 0, i ;
    
    while (temp != NULL) {
    	
        elementos[contador] = temp->dato;
        temp = temp->siguiente;
        contador++;
        
    }

    printf("\tla serie de fibonacci es: \n\n");
    for (i = contador - 1; i >= 0; i--) {
    	
        printf("%d ", elementos[i]);
        
    }
    printf("\n");
}

void fibonacci(Pila **top, int n) {
    int a = 0, b = 1, siguiente, i;
    
    push(top, a);
    if (n > 1) {
        push(top, b);
    }
    
    for (i = 3; i <= n; i++) {
        siguiente = a + b;
        push(top, siguiente);
        a = b;
        b = siguiente;
    }
}

int main() {
    Pila *top = NULL;
    int n;

    printf("ingrese el numero en terminos de la serie =  ");
    scanf("%d", &n);
    printf("\n");
    
    if (n <= 0) {
    	
        printf("por favor ingresa un numero que sea mayor que 0\n");
        
        return 1;
    }

    fibonacci(&top, n);
    mostrarPila(top);
    liberarPila(&top);

    return 0;
}
