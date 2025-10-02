#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// definicion de la estructura para los nodos
struct nodo {
    int id;
    char nombre[50];
    int edad;
    struct nodo *siguiente;
};

typedef struct nodo Nodo;
Nodo *inicio = NULL;

// todos los prototipos de funciones para su funcionamiento
Nodo* crearNodo(int id, char nombre[], int edad);
void error();
void agregarEstudiante(int id, char nombre[], int edad);
void agregacion();
void eliminarEstudiante(int id);
void eliminacion();
void buscarEstudiante(int id);
void estudiante_encontrado(Nodo *estudiante);
void convalidacion(int id);
void mostrarEstudiantes();
void datos_estudiante(Nodo *estudiante);
void liberarLista();
void mensaje_liberacion();
void manejarListaVacia();
void menu();
int la_opcion();
void opcion_agregar_estudiante();
void opcion_eliminar_estudiante();
void opcion_buscar_estudiante();
void opcion_listado_general();
void opcion_eliminacion_memoria();
void por_defecto();
void sistemas_opciones(int opcion);
int main();

// esta funcion se encargara de ir agregando nodos al final de la lista cuando sea llamada al momento de agregar un nuevo estudiante
Nodo* crearNodo(int id, char nombre[], int edad) {
	
    Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
    if(nuevo == NULL) {
    	
    	// llamado a la funcion que nos muestre que no se asigno memoria correctamente
        error();
        exit(-1);
    }
    
    nuevo->id = id;
    strcpy(nuevo->nombre, nombre);
    nuevo->edad = edad;
    nuevo->siguiente = nuevo;
    
    return nuevo;
}

// mensaje de error al momento de asignarle memoria
void error(){
    printf("Error al asignar memoria!\n");
}

// esta funcion es la que se encarga de ir agregando estudianntes al final de la lista
void agregarEstudiante(int id, char nombre[], int edad) {
	
	// al momento de llamar a la funcio de agregar estudiante, tambien se llamara a la funcio de creacion de nodo para que se vallan creando...
    Nodo *nuevo = crearNodo(id, nombre, edad);

    if(inicio == NULL) {
        inicio = nuevo;
    } else {
        Nodo *temp = inicio;
        
        while(temp->siguiente != inicio) {
        	
            temp = temp->siguiente;
        }
        
        temp->siguiente = nuevo;
        nuevo->siguiente = inicio;
    }
    
    // llamamo a la funcion que para visualizar el mensaje de agregacion
    agregacion();
}

// funcion que es el que se muestra como mensaje cuando un estudiante fue agregado exitosamente
void agregacion(){
	
	printf("el estudiante fue agregado con exito!!.\n");
	
}

// esta funcion se encargara de ir eliminando estudiantes mediante su id de identificacion
void eliminarEstudiante(int id) {
	
    if(inicio == NULL) {
    	
    	// llamamos a la funcion para visualizar que fue vaciada ya sea el nodo o la asignacion de memoria general
        manejarListaVacia();
        return;
    }

    Nodo *temp = inicio, *prev = NULL;

    // en caso de eliminar al unico nodo de la lista
    if(temp->siguiente == inicio && temp->id == id) {
    	
        free(temp);
        inicio = NULL;
        eliminacion();
        
        return;
    }

    // en caso de eliminar al nodo que es el primero 
	if(temp->id == id) {
		
        Nodo *ultimo = inicio;
        while(ultimo->siguiente != inicio) {
        	
            ultimo = ultimo->siguiente;
        }
        
        inicio = inicio->siguiente;
        ultimo->siguiente = inicio;
        free(temp);
        
    	eliminacion();
    	
        return;
    }

    // en este caso de eliminar el nodo que esta en el medio o al final de la lista
    while(temp->siguiente != inicio && temp->id != id) {
    	
        prev = temp;
        temp = temp->siguiente;
    }

    if(temp->id == id) {
    	
        prev->siguiente = temp->siguiente;
        free(temp);
        
        eliminacion();
        
    } else {
        convalidacion(id);
    }
}
 // esta funcion solamente mostrara el mensaje de eliminacion
void eliminacion(){
	
	printf("el estudiante fue eliminado con exito\n");
}

// esta funcion se encargara de buscar a un estudiante mediante su ID de identificacion de asignacion
void buscarEstudiante(int id) {
    if(inicio == NULL) {
    	
        manejarListaVacia();
        return;
    }

    Nodo *temp = inicio;
    do {
    	
        if(temp->id == id) {
        	
            estudiante_encontrado(temp);
            return;
        }
        
        temp = temp->siguiente;
        
    } while(temp != inicio);

    convalidacion(id);
}

void estudiante_encontrado(Nodo *estudiante){
	
    printf("\t---informacion del estudiante---\n");    
    printf("----------------------------\n");
    printf("ID: %d\n", estudiante->id);
    printf("Nombre: %s\n", estudiante->nombre);
    printf("Edad: %d\n", estudiante->edad);
    printf("----------------------------\n");
}

void convalidacion(int id){
	
	printf("El estudiante con ID [ %d ] no existe.\n", id);	
}

// funcion para mostrar todos los estudiantes agregados en la lista circular
void mostrarEstudiantes() {
    if(inicio == NULL) {
    	
        manejarListaVacia();
        
        return;
    }

    Nodo *temp = inicio;
    
    printf("\t---Listado de estudiantes---\n");
    do {
    	
       datos_estudiante(temp);
        
        temp = temp->siguiente;
        
    } while(temp != inicio);
}

void datos_estudiante(Nodo *estudiante){
	
	printf("-ID: %d\n", estudiante->id);
    printf("Nombre: %s\n", estudiante->nombre);
    printf("Edad: %d\n", estudiante->edad);
    printf("-------------------------\n");
}

// esta funcion se encargara de eliminar toda la lista de nodos al igual que la  memoria
void liberarLista() {
	
    if(inicio == NULL){
    	
    	return;
	}

    Nodo *temp = inicio;
    Nodo *nextNode;

    do {
    	
        nextNode = temp->siguiente;
        free(temp);
        temp = nextNode;
        
    } while(temp != inicio);

    inicio = NULL;
    mensaje_liberacion();
}

// mensaje cuando ya se halla eliminado todos los datos
void mensaje_liberacion(){
	
	printf("la memoria fue vaciada al igual que la lista...\n");
	
}

// funcion cuando se precione la opcion de motrar datos y esta se encuentre vacia
void manejarListaVacia() {
	
    printf("lo sentimos pero la lista esta vacia...\n");
    
}

// funcion para visualizar el menu de opciones
void menu() {
	
    printf("\n--------MENU--------\n");
    printf("1. Agregar estudiante\n");
    printf("2. Eliminar estudiante\n");
    printf("3. Buscar estudiante\n");
    printf("4. Mostrar todos los estudiantes inscritos\n");
    printf("5. Salir\n");
    printf("Seleccione una opcion: ");
    
}

// funcion para capturar la opcion del usruario
int la_opcion() {
	
    int opcion;
    
    scanf("%d", &opcion);

    // esta sera retornada a la funcion 'sistema_opciones' donde se podra ejecutar
    return opcion;
}

// funcion para ir agregando los datos y asi llamando a lafuncion para ir guardandolos dentro de un nodo
void opcion_agregar_estudiante(){
	int edad, id;
	char nombre[50];
	
	printf("\n");
    printf("\tAGREGAR ESTUDIANTE\n");
    printf("\n");
            
    printf("ingrese el ID del estudiante: ");
    scanf("%d", &id);
    printf("ingrese el nombre del estudiante: ");
    scanf(" %[^\n]", nombre);
    printf("ingrese la edad del estudiante: ");
    scanf("%d", &edad);
    printf("\n");

    // se manda a llamar a la funcion para agregar un nuevo estudiante
    agregarEstudiante(id, nombre, edad);
	
}

//esta funcionse encarga de buscar al estudiante mediante su id de identificacion
void opcion_eliminar_estudiante(){
	
	int id;

	printf("\nELIMINAR ESTUDIANTE\n");
    printf("Ingrese el ID del estudiante a eliminar: ");
    scanf("%d", &id);
    // llamado a la funcion para eliminar
    eliminarEstudiante(id);
}

//esta funcion se encargara de buscar al estudiante mediante su id de usuario
void opcion_buscar_estudiante(){
	int id;

	printf("\nBUSCAR ESTUDIANTE\n");
    printf("Ingrese el ID del estudiante a buscar: ");
    scanf("%d", &id);
    //llamado de la funcion para buscar un estudiante por su ID de identificacion
    buscarEstudiante(id);
}

//esta funcion se encargara de mostrar todos los datos de los estudiantes agregados
void opcion_listado_general(){
	
	printf("\n\n");
    printf("\t LISTA DE ESTUDIANTES INSCRITOS\n");
    // llamado a la funcion para mostrar todos los estudiantes
    mostrarEstudiantes();
}

// al momento de darle en la opcion 5, se llamara a esta funcion los cual tambien llamara a liberar memoria
void opcion_eliminacion_memoria(){
	// al mmomento del precionar la opcion 5, mandaria a cancelar todo la ejecucion y automaticamente eliminaria memoria
    liberarLista();
    printf("Saliendo...\n");
}

//al momento de no ingresar una opcion fuera del rango
void por_defecto(){
    printf("upps, opcion invalida, intentelo de nuevo...\n");
}

// esta funcion se encargara de poder ejecutar la opcion seleccionada desde la funcion 'la_opcion'
void sistemas_opciones(int opcion) {
	
    switch(opcion) {
        
    	// cada case estara llamando a su funcion respectivamente para que haga el procedimiento que se esta pidiendo
        case 1:
            // funcion para agregar un estudiante
			opcion_agregar_estudiante();
            break;
        case 2:
            // funcion para eliminar un estudiante mediante si id de identificacion
        	opcion_eliminar_estudiante();
            break;
        case 3:
            // funcion para buscar a un estudiante mediante su id de identificacion
            opcion_buscar_estudiante();
            break;
        case 4:
            // funcion para mosotrar todos los datos agregados dento de la lista circular
        	opcion_listado_general();
            break;
        case 5:
            // funcion para eliminar todos los datos luego de haber finalizado el ejercicio
            opcion_eliminacion_memoria();
            break;
        default:
            por_defecto();
    }
}

// la funcion principal solamente es como un mediador de las fuciones que se encargaran de hacer el procedimeinto de opciones y menu
int main() {
	
    int opcion;
    
    do {
    	
        // llamado de la funcion para mostar el menu
        menu();
        // el valor que devuelve de la funciona capturar el valor sera el cual mantendra el ciclo
        opcion = la_opcion();

        // llamado de la funcion de para ejecutar lo que halla devuelto la funcion que captura la opcion seleccionada por el usuario
        sistemas_opciones(opcion);
        
    } while(opcion != 5);

    return 0; 
}