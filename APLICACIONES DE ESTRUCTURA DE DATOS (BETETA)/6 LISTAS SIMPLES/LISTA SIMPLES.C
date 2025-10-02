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

void registrarPaciente() {
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    if(nuevo == NULL){
    	printf("error al asignar memoria \n");
    	exit(-1);
	}
    printf("codigo: ");
    scanf("%d", &nuevo->codigo);
    printf("primer nombre: ");
    scanf("%s", nuevo->nombres);
    printf("primer apellido: ");
    scanf("%s", nuevo->apellidos);
    printf("direccion: ");
    scanf("%s", nuevo->direccion);
    printf("telefono: ");
    scanf("%ld", &nuevo->telefono);
    printf("\n");
    nuevo->sgte = NULL;
    if(inicio == NULL) {
        inicio = nuevo;
    } else {
        Nodo *actual = inicio;
        while(actual->sgte != NULL) {
            actual = actual->sgte;
        }
        actual->sgte = nuevo;
    }
    printf("el paciente ah sido registrado exitosamente\n\n");
    system("pause");
    system ("cls");
}

void eliminarPaciente(int codigo) {
    Nodo *actual = inicio, *anterior = NULL;
    
    while(actual != NULL && actual->codigo != codigo) {
        anterior = actual;
        actual = actual->sgte;
    }
    if(actual == NULL) {
        printf("el paciente con el codigo [ %d ] no fue encontrado, verifica el codigo si esta bien escrito\n", codigo);
        system("pause");
        system("cls");
        
        return;
    }
    if(anterior == NULL) {
        inicio = actual->sgte;
    } else {
        anterior->sgte = actual->sgte;
    }
    free(actual);
    printf("el paciente con el codigo de identificacion [ %d ] fue eliminado con exito\n", codigo);
    system("pause");
    system("cls");
}

void actualizarPaciente(int codigo) {
    Nodo *actual = inicio;
    while(actual != NULL && actual->codigo != codigo) {
        actual = actual->sgte;
    }
    if(actual == NULL) {
        printf("Paciente con el codigo de identificacion [ %d ] no encontrado, verifica si esta bien escrito\n", codigo);
        system("pause");
    	system("cls");
        return;
    }
    
    printf("\nACTUALIZAR DATOS DEL PACIENTE\n");
    printf("nuevo nombre: ");
    scanf("%s", actual->nombres);
    printf("nuevos apellidos: ");
    scanf("%s", actual->apellidos);
    printf("nueva direccion: ");
    scanf("%s", actual->direccion);
    printf("nuevo numero de telefono: ");
    scanf("%ld", &actual->telefono);
    printf("\n");
    
    printf("el paciente con codigo de identificacion [ %d ], ah sido guardado exitosamente\n", codigo);
    system("pause");
	system("cls");
}

void mostrarPaciente(int codigo) {
    Nodo *actual = inicio;
    while(actual != NULL && actual->codigo != codigo) {
        actual = actual->sgte;
    }
    if(actual == NULL) {
        printf("no existe ningun paciente con el codigo [ %d ], ingresa un codigo que si exista dentro de la lista\n", codigo);
        system("pause");
    	system("cls");
        return;
    }
    printf("\n");
    printf("\n-------------------------\n");
    printf("codigo: %d\n", actual->codigo);
    printf("nombre: %s\n", actual->nombres);
    printf("apellido: %s\n", actual->apellidos);
    printf("direccion: %s\n", actual->direccion);
    printf("telefono: %ld\n", actual->telefono);
    printf("\n-------------------------\n");
    
    system("pause");
    system("cls");
}

void mostrarListado() {
    Nodo *actual = inicio;
    if(actual == NULL) {
        printf("lo sentimos, no hay pacientes registrado\n");
        system("pause");
    	system("cls");
        return;
    }
    while(actual != NULL) {
        printf("codigo: %d\n", actual->codigo);
        printf("nombre: %s\n", actual->nombres);
        printf("apellido: %s\n", actual->apellidos);
        printf("direccion: %s\n", actual->direccion);
        printf("telefono: %ld\n", actual->telefono);
        printf("\n------------------------------------\n");
        actual = actual->sgte;
    }
}

int main() {
    int opcion, codigo;
    
    do {
        printf("\n--------MENU--------\n");
        printf("1. registrar paciente\n");
        printf("2. eliminar datos del paciente\n");
        printf("3. actualizar datos del paciente\n");
        printf("4. mostrar datos del paciente\n");
        printf("5. motrar listado de todos los pacientes\n");
        printf("6. salir\n");
        printf("\n");
        printf("seleccione una opcion: ");
        scanf("%d", &opcion);
        
        system("pause");
        system ("cls");

        switch(opcion) {
            case 1:
            	printf ("\nREGISTRO DE PACIENTES\n");
                registrarPaciente();
                break;
            case 2:
            	printf("\nELIMINAR DATOS DE UN PACIENTE\n");
                printf("ingrese el codigo de identificacion del paciente: ");
                scanf("%d", &codigo);
                eliminarPaciente(codigo);
                break;
            case 3:
                printf("ingrese el codigo del paciente a actualizar: ");
                scanf("%d", &codigo);
                actualizarPaciente(codigo);
                break;
            case 4:
            	printf("\nMOSTRAR DATOS DE UN PACIENTE\n");
                printf("ingrese el codigo del paciente a mostrar: ");
                scanf("%d", &codigo);
                mostrarPaciente(codigo);
                break;
            case 5:
            	printf("\nLISTADO GENERAL DE TODOS LOS PACIENTES \n\n");
                mostrarListado();
                system("pause");
                system("cls");
                break;
            case 6:
                printf("Saliendo...\n");
                break;
            default:
                printf("opcion invalida, vuelve a intentarlo\n");
        }
    } while(opcion != 6);
    
    
    Nodo *actual = inicio;
    while(actual != NULL) {
        Nodo *temp = actual;
        actual = actual->sgte;
        free(temp);
    }
    return 0;
}