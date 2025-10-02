#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define MAX_MARCOS 10
#define MAX_PAGINAS 100
#define REPETICIONES 100000

typedef struct {
    int marcos[MAX_MARCOS];
    int capacidad;
    int cantidad_marcos;
    int primero;
} SistemaFIFO;


// funciones a utilizar
void inicializarFIFO(SistemaFIFO *sistema, int capacidad);
bool paginaEnMemoria(SistemaFIFO *sistema, int capacidad);
void tablaDeMarcos(SistemaFIFO *sistema, int capacidad);
void simularFIFOConTrazaFija();
int main();

void inicializarFIFO(SistemaFIFO *sistema, int capacidad) {
    sistema->capacidad = capacidad;
    sistema->cantidad_marcos = 0;
    sistema->primero = 0;
}

bool paginaEnMemoria(SistemaFIFO *sistema, int pagina) {
    for (int i = 0; i < sistema->cantidad_marcos; i++) {
        if (sistema->marcos[i] == pagina) {
            return true;
        }
    }
    return false;
}

void tablaDeMarcos(SistemaFIFO *sistemaOriginal, int traza[], int longitud_traza) {
    int tabla[MAX_MARCOS][MAX_PAGINAS];
    int cantidad_marcos = sistemaOriginal->capacidad;

    for (int i = 0; i < cantidad_marcos; i++) {
        for (int j = 0; j < longitud_traza; j++) {
            tabla[i][j] = -1;
        }
    }

    SistemaFIFO sistema;
    inicializarFIFO(&sistema, sistemaOriginal->capacidad);

    for (int t = 0; t < longitud_traza; t++) {
        int pagina = traza[t];
        if (!paginaEnMemoria(&sistema, pagina)) {
            if (sistema.cantidad_marcos < sistema.capacidad) {
                sistema.marcos[sistema.cantidad_marcos++] = pagina;
            } else {
                sistema.marcos[sistema.primero] = pagina;
                sistema.primero = (sistema.primero + 1) % sistema.capacidad;
            }
        }

        for (int m = 0; m < sistema.cantidad_marcos; m++) {
            tabla[m][t] = sistema.marcos[m];
        }
    }

    printf("\t === SIMULACION DEL FIFO ===\n");
    printf("\nTRAZA:\n");
    for (int t = 0; t < longitud_traza; t++) {
        printf("%2d ", traza[t]);
    }
    printf("\n\n==================================================================\n");

    for (int i = 0; i < cantidad_marcos; i++) {
        for (int j = 0; j < longitud_traza; j++) {
            if (tabla[i][j] == -1) {
                printf(" . ");
            } else {
                printf("%2d ", tabla[i][j]);
            }
        }
        printf("\n");
    }
}

void simularFIFOConTrazaFija() {
    SistemaFIFO sistema;
    int traza[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int longitud_traza = sizeof(traza) / sizeof(traza[0]);
    int capacidad_marcos = 3;

    int fallos_totales = 0;
    int escrituras_totales = 0;

    clock_t inicio_cpu = clock();

    for (int rep = 0; rep < REPETICIONES; rep++) {
        inicializarFIFO(&sistema, capacidad_marcos);
        for (int i = 0; i < longitud_traza; i++) {
            int pagina = traza[i];
            if (!paginaEnMemoria(&sistema, pagina)) {
                if (sistema.cantidad_marcos < sistema.capacidad) {
                    sistema.marcos[sistema.cantidad_marcos++] = pagina;
                } else {
                    sistema.marcos[sistema.primero] = pagina;
                    sistema.primero = (sistema.primero + 1) % sistema.capacidad;
                }
                fallos_totales++;
                escrituras_totales++;
            }
        }
    }

    clock_t fin_cpu = clock();
    double tiempo_total = (double)(fin_cpu - inicio_cpu) / CLOCKS_PER_SEC;
    double tiempo_promedio = tiempo_total / REPETICIONES;

    inicializarFIFO(&sistema, capacidad_marcos);
    int fallos_pagina = 0;
    int escrituras_disco = 0;

    for (int i = 0; i < longitud_traza; i++) {
        int pagina = traza[i];
        if (!paginaEnMemoria(&sistema, pagina)) {
            if (sistema.cantidad_marcos < sistema.capacidad) {
                sistema.marcos[sistema.cantidad_marcos++] = pagina;
            } else {
                sistema.marcos[sistema.primero] = pagina;
                sistema.primero = (sistema.primero + 1) % sistema.capacidad;
            }
            fallos_pagina++;
            escrituras_disco++;
        }
    }

    tablaDeMarcos(&sistema, traza, longitud_traza);

    int total_accesos = longitud_traza;
    int aciertos = total_accesos - fallos_pagina;
    float tasa_fallos = ((float)fallos_pagina / total_accesos) * 100;
    float uso_cpu = ((float)aciertos / total_accesos) * 100;

    printf("\n\t === RESULTADO DE SIMULACION ===\n");
    printf("total de acceso:            %d\n", total_accesos);
    printf("fallos de paginas:          %d\n", fallos_pagina);
    printf("tasa de fallo:              %.2f%%\n", tasa_fallos);
    printf("escritura en disco:         %d\n", escrituras_disco);
    printf("tiempo total de ejecucion:  %.6f segundos\n", tiempo_promedio);
    printf("uso estimado de CPU:        %.2f%%\n", uso_cpu);
}

int main() {
    simularFIFOConTrazaFija();
    return 0;
}
