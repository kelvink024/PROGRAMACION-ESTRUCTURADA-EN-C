#include <stdio.h>


int calcularSuma(int *puntero, int tam);
float calcularMedia(int suma, int tam);

int main() {
    int vector[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int suma;
    float media;

    
    suma = calcularSuma(vector, 10);

    
    media = calcularMedia(suma, 10);

    
    printf("La media aritmética del vector es: %.2f\n", media);

    return 0;
}


int calcularSuma(int *puntero, int tam) {
    int suma = 0;
    for (int i = 0; i < tam; i++) {
        suma += *(puntero + i);
    }
    return suma;
}


float calcularMedia(int suma, int tam) {
    return suma / tam;
}
