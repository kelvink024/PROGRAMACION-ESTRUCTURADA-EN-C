#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PALABRAS 100
#define LONGITUD_MAXIMA 50

//funciones para el método de ordenamiento y la búsqueda binaria
void Quicksort(char palabras[][LONGITUD_MAXIMA], int bajo, int alto);
int busqueda_binaria(char palabras[][LONGITUD_MAXIMA], int bajo, int alto, char *clave);
int particion(char palabras[][LONGITUD_MAXIMA], int bajo, int alto);
void swap(char* a, char* b);

// funciones en donde se encargaran de hacer los procedimientos necesarios
void visualizar_palabras(char palabras[][LONGITUD_MAXIMA], int num_palabras);
void aniadir_palabra(char palabras[][LONGITUD_MAXIMA], int *num_palabras);
void cargar_palabras(char palabras[][LONGITUD_MAXIMA], int *num_palabras);
void guardar_palabras(char palabras[][LONGITUD_MAXIMA], int num_palabras);

//funcion para visualizar las palabras
void visualizar_palabras(char palabras[][LONGITUD_MAXIMA], int num_palabras) {
    int i;
    printf("\np alabras del diccionario:\n");
    for (i = 0; i < num_palabras; i++) {
        printf("%s\n", palabras[i]);
    }
}

//funcion para aniadir palabras
void aniadir_palabra(char palabras[][LONGITUD_MAXIMA], int *num_palabras) {
    if (*num_palabras >= MAX_PALABRAS) {
        printf("no se pueden aniadir mas palabras\n");
        return;
    }
    printf("ingrese una nueva palabra: ");
    scanf("%s", palabras[*num_palabras]);
    (*num_palabras)++;

    printf("la palabra ha sido aniadida a la lista\n");
}

//funcion para abrir el fichero en donde se encuentran los datos guardados
void cargar_palabras(char palabras[][LONGITUD_MAXIMA], int *num_palabras) {
    FILE *archivo = fopen("C:\\Users\\kelvin_k024\\Desktop\\CUARTO SEMESTRE\\APLICACIONES DE ESTRUCTURA DE DATOS (BETETA)\\APLICACIONES-BETETA\\5 BUSQUEDA SECUENCIAL\\palabras.txt", "r");
    if (archivo == NULL) {
        printf("error al abrir el fichero\n");
        return;
    }

    while (fscanf(archivo, "%s", palabras[*num_palabras]) != EOF) {
        (*num_palabras)++;
    }
    fclose(archivo);
}

//funcion para guardar las palabras en el fichero
void guardar_palabras(char palabras[][LONGITUD_MAXIMA], int num_palabras) {
    int i;
    FILE *archivo = fopen("palabras.txt", "w");
    if (archivo == NULL) {
        printf("no se pudo abrir el fichero para guardar las palabras\n");
        return;
    }

    for (i = 0; i < num_palabras; i++) {
        fprintf(archivo, "%s\n", palabras[i]);
    }

    fclose(archivo);
}

//funcion para el ordenamiento aplicando Quicksort
void Quicksort(char palabras[][LONGITUD_MAXIMA], int bajo, int alto) {
    if (bajo < alto) {
        int pi = particion(palabras, bajo, alto);
        Quicksort(palabras, bajo, pi - 1);
        Quicksort(palabras, pi + 1, alto);
    }
}

int particion(char palabras[][LONGITUD_MAXIMA], int bajo, int alto) {
    char pivote[LONGITUD_MAXIMA];
    strcpy(pivote, palabras[alto]);
    int i = (bajo - 1);
    int j;

    for (j = bajo; j < alto; j++) {
        if (strcmp(palabras[j], pivote) < 0) {
            i++;
            swap(palabras[i], palabras[j]);
        }
    }
    swap(palabras[i + 1], palabras[alto]);
    return (i + 1);
}

void swap(char* a, char* b) {
    char temporal[LONGITUD_MAXIMA];
    strcpy(temporal, a);
    strcpy(a, b);
    strcpy(b, temporal);
}

//funcion de busqueda binaria
int busqueda_binaria(char palabras[][LONGITUD_MAXIMA], int bajo, int alto, char *clave) {
    if (bajo <= alto) {
        int medio = bajo + (alto - bajo) / 2;
        int resultado = strcmp(clave, palabras[medio]);

        if (resultado == 0) {
            return medio;
        } else if (resultado < 0) {
            return busqueda_binaria(palabras, bajo, medio - 1, clave);
        } else {
            return busqueda_binaria(palabras, medio + 1, alto, clave);
        }
    }
    return -1;
}

int main() {
    char palabras[MAX_PALABRAS][LONGITUD_MAXIMA];
    int num_palabras = 0;
    int opcion, encontrado = -1;
    char clave[LONGITUD_MAXIMA];

    cargar_palabras(palabras, &num_palabras);

    do {
        printf("\n***** busqueda del diccionario *****\n");
        printf("1. visualizar palabras\n");
        printf("2. Aniadir una nueva palabra a las ya existentes\n");
        printf("3. ordenar las palabras utilizando Quicksort\n");
        printf("4. buscar una palabra usando la busqueda binaria\n");
        printf("5. visualizar la palabra encontrada\n");
        printf("6. ninguna de las anteriores\n");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                visualizar_palabras(palabras, num_palabras);
                break;
            case 2:
    			aniadir_palabra(palabras, &num_palabras);
    			guardar_palabras(palabras, num_palabras);
    			break;
            case 3:
                Quicksort(palabras, 0, num_palabras - 1);
                printf("palabras ordenadas\n");
                break;
            case 4:
                printf("ingrese la clave a buscar: ");
                scanf("%s", clave);
                encontrado = busqueda_binaria(palabras, 0, num_palabras - 1, clave);
                if (encontrado != -1) {
                    printf("palabra encontrada en la posicion %d\n", encontrado);
                } else {
                    printf("Palabra no encontrada\n");
                }
                break;
            case 5:
                if (encontrado != -1) {
                    printf("palabra encontrada: %s\n", palabras[encontrado]);
                } else {
                    printf("no ha realizado ninguna búsqueda o la palabra no fue encontrada\n");
                }
                break;
            case 6:
                printf("vamonos de aca \n");
                break;
            default:
                printf("opcion invalida\n");
                break;
        }
    } while (opcion != 6);

    guardar_palabras(palabras, num_palabras);
    return 0;
}
