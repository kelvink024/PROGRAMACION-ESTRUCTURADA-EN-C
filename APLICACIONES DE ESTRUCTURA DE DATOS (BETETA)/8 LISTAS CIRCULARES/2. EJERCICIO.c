#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Paciente {
    char nombre[50];
    int edad;
    char sexo;
    char domicilio[100];
    char telefono[15];
    int seguro;
    struct Paciente *siguiente;
} Paciente;

Paciente *crearPaciente();
void error();
void insertarPaciente(Paciente **lista, Paciente *nuevo);
void listarNombres(Paciente *lista);
void calcularPorcentajes(Paciente *lista);
void listarDatosPaciente(Paciente *lista, char nombre[]);
void liberarLista(Paciente **lista);
void menu();

Paciente *crearPaciente() {
    Paciente *nuevo = (Paciente *)malloc(sizeof(Paciente));
    if (nuevo == NULL) {
        error();
        exit(-1);
    }

    printf("\t DATOS DEL PACIENTE\n");
    
    printf("nombre: ");
    scanf(" %49[^\n]", nuevo->nombre);
    
    printf("edad: ");
    scanf("%d", &nuevo->edad);
    
    printf("sexo (M/F): ");
    scanf(" %c", &nuevo->sexo);
    
    printf("domicilio: ");
    scanf(" %99[^\n]", nuevo->domicilio);
    
    printf("telefono: ");
    scanf(" %14[^\n]", nuevo->telefono);
    
    printf("Tiene seguro medico: (1: Si, 0: No): ");
    scanf("%d", &nuevo->seguro);
    
    nuevo->siguiente = nuevo;

    return nuevo;
}

void error() {
    printf("Error al asignar memoria\n");
}

void insertarPaciente(Paciente **lista, Paciente *nuevo) {
    if (*lista == NULL) {
        *lista = nuevo;
    } else {
        Paciente *temp = *lista;
        while (temp->siguiente != *lista) {
            temp = temp->siguiente;
        }
        
        temp->siguiente = nuevo;
        nuevo->siguiente = *lista;
    }
}

void listarNombres(Paciente *lista) {
    if (lista == NULL) {
        printf("Ups, la lista esta vacia...\n");
        return;
    }

    int contador = 0;
    Paciente *temp = lista;

    do {
        printf("%d: %s\n", contador + 1, temp->nombre);
        temp = temp->siguiente;
        contador++;
    } while (temp != lista);
}

void calcularPorcentajes(Paciente *lista) {
    if (lista == NULL) {
        return;
    }
    
    int total = 0, ninios = 0, jovenes = 0, adultos = 0, hombres = 0, mujeres = 0, conSeguro = 0;
    float r_ninios = 0, r_jovenes = 0, r_adultos = 0, r_hombres = 0, r_mujeres = 0, con_seguro = 0;
    
    Paciente *temp = lista;
    do {
        total++;
        if (temp->edad <= 13) {
            ninios++;    
        } else if (temp->edad <= 30) {
            jovenes++;    
        } else {
            adultos++;    
        }
        
        if (temp->sexo == 'M' || temp->sexo == 'm') {
            hombres++;  
        } else if(temp->sexo == 'F' || temp->sexo == 'f') {
            mujeres++;
        } else {
            printf("sexo invalido para el paciente %s\n", temp->nombre);
        }
        
        if (temp->seguro) {
            conSeguro++;    
        }
        temp = temp->siguiente;
    } while (temp != lista);
    
    r_ninios = ((ninios * 100.0) / total);
    r_jovenes = ((jovenes * 100.0) / total);
    r_adultos = ((adultos * 100.0) / total);
    r_hombres = ((hombres * 100.0) / total);
    r_mujeres = ((mujeres * 100.0) / total);
    con_seguro = ((conSeguro * 100.0) / total);

    printf("Ninios: %.2f%%\n", r_ninios);
    printf("Jovenes: %.2f%%\n", r_jovenes);
    printf("Adultos: %.2f%%\n", r_adultos);
    printf("Hombres: %.2f%%\n", r_hombres);
    printf("Mujeres: %.2f%%\n", r_mujeres);
    printf("Seguro Medico: %.2f%%\n", con_seguro);
}

void listarDatosPaciente(Paciente *lista, char nombre[]) {
    if (lista == NULL) {
        return;
    }
    
    Paciente *temp = lista;
    
    do {
        if (strcmp(temp->nombre, nombre) == 0) {
            printf("Nombre: %s\n", temp->nombre);
            printf("Edad: %d\n", temp->edad);
            printf("Sexo: %c\n", temp->sexo);
            printf("Domicilio: %s\n", temp->domicilio);
            printf("Telefono: %s\n", temp->telefono);
            printf("Seguro Medico: %s\n", temp->seguro ? "TIENE SEGURO" : "NO TIENE SEGURO");
            return;
        }
        
        temp = temp->siguiente;
    } while (temp != lista);
    
    printf("el paciente no fue encontrado, verifica bien el nombre...\n");
}

void liberarLista(Paciente **lista) {
    if (*lista == NULL) {
        return;
    }

    Paciente *temp = *lista;
    Paciente *siguiente;

    do {
        siguiente = temp->siguiente;
        free(temp);
        temp = siguiente;
    } while (temp != *lista);
    
    *lista = NULL;
}

void menu() {
	
    printf("\n--- Menu de opciones ---\n");
    printf("1. Insertar paciente\n");
    printf("2. Listar nombres de pacientes\n");
    printf("3. Calcular porcentajes\n");
    printf("4. Buscar datos de un paciente\n");
    printf("5. Salir\n");
    printf("Seleccione una opcion: ");
    
}

int main() {
    Paciente *lista = NULL;
    int opcion;

    do {
        menu();
        scanf("%d", &opcion);
        system("pause");
        system("cls");

        switch(opcion) {
            case 1:
            	
                {
                	Paciente *nuevoPaciente = crearPaciente();
                	insertarPaciente(&lista, nuevoPaciente);
                	printf("\nPaciente insertado correctamente.\n");
                	system("pause");
                	system("cls");
                	break;
				}   
            case 2:
            	
                printf("\nNombres de todos los pacientes hospitalizados:\n\n");
                listarNombres(lista);
                system("pause");
                system("cls");
                break;
            case 3:
            	
                printf("\nPorcentajes de pacientes hospitalizados por categorias:\n");
                calcularPorcentajes(lista);
                system("pause");
                system("cls");
                break;
            case 4:
            	
                printf("Ingrese el nombre del paciente a buscar: ");
                char nombre[50];
                scanf(" %49[^\n]", nombre);
                listarDatosPaciente(lista, nombre);
                system("pause");
                system("cls");
                break;
            case 5:
            	
                printf("Saliendo del programa.\n");
                liberarLista(&lista);
                break;
            default:
                printf("Opción invalida. Intente nuevamente.\n");
        }
    } while (opcion != 5);

    return 0;
}