#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct empleados Empleados;
struct empleados {
    char nombre[64];
    float salario;
    Empleados *siguiente;
};

typedef Empleados *Pempleados;

typedef struct proyectos Proyectos;
struct proyectos {
    int numero;
    char nombre[64];
    Pempleados inicio;
    Proyectos *siguiente;
};

typedef Proyectos *Pproyectos;

void insertarProyecto(Pproyectos *proyectos);
void error();
void insertarEmpleado(Pproyectos proyectos);
void mensaje();
void advertencia();
void mostrarProyectos(Pproyectos proyectos);
void mostrarEmpleados(Pproyectos proyectos);
void pagarEmpleados(Pproyectos *proyectos);
int Menu();
int la_opcion();
void sistema_opciones(int opcion, Pproyectos *proyectos);
void liberar_memoria(Pproyectos *proyectos);
void popProyecto(Pproyectos *proyectos);
void popEmpleado(Pproyectos proyectos);

void insertarProyecto(Pproyectos *proyectos) {
    Proyectos *nuevo = (Proyectos *)malloc(sizeof(Proyectos));
    if (nuevo == NULL) {
        error();
        return;
    }
    
    printf("Ingrese un numero de ID para su proyecto: ");
    scanf("%d", &nuevo->numero);
    
    printf("\nIngrese el nombre del proyecto: ");
    getchar();
    fgets(nuevo->nombre, 64, stdin);
    nuevo->nombre[strcspn(nuevo->nombre, "\n")] = '\0';
    nuevo->inicio = NULL;

    nuevo->siguiente = *proyectos;  
    *proyectos = nuevo;     

    mensaje();
}

void error() {
    printf("Error al asignar memoria.\n");
}

void insertarEmpleado(Pproyectos proyectos) {
    int numero;
    printf("Ingrese el numero del proyecto: ");
    scanf("%d", &numero);
    system("pause");

    if (proyectos == NULL) {
        printf("No hay proyectos registrados.\n");
        return;
    }
    
    Proyectos *tempProyecto = proyectos;
    while (tempProyecto != NULL) {
        if (tempProyecto->numero == numero) break;
        tempProyecto = tempProyecto->siguiente;
    }

    if (tempProyecto == NULL) {
        printf("Uppss, verifica que el numero que acabas de ingresar pertenezca a algun proyecto...\n");
        return;
    }
    
    Empleados *nuevoEmpleado = (Empleados *)malloc(sizeof(Empleados));
    if (nuevoEmpleado == NULL) {
        error();
        return;
    }
    
    printf("Ingrese el nombre del empleado: ");
    getchar(); 
    fgets(nuevoEmpleado->nombre, 64, stdin);
    nuevoEmpleado->nombre[strcspn(nuevoEmpleado->nombre, "\n")] = '\0';
    
    printf("Ingrese el salario del empleado: ");
    scanf("%f", &nuevoEmpleado->salario);

    nuevoEmpleado->siguiente = tempProyecto->inicio;
    tempProyecto->inicio = nuevoEmpleado;
    
    advertencia();
}

void mensaje() {
   printf("el proyecto fue agregado con exito...");
}

void advertencia() {
    printf("el empleado fue agregado con exito...");
}

void mostrarProyectos(Pproyectos proyectos) {
    if (proyectos == NULL) {
        printf("Lo sentimos, pero no hay proyectos para mostrar\n");
        return;
    }
    printf("\n\t LOS PROYECTOS GUARDADOS SON: \n");
    Proyectos *temp = proyectos;
    while (temp != NULL) {
        printf("ID: %d\n", temp->numero);
        printf("Nombre: %s\n", temp->nombre);
        printf("----------------------------\n");
        temp = temp->siguiente;
    }
}

void mostrarEmpleados(Pproyectos proyectos) {
    int numero;
    printf("Ingrese el numero ID del proyecto: ");
    scanf("%d", &numero);
    
    if (proyectos == NULL) {
        printf(" lo sentimos, pero no hay proyectos registrados...\n");
        return;
    }
    
    Proyectos *tempProyecto = proyectos;
    while (tempProyecto != NULL) {
        if (tempProyecto->numero == numero) break;
        tempProyecto = tempProyecto->siguiente;
    }

    if (tempProyecto == NULL) {
        printf("Lo sentimos, pero el proyecto no fue encontrado...\n");
        return;
    }

    printf("\n\t PROYECTO '%s' \n", tempProyecto->nombre);
    printf("\nLos empleados del proyecto son: \n");
    
    Empleados *tempEmpleado = tempProyecto->inicio;
    if (tempEmpleado == NULL) {
        printf("No hay empleados en este proyecto.\n");
    } else {
        while (tempEmpleado != NULL) {
            printf("Nombre: %s\n", tempEmpleado->nombre);
            printf("Salario: %.2f\n", tempEmpleado->salario);
            printf("----------------------\n");
            tempEmpleado = tempEmpleado->siguiente;
        }
    }
}

void pagarEmpleados(Pproyectos *proyectos) {
    int numero;
    printf("Ingrese el numero ID del proyecto: ");
    scanf("%d", &numero);

    if (*proyectos == NULL) {
        printf("Lo sentimos, no hay proyectos agendados...\n");
        return;
    }
    
    Proyectos *tempProyecto = *proyectos;
    while (tempProyecto != NULL) {
        if (tempProyecto->numero == numero) break;
        tempProyecto = tempProyecto->siguiente;
    }

    if (tempProyecto == NULL) {
        printf("El proyecto no fue encontrado.\n");
        return;
    }

    Empleados *tempEmpleado = tempProyecto->inicio;
    if (tempEmpleado == NULL) {
        printf("Este proyecto no cuenta con empleados para pagarles...\n");
    } else {
        printf("\n\t Pagando empleados del proyecto '%s':\n", tempProyecto->nombre);
        while (tempEmpleado != NULL) {
            printf("Se le ha pagado al empleado %s con salario %.2f\n", tempEmpleado->nombre, tempEmpleado->salario);
            Empleados *aux = tempEmpleado;
            tempEmpleado = tempEmpleado->siguiente; 
            free(aux);  
        }
        tempProyecto->inicio = NULL;  
        printf("Todos los empleados han sido pagados.\n");
    }
}

int Menu() {
    printf("\n/********* MENU *********/");
    printf("\n 1. Insertar un nuevo proyecto");
    printf("\n 2. Insertar empleado a un proyecto");
    printf("\n 3. Mostrar proyectos");
    printf("\n 4. Mostrar empleados de un proyecto");
    printf("\n 5. Pagar empleados de un proyecto");
    printf("\n 6. Eliminar el ultimo proyecto");
    printf("\n 7. Eliminar el ultimo empleado de un proyecto");
    printf("\n 8. Salir");
    printf("\n Selecciona una opcion: ");
    return la_opcion();
}

int la_opcion() {
    int opcion;
    do {
        scanf("%d", &opcion);
    } while (opcion < 1 || opcion > 8);
    return opcion;
}

void sistema_opciones(int opcion, Pproyectos *proyectos) {
    switch (opcion) {
        case 1:
            insertarProyecto(proyectos);
            break;
        case 2:
            insertarEmpleado(*proyectos);
            break;
        case 3:
            mostrarProyectos(*proyectos);
            break;
        case 4:
            mostrarEmpleados(*proyectos);
            break;
        case 5:
            pagarEmpleados(proyectos);
            break;
        case 6:
            popProyecto(proyectos);
            break;
        case 7:
            popEmpleado(*proyectos);
            break;
        case 8:
            printf("Saliendo del programa...\n");
            liberar_memoria(proyectos);
            break;
        default:
            printf("Opcion invalida, ingresa un numero que este dentro del menu...\n");
    }
}

void liberar_memoria(Pproyectos *proyectos) {
    if (*proyectos == NULL) return;

    Proyectos *tempProyecto = *proyectos;
    while (tempProyecto != NULL) {
        Empleados *tempEmpleado = tempProyecto->inicio;
        while (tempEmpleado != NULL) {
            Empleados *auxEmpleado = tempEmpleado;
            tempEmpleado = tempEmpleado->siguiente;
            free(auxEmpleado);
        }
        
        Proyectos *auxProyecto = tempProyecto;
        tempProyecto = tempProyecto->siguiente;
        free(auxProyecto);
    }
    
    *proyectos = NULL;
}

void popProyecto(Pproyectos *proyectos) {
    if (*proyectos == NULL) {
        printf("lo sentimos, pero no hay proyectos agendados.\n");
        return;
    }
    
    Proyectos *temp = *proyectos;
    *proyectos = (*proyectos)->siguiente;

   
    Empleados *tempEmpleado = temp->inicio;
    while (tempEmpleado != NULL) {
        Empleados *auxEmpleado = tempEmpleado;
        tempEmpleado = tempEmpleado->siguiente;
        free(auxEmpleado);
    }
    
    free(temp);
    printf("el proyecto fue eliminado con exito!\n");
}

void popEmpleado(Pproyectos proyectos) {
    if (proyectos == NULL) {
        printf("No hay proyectos registrados.\n");
        return;
    }
    
    int numero;
    printf("Ingrese el numero del proyecto: ");
    scanf("%d", &numero);

    Proyectos *tempProyecto = proyectos;
    while (tempProyecto != NULL) {
    	
        if (tempProyecto->numero == numero) break;
        tempProyecto = tempProyecto->siguiente;
    }

    if (tempProyecto == NULL || tempProyecto->inicio == NULL) {
    	
        printf("lo sentimos, pero el proyecto con sus empleados no se encontraron!\n");
        return;
    }

    Empleados *tempEmpleado = tempProyecto->inicio;
    tempProyecto->inicio = tempEmpleado->siguiente; 
    free(tempEmpleado); 

    printf("Empleado eliminado de la cima de la pila.\n");
}

int main() {
    Pproyectos proyectos = NULL;
    int opcion;

    do {
        opcion = Menu();
        sistema_opciones(opcion, &proyectos);
    } while (opcion != 8);

    return 0;
}
