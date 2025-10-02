#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;

    char *buffer = (char *)malloc(256 * sizeof(char));
    if(buffer == NULL){
        printf("error al asignarle memoria\n");
        exit(1);
    }

    file = fopen("C:\\Users\\kelvin_k024\\Desktop\\CUARTO SEMESTRE\\APLICACIONES DE ESTRUCTURA DE DATOS (BETETA)\\APLICACIONES-BETETA\\3 OPERACIONES CON FICHEROS\\SALIDA.TXT", "w");
    if (file == NULL) {
        perror("No se pudo abrir el archivo");
        return EXIT_FAILURE;
    }

    printf("ingresa un texto: \n");
    printf("o CTRL + Z para finalizar\n");
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        fputs(buffer, file);
    }

    fclose(file);

    printf("Texto guardado en SALIDA.TXT\n");
    return EXIT_SUCCESS;
}