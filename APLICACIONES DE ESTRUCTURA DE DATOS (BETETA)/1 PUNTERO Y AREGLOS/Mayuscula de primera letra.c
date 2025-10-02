#include <stdio.h>
#include <ctype.h>


void capitalizar(char *cadena);

int main() {
    char *cadena=(char*)calloc(100, sizeof(char)); 

    
    printf("ingresa un parrafo: ");
    fgets(cadena, sizeof(cadena), stdin);

    
    capitalizar(cadena);

    printf("parrafo actualizado: %s\n", cadena);

    return 0;
}


void capitalizar(char *cadena) {
    int capitalizarSiguiente = 1;

    while (*cadena) {
        if (capitalizarSiguiente && isalpha(*cadena)) {
            *cadena = toupper(*cadena);
            capitalizarSiguiente = 0;
        }

        if (*cadena == '.') {
            capitalizarSiguiente = 1;
        }

        cadena++;
    }
}
