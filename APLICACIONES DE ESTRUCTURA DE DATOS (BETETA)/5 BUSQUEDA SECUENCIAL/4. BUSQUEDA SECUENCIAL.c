#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int **p;    
    int filas;  
    int cols; 
} tmatriz2D;

// Función para asignar memoria a la matriz
tmatriz2D *AsignarMem2D(int filas, int cols) {
    if (filas <= 0 || cols <= 0) {
        printf("El número de filas y columnas debe ser mayor que cero.\n");
        return NULL;
    }

    int f = 0;
    tmatriz2D *x = (tmatriz2D *)malloc(sizeof(tmatriz2D));
    if (x == NULL) {
        printf("Error al asignar memoria para la estructura tmatriz2D.\n");
        return NULL;
    }

    x->p = NULL; 
    x->filas = filas; 
    x->cols = cols;

    x->p = (int **)malloc(filas * sizeof(int *));
    if (x->p == NULL) {
        printf("Error al asignar memoria para las filas de la matriz.\n");
        free(x);
        return NULL;
    }

    for (f = 0; f < x->filas; f++) {
        printf("Asignando memoria para la fila %d\n", f);
        x->p[f] = (int *)malloc(cols * sizeof(int));
        if (x->p[f] == NULL) {
            printf("Error al asignar memoria para la fila %d.\n", f);
            LiberarMem2D(*x); 
            free(x);
            return NULL;
        }
    }
    return x;
}


void LiberarMem2D(tmatriz2D x) {
    int f = 0;
    for (f = 0; f < x.filas; f++) {
        free(x.p[f]);
    }
    free(x.p);
}


void Visualizar(tmatriz2D x) {
    for (int i = 0; i < x.filas; i++) {
        for (int j = 0; j < x.cols; j++) {
            printf("%d ", x.p[i][j]);
        }
        printf("\n");
    }
}

void LeerDatos(tmatriz2D *x) {
    printf("Ingrese los valores de la matriz (%d x %d):\n", x->filas, x->cols);
    for (int i = 0; i < x->filas; i++) {
        for (int j = 0; j < x->cols; j++) {
            printf("Elemento [%d][%d]: ", i, j);
            scanf("%d", &(x->p[i][j]));
        }
    }
}


void Ordenar(tmatriz2D *x) {
    int total = x->filas * x->cols;
    int *lineal = (int *)malloc(total * sizeof(int));
    int index = 0;

    for (int i = 0; i < x->filas; i++) {
        for (int j = 0; j < x->cols; j++) {
            lineal[index++] = x->p[i][j];
        }
    }

    for (int i = 0; i < total - 1; i++) {
        for (int j = i + 1; j < total; j++) {
            if (lineal[i] > lineal[j]) {
                int temp = lineal[i];
                lineal[i] = lineal[j];
                lineal[j] = temp;
            }
        }
    }

    index = 0;
    for (int i = 0; i < x->filas; i++) {
        for (int j = 0; j < x->cols; j++) {
            x->p[i][j] = lineal[index++];
        }
    }

    free(lineal);
}

void BusquedaBinaria(tmatriz2D *x, int valor) {
    int total = x->filas * x->cols;
    int *lineal = (int *)malloc(total * sizeof(int));
    int index = 0;

    for (int i = 0; i < x->filas; i++) {
        for (int j = 0; j < x->cols; j++) {
            lineal[index++] = x->p[i][j];
        }
    }

    int inf = 0, sup = total - 1, medio;
    while (inf <= sup) {
        medio = (inf + sup) / 2;
        if (lineal[medio] == valor) {
            printf("Valor %d encontrado en la posición lineal %d.\n", valor, medio);
            free(lineal);
            return;
        } else if (lineal[medio] < valor) {
            inf = medio + 1;
        } else {
            sup = medio - 1;
        }
    }

    printf("Valor %d no encontrado.\n", valor);
    free(lineal);
}

int main() {
    int filas, cols, valor;
    printf("Ingrese el número de filas y columnas de la matriz cuadrada: ");
    scanf("%d", &filas);
    cols = filas;

    tmatriz2D *matriz = AsignarMem2D(filas, cols);
    if (matriz == NULL) {
        printf("Error al asignar memoria.\n");
        return -1;
    }

    LeerDatos(matriz);
    printf("Matriz original:\n");
    Visualizar(*matriz);

    Ordenar(matriz);
    printf("\nMatriz ordenada:\n");
    Visualizar(*matriz);

    printf("\nIngrese el valor a buscar: ");
    scanf("%d", &valor);

    BusquedaBinaria(matriz, valor);

    LiberarMem2D(*matriz);
    free(matriz);
    return 0;
}
