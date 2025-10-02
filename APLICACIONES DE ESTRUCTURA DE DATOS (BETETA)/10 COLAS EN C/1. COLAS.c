/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo_cola {
    char nombre[65];
    struct nodo_cola *siguiente;
};

void agregar_nodo(struct nodo_cola **nodo, char *nombre);
void error();
void imprimir_nodos(struct nodo_cola *nodo);
void sacar_nodo(struct nodo_cola **nodo);
void menu();
void liberar_memoria(struct nodo_cola **nodo);

void agregar_nodo(struct nodo_cola **nodo, char *nombre) {
    struct nodo_cola *nuevo = (struct nodo_cola *)malloc(sizeof(struct nodo_cola));
    if (nuevo == NULL) {
        error();
        exit(EXIT_FAILURE);
    }

    strcpy(nuevo->nombre, nombre);
    nuevo->siguiente = NULL;

    if (*nodo == NULL) {
        *nodo = nuevo;
    } else {
        struct nodo_cola *temp = *nodo;
        while (temp->siguiente != NULL) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
    }
}

void error() {
    printf("Error al asignar memoria al nodo...\n");
}

void imprimir_nodos(struct nodo_cola *nodo) {
    if (nodo == NULL) {
        printf("la cola esta vacia...\n");
        return;
    }
    while (nodo != NULL) {
        printf("Nombre: '%s'\n", nodo->nombre);
        nodo = nodo->siguiente;
    }
}

void sacar_nodo(struct nodo_cola **nodo) {
    if (*nodo == NULL) {
        printf("la cola está vacia, no hay elementos para sacar.\n");
        return;
    }

    struct nodo_cola *temp = *nodo;
    *nodo = (*nodo)->siguiente;
    printf("Nodo removido: '%s'\n", temp->nombre);
    free(temp);
}

void liberar_memoria(struct nodo_cola **nodo) {
    while (*nodo != NULL) {
        struct nodo_cola *temp = *nodo;
        *nodo = (*nodo)->siguiente;
        free(temp);
    }
}

void menu() {
    printf("\n--- Menu ---\n");
    printf("1. Mostrar la cola inicial\n");
    printf("2. Sacar el primer nodo y mostrar la cola\n");
    printf("3. Sacar otro nodo y mostrar la cola\n");
    printf("4. Salir\n");
    printf("Seleccione una opcion: ");
}

int main() {
    struct nodo_cola *cola = NULL;
    int opcion;

    agregar_nodo(&cola, "Kelvin");
    agregar_nodo(&cola, "Oniel");
    agregar_nodo(&cola, "Mayorga");
    agregar_nodo(&cola, "Melado");

    do {
        menu();
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                printf("\nCola inicial:\n");
                imprimir_nodos(cola);
                break;
            case 2:
                printf("\nSacando el primer nodo...\n");
                sacar_nodo(&cola);
                printf("\n");
                printf("Cola despues de sacar el primer nodo:\n");
                imprimir_nodos(cola);
                break;
            case 3:
                printf("\nSacando otro nodo...\n");
                sacar_nodo(&cola);
                printf("\n");
                printf("Cola despues de sacar otro nodo:\n");
                imprimir_nodos(cola);
                break;
            case 4:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion invalida, ingresa una opcion dentro del menu.\n");
        }
    } while (opcion != 4);

    liberar_memoria(&cola);
    return 0;
}*/




#include <stdio.h>

typedef struct {
    int pid;        // ID del proceso
    int llegada;    // Tiempo de llegada
    int rafaga;     // Duración
    int inicio;     // Tiempo de inicio
    int fin;        // Tiempo de finalización
    int espera;     // Tiempo de espera
    int retorno;    // Tiempo de retorno
} Proceso;

int main() {
    // Procesos definidos
    Proceso p[] = {
        {1, 0, 5, 0, 0, 0, 0},
        {2, 1, 3, 0, 0, 0, 0},
        {3, 2, 8, 0, 0, 0, 0},
        {4, 3, 6, 0, 0, 0, 0}
    };

    int n = sizeof(p) / sizeof(p[0]);

    // Ordenar por tiempo de llegada (FCFS)
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (p[i].llegada > p[j].llegada) {
                Proceso temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Calcular tiempos
    int tiempo_actual = 0;
    float total_espera = 0, total_retorno = 0;
    for (int i = 0; i < n; i++) {
        if (tiempo_actual < p[i].llegada)
            tiempo_actual = p[i].llegada;

        p[i].inicio = tiempo_actual;
        p[i].fin = p[i].inicio + p[i].rafaga;
        p[i].espera = p[i].inicio - p[i].llegada;
        p[i].retorno = p[i].fin - p[i].llegada;

        tiempo_actual = p[i].fin;

        total_espera += p[i].espera;
        total_retorno += p[i].retorno;
    }

    // Mostrar traza tipo Gantt
    printf("\nTRAZA GANTT (FCFS):\n");
    for (int i = 0; i < n; i++) {
        printf("| P%d \t", p[i].pid);
    }
    printf("|\n0");
    for (int i = 0; i < n; i++) {
        printf("\t%d", p[i].fin);
    }
    printf("\n");

    // Mostrar tabla de tiempos
    printf("\nTabla de procesos:\n");
    printf("PID\tLlegada\tRafaga\tInicio\tFin\tEspera\tRetorno\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].llegada, p[i].rafaga,
               p[i].inicio, p[i].fin, p[i].espera, p[i].retorno);
    }

    // Promedios
    printf("\nPromedio de espera: %.2f\n", total_espera / n);
    printf("Promedio de retorno: %.2f\n", total_retorno / n);

    return 0;
}


