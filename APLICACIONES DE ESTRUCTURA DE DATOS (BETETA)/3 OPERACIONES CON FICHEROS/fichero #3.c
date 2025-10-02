#include <stdio.h>
#include <stdbool.h>

bool esPrimo(int num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

void generarPrimos(int cantidad) {
    FILE *archivo = fopen("C:\\Users\\kelvin_k024\\Desktop\\CUARTO SEMESTRE\\APLICACIONES DE ESTRUCTURA DE DATOS (BETETA)\\APLICACIONES-BETETA\\3 OPERACIONES CON FICHEROS\\primos.txt", "w");
    if (archivo == NULL) {
        perror("No se pudo abrir el archivo");
        return;
    }

    int contador = 0;
    int num = 2;

    while (contador < cantidad) {
        if (esPrimo(num)) {
            fprintf(archivo, "%d\n", num);
            contador++;
        }
        num++;
    }

    fclose(archivo);
}

int main() {
    const int cantidadPrimos = 20;
    const char *nombreArchivo = "primo.txt";

    generarPrimos(cantidadPrimos);

    printf("Los primeros %d numeros primos se han guardado en el archivo '%s'.\n", cantidadPrimos, nombreArchivo);

    return 0;
}