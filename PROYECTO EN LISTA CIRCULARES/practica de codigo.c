#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo{
    int id;
    char nombre[50];
    int edad;
    char carrera[100];

    struct nodo *siguiente;
};

typedef struct nodo Datos_generales;

Datos_generales *inicio = NULL;

//funciones principales del sistema
Datos_generales* crear_nodo(int id, char nombre[], char carrera[], int edad);
void agregar_usuario(int id, char nombre[], char carrera[], int edad);
void eliminar_usuario(int id);
void buscar_usuario(int id);
void mostrar_usuarios();
void usuario_encontrado(Datos_generales *usuario);
void datos_usuario(Datos_generales *usuario);
void liberar_lista();

//funciones de mensajes de advertencia del sistema
void msj_error();
void msj_agregacion();
void msj_eliminacion();
void msj_mostrar_usuarios();
void msj_convalidacion();
void msj_liberar_lista();
void mjs_manejar_lista_vacia();
void msj_por_defecto();

//funciones de menu y cada ejecucion del sistema
void menu();
int la_opcion();
void opcion_agregar_usuario();
void opcion_eliminar_usuario();
void opcion_buscar_usuario();
void opcion_listado_general();
void opcion_eliminar_memoria();
void menu_opciones(int opcion);
int main();

Datos_generales* crear_nodo(int id, char nombre[], char carrera[], int edad) {
    Datos_generales *nuevo = (Datos_generales*)malloc(sizeof(Datos_generales));
    if(nuevo == NULL){
        msj_error();
        exit(-1);
    }

    nuevo->id = id;
    strcpy(nuevo->nombre, nombre);
    strcpy(nuevo->carrera, carrera);  // Added this line to assign carrera
    nuevo->edad = edad;
    nuevo->siguiente = nuevo;
    
    return nuevo;
}

void msj_error(){
    printf("Error al asignar memoria, intentalo de nuevo!\n");
}

void agregar_usuario(int id, char nombre[], char carrera[], int edad) {
    Datos_generales *nuevo = crear_nodo(id, nombre, carrera, edad);  // Fixed argument order

    if (inicio == NULL) {
        inicio = nuevo;
    } else {
        Datos_generales *temp = inicio;
        while (temp->siguiente != inicio) {
            temp = temp->siguiente;
        }

        temp->siguiente = nuevo;
        nuevo->siguiente = inicio;
    }
    msj_agregacion();
}

void msj_agregacion(){
    printf("El usuario fue agregado con exito!\n");
}

void eliminar_usuario(int id) {
    if (inicio == NULL) {  // Fixed comparison operator (was `=` instead of `==`)
        mjs_manejar_lista_vacia();
        return;
    }

    Datos_generales *temp = inicio, *prev = NULL;

    if (temp->siguiente == inicio && temp->id == id) {
        free(temp);
        inicio = NULL;
        msj_eliminacion();
        return;
    }

    if (temp->id == id) {
        Datos_generales *ultimo = temp;  // Fixed incorrect declaration
        while (ultimo->siguiente != inicio) {
            ultimo = ultimo->siguiente;
        }
        inicio = inicio->siguiente;
        ultimo->siguiente = inicio;
        free(temp);
        msj_eliminacion();
        return;
    }

    while (temp->siguiente != inicio && temp->id != id) {
        prev = temp;
        temp = temp->siguiente;
    }

    if (temp->id == id) {
        prev->siguiente = temp->siguiente;
        free(temp);
        msj_eliminacion();
    } else {
        msj_convalidacion();
    }
}

void msj_eliminacion(){
    printf("El usuario fue eliminado con exito!\n");
}

void buscar_usuario(int id) {

    if (inicio == NULL) {  // Fixed comparison operator (was `=` instead of `==`)
        mjs_manejar_lista_vacia();
        return;
    }

    Datos_generales *temp = inicio;

    do {

        if (temp->id == id) {
            usuario_encontrado(temp);
            return;
        }

        temp = temp->siguiente;

    } while (temp != inicio);

    msj_convalidacion();
}

void usuario_encontrado(Datos_generales *usuario) {

    printf("\t --- Información del usuario encontrado ---\n");
    printf("----------------------------\n");
    printf("-ID: %d\n", usuario->id);  // Fixed incorrect variable usage
    printf("Nombre: %s\n", usuario->nombre);
    printf("Carrera: %s\n", usuario->carrera);
    printf("Edad: %d\n", usuario->edad);
    printf("------------------------------------------\n");
}

void msj_convalidacion(){
    printf("El usuario no existe.\n");  // Fixed format specifier
}

void mostrar_usuarios() {
    if (inicio == NULL) {
        mjs_manejar_lista_vacia();
        return;
    }

    Datos_generales *temp = inicio;

    printf("\t Listado de todos los usuarios\n");

    do {
        datos_usuario(temp);
        temp = temp->siguiente;
    } while (temp != inicio);  // Fixed infinite loop: added `datos_usuario`
}

void datos_usuario(Datos_generales *usuario) {
    printf("-ID: %d\n", usuario->id);  // Fixed incorrect variable usage
    printf("Nombre de usuario: %s\n", usuario->nombre);
    printf("Carrera: %s\n", usuario->carrera);
    printf("Edad: %d\n", usuario->edad);
    printf("--------------------------------------\n");
}

void liberar_lista(){
    if(inicio == NULL){
        return;
    }

    Datos_generales *temp = inicio;
    Datos_generales *siguiente;

    do {
        siguiente = temp->siguiente;
        free(temp);
        temp = siguiente;
    } while (temp != inicio);

    inicio = NULL;
    msj_liberar_lista();
}

void msj_liberar_lista(){
    printf("La memoria fue vaciada al igual que la lista...\n");
}

void mjs_manejar_lista_vacia(){
    printf("Lo sentimos, pero la lista está vacía...\n");
}

void menu(){
    printf("\n-------MENU-------\n");
    printf("1. Agregar usuarios\n");
    printf("2. Eliminar usuario\n");
    printf("3. Buscar usuarios\n");
    printf("4. Mostrar todos los usuarios agregados\n");
    printf("5. Salir\n");
    printf("Selecciona una opcion: ");
}

int la_opcion(){
    int opcion;
    scanf("%d", &opcion);
    return opcion;
}

void opcion_agregar_usuario(){
    int edad, id;
    char nombre[50], carrera[100];  // Added missing `carrera` input

    printf("\n");
    printf("\t AGREGAR USUARIO\n");
    printf("\n");

    printf("Ingrese el ID de usuario: ");
    scanf("%d", &id);
    printf("\n");

    printf("Ingrese el nombre del nuevo usuario: ");
    scanf(" %[^\n]", nombre);
    printf("\n");

    printf("Ingrese la carrera del usuario: ");  // Added prompt
    scanf(" %[^\n]", carrera);
    printf("\n");

    printf("Ingrese la edad del usuario: ");
    scanf("%d", &edad);
    printf("\n");

    agregar_usuario(id, nombre, carrera, edad);
}

void opcion_eliminar_usuario(){
    int id;
    printf("\t ELIMINAR USUARIO\n");
    printf("Ingrese el número de ID del usuario a eliminar: ");
    scanf("%d", &id);
    eliminar_usuario(id);
}

void opcion_buscar_usuario(){
    int id;
    printf("\n BUSCAR ESTUDIANTE\n");
    printf("Ingrese el numero de ID del usuario a buscar: ");
    scanf("%d", &id);
    buscar_usuario(id);
}

void opcion_listado_general(){
    printf("\n\n");
    printf("\t LISTADO GENERAL DE LOS USUARIOS AGREGADOS\n");
    mostrar_usuarios();
}

void opcion_eliminar_memoria(){
    liberar_lista();
    printf("Saliendo....");
}

void msj_por_defecto(){
    printf("Ups, opcion invalida, intentelo de nuevo...");
}

void menu_opciones(int opcion){
    switch(opcion){
        case 1:
            opcion_agregar_usuario();
            break;
        case 2:
            opcion_eliminar_usuario();
            break;
        case 3:
            opcion_buscar_usuario();
            break;
        case 4:
            opcion_listado_general();
            break;
        case 5:
            opcion_eliminar_memoria();
            break;
        default:
            msj_por_defecto();
    }
}

int main(){
    int opcion;

    do {
        menu();

        opcion = la_opcion();

        menu_opciones(opcion);

    } while (opcion != 5);

    return 0;
}