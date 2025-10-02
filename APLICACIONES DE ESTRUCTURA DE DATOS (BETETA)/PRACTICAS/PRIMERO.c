#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo{
	int dato;
	struct nodo *siguiente;
};

struct nodo* creacion_nodo(int dato){
	
	struct nodo* nuevo_nodo = (struct nodo*)malloc(sizeof(struct nodo));
	if(nuevo_nodo ==  NULL) {
		
		printf("error al asignar memoria\n");
		
	}else{
		
		printf("memorias asignada exitosamente para el nuevo nodo\n");
		
	}
		
	nuevo_nodo->dato = dato;
	nuevo_nodo->siguiente = NULL;
	
	return nuevo_nodo;
}

// insertar al inicio de la lista 
void insertar_inicio(struct nodo** head, int dato){
	
	struct nodo* nuevo_nodo = creacion_nodo(dato);
	if (nuevo_nodo == NULL) return;
	
	if (*head == NULL){
		
		*head = nuevo_nodo;
		nuevo_nodo->siguiente = nuevo_nodo;
		
	}else{
		
		struct nodo* ultimo = *head;
		
		while(ultimo->siguiente != *head){
			
			ultimo = ultimo->siguiente;
		}
		
		nuevo_nodo->siguiente = *head;
		ultimo->siguiente = nuevo_nodo;
		*head = nuevo_nodo;
	}
}

//funcion para que se inserter los datos de ultimo
void insertar_final(struct nodo** head, int dato){
	
	struct nodo* nuevo_nodo = creacion_nodo(dato);
	if(nuevo_nodo == NULL) return;
	
	if(*head == NULL){
		
		*head = nuevo_nodo;
		nuevo_nodo->siguiente = nuevo_nodo;
		
	}else{
		
		struct nodo* ultimo = *head;
		nuevo_nodo->siguiente = nuevo_nodo;
		
		while(ultimo->siguiente != *head){
			
			ultimo = ultimo->siguiente;
		}
		ultimo->siguiente = nuevo_nodo;
		nuevo_nodo->siguiente = *head;
	}
}

int main(){
	
}