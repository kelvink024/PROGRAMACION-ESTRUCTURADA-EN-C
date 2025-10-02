#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generarArreglo(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }
}

void imprimirArreglo(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void ordenamientoBurbuja(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void ordenamientoInsercion(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int clave = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > clave) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = clave;
    }
}

void ordenamientoSeleccion(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void medirTiempo(void (*funcion)(int[], int), int arr[], int n) {
    clock_t start = clock();
    funcion(arr, n);
    clock_t end = clock();
    double tiempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecucion: %f segundos\n", tiempo);
}

int main() {
    const int N = 10000;
    int arr[N];

    srand(time(NULL));
    
    
    generarArreglo(arr, N);
    
    printf("Ordenamiento Burbuja:\n");
    int arrBurbuja[N];
    for (int i = 0; i < N; i++) {
        arrBurbuja[i] = arr[i];
    }
    medirTiempo(ordenamientoBurbuja, arrBurbuja, N);

    printf("Ordenamiento Insercion:\n");
    int arrInsercion[N];
    for (int i = 0; i < N; i++) {
        arrInsercion[i] = arr[i];
    }
    medirTiempo(ordenamientoInsercion, arrInsercion, N);

    printf("Ordenamiento Seleccion:\n");
    int arrSeleccion[N];
    for (int i = 0; i < N; i++) {
        arrSeleccion[i] = arr[i];
    }
    medirTiempo(ordenamientoSeleccion, arrSeleccion, N);

    return 0;
}