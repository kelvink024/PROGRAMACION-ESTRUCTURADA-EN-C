#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo {
    int codigo;
    char nombre[30];
    char apellido[30];
    char correo[50];
    float nota;
    struct nodo *prev;
    struct nodo *next;
};

typedef struct nodo Nodo;
Nodo *inicio = NULL, *fin = NULL;

Nodo* crearNodo(int codigo, char nombre[], char apellido[], char correo[], float nota);
void error();
void liberarNodo(Nodo* nodo);
void agregarEstudiante();
void buscarEstudiante(int codigo);
void eliminarEstudiante(int codigo);
void totalAprobados();
void totalReprobados();
void mostrarEstudiantes();
void liberarLista();

int main() {
    int opcion, codigo;

    do {
        printf("\n--------MENU--------\n");
        printf("1. agregar un estudiante\n");
        printf("2. buscar estudiante mediante el codigo\n");
        printf("3. eliminar estudiante\n");
        printf("4. total de estudiantes aprobados\n");
        printf("5. total de estudiantes reprobados\n");
        printf("6. Mostrar todos los estudiantes\n");
        printf("7. Salir\n");
        printf("\n");
        printf("seleccione una opcion: ");
        scanf("%d", &opcion);

        system("pause");
        system ("cls");

        switch(opcion) {
            case 1:
                printf("\nREGISTRO DEL ESTUDIANTE\n");
                agregarEstudiante();
                break;
            case 2:
                printf("\nBUSQUEDA DE ESTUDIANTE\n");
                printf("ingrese el codigo del estudiante a buscar: ");
                scanf("%d", &codigo);
                system("pause");
                system("cls");
                buscarEstudiante(codigo);
                break;
            case 3:
                printf("\nELIMINACION DE ESTUDIANTE MEDIANTE CODIGO ID\n");
                printf("ingrese el codigo del estudiante a eliminar: ");
                scanf("%d", &codigo);
                system("pause");
        		system("cls");
                eliminarEstudiante(codigo);
                break;
            case 4:
                totalAprobados();
                break;
            case 5:
                totalReprobados();
                break;
            case 6:
                mostrarEstudiantes();
                system("pause");
                system("cls");
                break;
            case 7:
                liberarLista();
                printf("Saliendo...\n");
                break;
            default:
                printf("opcion no valida, intentalo de nuevo\n");
        }
    } while(opcion != 7);

    return 0;
}

Nodo* crearNodo(int codigo, char nombre[], char apellido[], char correo[], float nota) {
	
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    if(nuevo == NULL){
    	
    	error();
    	return 0;
	}
    nuevo->codigo = codigo;
    strcpy(nuevo->nombre, nombre);
    strcpy(nuevo->apellido, apellido);
    strcpy(nuevo->correo, correo);
    nuevo->nota = nota;
    nuevo->prev = nuevo->next = NULL;
    return nuevo;
}

void error(){
	printf("error al asignar memoria !!");
}

void liberarNodo(Nodo* nodo) {
    free(nodo);
}

void agregarEstudiante() {
    int codigo;
    char nombre[30], apellido[30], correo[50];
    float nota;
    printf("ID del estudiante: ");
    scanf("%d", &codigo);
    printf("primer nombre: ");
    scanf("%s", nombre);
    printf("primer apellido: ");
    scanf("%s", apellido);
    printf("correo electronico: ");
    scanf("%s", correo);
    printf("ingresa la nota del estudiante: ");
    scanf("%f", &nota);

    Nodo *nuevo = crearNodo(codigo, nombre, apellido, correo, nota);

    if(nuevo->nota >= 60) {
        if(inicio == NULL) {
            inicio = fin = nuevo;
        } else {
            nuevo->next = inicio;
            inicio->prev = nuevo;
            inicio = nuevo;
        }
    } else {
        if(inicio == NULL) {
            inicio = fin = nuevo;
        } else {
            fin->next = nuevo;
            nuevo->prev = fin;
            fin = nuevo;
        }
    }
    printf("\n");
    printf("Estudiante agregado exitosamente\n");
    system("pause");
    system("cls");
}

void buscarEstudiante(int codigo) {
    Nodo *actual = inicio;
    while(actual != NULL && actual->codigo != codigo) {
        actual = actual->next;
    }
    if(actual == NULL) {
        printf("lo lamentamos, el codigo de identificacion [ %d ], no esta asignado a ningun estudiante\n", codigo);
        printf("verifica si esta bien escrito el codigo del estudiante\n");
        system("pause");
        system("cls");
    } else {
        printf("\n-------------------------\n");
        printf("codigo [ID]: %d\n", actual->codigo);
        printf("Nombre: %s\n", actual->nombre);
        printf("Apellido: %s\n", actual->apellido);
        printf("Correo: %s\n", actual->correo);
        printf("Nota: %.2f\n", actual->nota);
        printf("-------------------------\n");
        system("pause");
        system("cls");

    }
}

void eliminarEstudiante(int codigo) {
    Nodo *actual = inicio;
    while(actual != NULL && actual->codigo != codigo) {
        actual = actual->next;
    }
    if(actual == NULL) {
    	printf("upss....");
        printf(" el codigo de identificacion [ %d ] no esta asignado a ningun estudiante\n", codigo);
        printf("verifica si el codigo esta asignado a un estudiante\n");
        printf("\n");
        system("pause"); 
        system("cls");
        return;
    }
    if(actual->prev != NULL) {
        actual->prev->next = actual->next;
    } else {
        inicio = actual->next;
    }
    if(actual->next != NULL) {
        actual->next->prev = actual->prev;
    } else {
        fin = actual->prev;
    }
    liberarNodo(actual);
    printf("el estudiante con el codigo de identificacion [ %d ] fue eliminado con exito\n", codigo);
    system("pause");
    system("cls");
}

void totalAprobados() {
    Nodo *actual = inicio;
    int contador = 0;
    while(actual != NULL) {
        if(actual->nota >= 60) {
            contador++;
        }
        actual = actual->next;
    }
    printf("Total de estudiantes aprobados: %d\n", contador);
    system("pause");
    system("cls");
}

void totalReprobados() {
    Nodo *actual = inicio;
    int contador_r = 0;
    while(actual != NULL) {
        if(actual->nota < 60) {
            contador_r++;
        }
        actual = actual->next;
    }
    printf("Total de estudiantes reprobados: %d\n", contador_r);
    system("pause");
    system("cls");
}

void mostrarEstudiantes() {
    Nodo *actual = inicio;
    if(actual == NULL) {

        printf("upss\n");
        printf("lo sentimos, pero no hay una lista de estudiantes\n");
        printf("puedes agregar desde la primera opcion\n");
        system("pause");
        system("cls");
        return;
    }

    printf("\nLISTADO GENERAL DE TODOS LOS ESTUDIANTES\n\n");
    while(actual != NULL) {
        printf("codigo [ID]: %d\n", actual->codigo);
        printf("nombre: %s\n", actual->nombre);
        printf("apellido: %s\n", actual->apellido);
        printf("Correo: %s\n", actual->correo);
        printf("Nota: %.2f\n", actual->nota);
        printf("-------------------------\n");
        actual = actual->next;
    }
}

void liberarLista() {
    Nodo *actual = inicio;
    while(actual != NULL) {
        Nodo *temp = actual;
        actual = actual->next;
        liberarNodo(temp);
    }
    inicio = fin = NULL;
}
