#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo {
    int codigo;
    char nombres[30];
    char apellidos[30];
    char direccion[60];
    long telefono;
    struct nodo *sgte;
};

typedef struct nodo Nodo;
Nodo *inicio = NULL;

void registrarPaciente();
void eliminarPaciente(int codigo);
void actualizarPaciente(int codigo);
void mostrarPaciente(int codigo);
void mostrarListado();

int main() {
    int opcion, codigo;
    
    do {
        printf("\nMenú de opciones\n");
        printf("1. Registrar paciente\n");
        printf("2. Eliminar datos de paciente\n");
        printf("3. Actualizar datos de paciente\n");
        printf("4. Mostrar datos de paciente\n");
        printf("5. Mostrar listado de pacientes\n");
        printf("6. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                registrarPaciente();
                break;
            case 2:
                printf("Ingrese el código del paciente a eliminar: ");
                scanf("%d", &codigo);
                eliminarPaciente(codigo);
                break;
            case 3:
                printf("Ingrese el código del paciente a actualizar: ");
                scanf("%d", &codigo);
                actualizarPaciente(codigo);
                break;
            case 4:
                printf("Ingrese el código del paciente a mostrar: ");
                scanf("%d", &codigo);
                mostrarPaciente(codigo);
                break;
            case 5:
                mostrarListado();
                break;
            case 6:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida\n");
        }
    } while(opcion != 6);

    // Liberar la lista antes de salir
    Nodo *actual = inicio;
    while(actual != NULL) {
        Nodo *temp = actual;
        actual = actual->sgte;
        free(temp);
    }
    return 0;
}

void registrarPaciente() {
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    printf("Ingrese el código: ");
    scanf("%d", &nuevo->codigo);
    printf("Ingrese los nombres: ");
    scanf("%s", nuevo->nombres);
    printf("Ingrese los apellidos: ");
    scanf("%s", nuevo->apellidos);
    printf("Ingrese la dirección: ");
    scanf("%s", nuevo->direccion);
    printf("Ingrese el teléfono: ");
    scanf("%ld", &nuevo->telefono);
    nuevo->sgte = NULL;  // El nuevo nodo apunta a NULL
    if(inicio == NULL) {
        inicio = nuevo;
    } else {
        Nodo *actual = inicio;
        while(actual->sgte != NULL) {
            actual = actual->sgte;
        }
        actual->sgte = nuevo;
    }
    printf("Paciente registrado exitosamente\n");
}

void eliminarPaciente(int codigo) {
    Nodo *actual = inicio, *anterior = NULL;
    while(actual != NULL && actual->codigo != codigo) {
        anterior = actual;
        actual = actual->sgte;
    }
    if(actual == NULL) {
        printf("Paciente no encontrado\n");
        return;
    }
    if(anterior == NULL) {
        inicio = actual->sgte;
    } else {
        anterior->sgte = actual->sgte;
    }
    free(actual);
    printf("Paciente eliminado exitosamente\n");
}

void actualizarPaciente(int codigo) {
    Nodo *actual = inicio;
    while(actual != NULL && actual->codigo != codigo) {
        actual = actual->sgte;
    }
    if(actual == NULL) {
        printf("Paciente no encontrado\n");
        return;
    }
    printf("Ingrese los nuevos nombres: ");
    scanf("%s", actual->nombres);
    printf("Ingrese los nuevos apellidos: ");
    scanf("%s", actual->apellidos);
    printf("Ingrese la nueva dirección: ");
    scanf("%s", actual->direccion);
    printf("Ingrese el nuevo teléfono: ");
    scanf("%ld", &actual->telefono);
    printf("Paciente actualizado exitosamente\n");
}

void mostrarPaciente(int codigo) {
    Nodo *actual = inicio;
    while(actual != NULL && actual->codigo != codigo) {
        actual = actual->sgte;
    }
    if(actual == NULL) {
        printf("Paciente no encontrado\n");
        return;
    }
    printf("Código: %d\n", actual->codigo);
    printf("Nombres: %s\n", actual->nombres);
    printf("Apellidos: %s\n", actual->apellidos);
    printf("Dirección: %s\n", actual->direccion);
    printf("Teléfono: %ld\n", actual->telefono);
}

void mostrarListado() {
    Nodo *actual = inicio;
    if(actual == NULL) {
        printf("No hay pacientes registrados\n");
        return;
    }
    while(actual != NULL) {
        printf("Código: %d\n", actual->codigo);
        printf("Nombres: %s\n", actual->nombres);
        printf("Apellidos: %s\n", actual->apellidos);
        printf("Dirección: %s\n", actual->direccion);
        printf("Teléfono: %ld\n", actual->telefono);
        actual = actual->sgte;
    }
}
