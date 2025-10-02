#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMO_PALABRAS 10000       
#define MAXIMO_LONGITUD_PALABRA 100

int comparar(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}
int leer_palabras_desde_archivo(const char *nombre_archivo, char *palabras[], int maximo_palabras) {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        perror("No se puede abrir el archivo");
        exit(EXIT_FAILURE);
    }

    char buffer[MAXIMO_LONGITUD_PALABRA];
    int contador = 0;

    while (fscanf(archivo, "%s", buffer) == 1) {
        palabras[contador] = strdup(buffer); 
        contador++;
        if (contador >= maximo_palabras) {
            break;
        }
    }

    fclose(archivo);  // Cierra el archivo después de leer
    return contador;  // Retorna la cantidad de palabras leídas
}

void escribir_palabras_en_archivo(const char *nombre_archivo, char *palabras[], int cantidad) {
    FILE *archivo = fopen(nombre_archivo, "w");
    if (archivo == NULL) {
        perror("No se puede abrir el archivo");
        exit(EXIT_FAILURE);
    }

    // Escribe cada palabra en el archivo, una por línea
    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "%s\n", palabras[i]);
        free(palabras[i]);
    }

    fclose(archivo);  
}

int main() {
    const char *ruta_archivo_entrada = "ruta/al/archivo/de/entrada.txt";  
    const char *ruta_archivo_salida = "ruta/al/archivo/de/salida.txt";   

    char *palabras[MAXIMO_PALABRAS];  
    int numero_palabras = leer_palabras_desde_archivo(ruta_archivo_entrada, palabras, MAXIMO_PALABRAS);  

   
    qsort(palabras, numero_palabras, sizeof(char *), comparar);

    escribir_palabras_en_archivo(ruta_archivo_salida, palabras, numero_palabras);

    return 0;
}
