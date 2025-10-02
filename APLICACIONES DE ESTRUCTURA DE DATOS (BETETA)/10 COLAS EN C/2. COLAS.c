#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char customer[60];
    int qtty;
} orden;

typedef struct Node {
    orden dato;
    struct Node* siguiente;
} Node;

typedef struct {
    Node* primero;
    Node* cola;
} LinkedQueue;

void iniciar_cola(LinkedQueue* queue) {
    queue->primero = NULL;
    queue->cola = NULL;
}

int verificacion(LinkedQueue* queue) {
    return queue->primero == NULL;
}

void encolacion_pedido(LinkedQueue* queue, orden order) {
    Node* nuevo_nodo = (Node*)malloc(sizeof(Node));
    if(nuevo_nodo ==NULL){
    	printf("error al asignar memoria");
	}
    nuevo_nodo->dato = order;
    nuevo_nodo->siguiente = NULL;

    if (verificacion(queue)) {
        queue->primero = nuevo_nodo;
        queue->cola = nuevo_nodo;
    } else {
        queue->cola->siguiente = nuevo_nodo;
        queue->cola = nuevo_nodo;
    }
}

orden eliminacion_cola(LinkedQueue* queue) { 
    if (verificacion(queue)) {
        printf("Error: La cola esta vacia.\n");
        exit(EXIT_FAILURE);
    }

    Node* temp = queue->primero;
    orden data_delete = temp->dato;
    queue->primero = temp->siguiente;

    if (queue->primero == NULL) {
        queue->cola = NULL;
    }

    free(temp);
    return data_delete; 
}

void mostar_datos(LinkedQueue* queue) {
    if (verificacion(queue)) {
        printf("La cola esta vacia.\n");
        return;
    }

    Node* current = queue->primero;
    printf("Pedidos en la cola:\n");
    while (current != NULL) {
        printf("Cliente: %s, Cantidad: %d\n", current->dato.customer, current->dato.qtty);
        current = current->siguiente;
    }
}

int main() {
    LinkedQueue queue;
    iniciar_cola(&queue);

    orden order1 = {"Cliente A", 5};
    orden order2 = {"Cliente B", 10};
    orden order3 = {"Cliente C", 2};

    encolacion_pedido(&queue, order1);
    encolacion_pedido(&queue, order2);
    encolacion_pedido(&queue, order3);

    printf("Estado inicial de la cola:\n");
    mostar_datos(&queue);

    printf("\nProcesando pedido...\n");
    orden data_delete = eliminacion_cola(&queue);
    printf("Pedido procesado: Cliente: %s, Cantidad: %d\n", data_delete.customer, data_delete.qtty);

    printf("\nEstado de la cola despues de procesar un pedido:\n");
    mostar_datos(&queue);

    return 0;
}