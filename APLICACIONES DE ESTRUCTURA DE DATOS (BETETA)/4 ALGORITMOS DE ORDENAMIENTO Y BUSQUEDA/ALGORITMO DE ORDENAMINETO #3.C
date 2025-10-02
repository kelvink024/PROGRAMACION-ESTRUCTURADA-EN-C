#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 10  // Utiliza mayúsculas para las constantes

void imprimir_vector(int vector[], int tamanio) {
    for (int i = 0; i < tamanio; i++) {
        printf("%d ", vector[i]);  // Añadido un espacio para mejor formato
    }
    printf("\n");
}

void inicializar_vector(int vector[], int tamanio) {  // Cambiado el nombre del parámetro para que coincida
    for (int i = 0; i < tamanio; i++) {
        vector[i] = rand() % 40;  // Añadido el punto y coma que faltaba
    }
}

int eliminar_duplicados(int vector[], int tamanio, int resultado[]) {
    int resultado_tamanio = 0;

    for (int i = 0; i < tamanio; i++) {
        int duplicado = 0;

        for (int j = 0; j < resultado_tamanio; j++) {  // Corregido de 'i' a 'j' en el bucle
            if (vector[i] == resultado[j]) {
                duplicado = 1;
                break;
            }
        }

        if (!duplicado) {
            resultado[resultado_tamanio] = vector[i];
            resultado_tamanio++;
        }
    }

    return resultado_tamanio;
}

int main() {
    int vector[TAM];
    int vector_sin_duplicados[TAM];
    int tamanio_sin_duplicados;

    srand(time(NULL));
    inicializar_vector(vector, TAM);

    printf("El vector original es: \n");
    imprimir_vector(vector, TAM);

    tamanio_sin_duplicados = eliminar_duplicados(vector, TAM, vector_sin_duplicados);

    printf("El vector sin duplicados es: \n");
    imprimir_vector(vector_sin_duplicados, tamanio_sin_duplicados);

    return 0;
}