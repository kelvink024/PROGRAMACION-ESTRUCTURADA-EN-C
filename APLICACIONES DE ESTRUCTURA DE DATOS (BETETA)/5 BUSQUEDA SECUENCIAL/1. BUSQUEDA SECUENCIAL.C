#include <stdio.h>
#include <string.h>

/*
1.1. Ejercicios Propuesto 1:

Elaborar un programa usando la búsqueda secuencial para encontrar la letra dentro de una
cadena de caracteres. Ejemplo. Cadena: Computación, Buscar la letra: u.

*/

int busqueda(char cadena[], char letra){
    int contador = 0, i;
    int longitud = strlen(cadena);

    for(i=0; i<longitud; i++){
        if(cadena[i] == letra){
            contador++;
        }
    }
    return contador;
}

int main(){
    char cadena[100];
    char letra;

    printf("ingrese una cadena: \n");
    scanf("%s", cadena);
    
    fflush(stdin);

    printf("ingrese el caracter a buscar: \n");
    scanf("%c", &letra);
    int resultado = busqueda(cadena, letra);

    printf("la letra '%c' aparece %d veces en la cadena '%s' ", letra, resultado, cadena);
    return 0;
}