#include <stdio.h>

void leerYMostrarArchivo(const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("No se pudo abrir el archivo");
        return;
    }

    int num;
    while (fscanf(archivo, "%d", &num) != EOF) {
        printf("%d\n", num);
    }

    fclose(archivo);
}

int main() {
    const char *nombreArchivo = "C:\\Users\\kelvin_k024\\Desktop\\CUARTO SEMESTRE\\APLICACIONES DE ESTRUCTURA DE DATOS (BETETA)\\APLICACIONES-BETETA\\3 OPERACIONES CON FICHEROS\\primos.txt";
    printf("los numero primos son:\n");
    leerYMostrarArchivo(nombreArchivo);

    return 0;
}