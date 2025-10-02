#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h> // Para gettimeofday()

#define MAX_MARCOS 10
#define MAX_PAGINAS 100

typedef struct {
    int marcos[MAX_MARCOS];
    int capacidad;
    int cantidad_marcos;
} SistemaLRU;



void inicializarLRU(SistemaLRU *sistema, int capacidad)
{
    sistema->capacidad = capacidad;
    sistema->cantidad_marcos = 0;
}

bool paginaEnMemoria(SistemaLRU *sistema, int pagina)
{
    for (int i = 0; i < sistema->cantidad_marcos; i++) {
        if (sistema->marcos[i] == pagina) {
            return true;
        }
    }
    return false;
}

void actualizarUso(SistemaLRU *sistema, int pagina)
{
    int i;
    for (i = 0; i < sistema->cantidad_marcos; i++) {
        if (sistema->marcos[i] == pagina) {
            break;
        }
    }

    for (; i < sistema->cantidad_marcos - 1; i++) {
        sistema->marcos[i] = sistema->marcos[i + 1];
    }

    sistema->marcos[sistema->cantidad_marcos - 1] = pagina;
}

void simularLRUConTrazaFija()
{
    SistemaLRU sistema;
    int traza[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int longitud_traza = sizeof(traza) / sizeof(traza[0]);
    int capacidad_marcos = 3;

    inicializarLRU(&sistema, capacidad_marcos);

    int fallos_pagina = 0;
    int escrituras = 0;

    clock_t inicioCPU = clock();
    struct timeval inicioReal, finReal;
    gettimeofday(&inicioReal, NULL);

    int tabla[MAX_MARCOS][MAX_PAGINAS];
    for (int i = 0; i < capacidad_marcos; i++) {
        for (int j = 0; j < longitud_traza; j++) {
            tabla[i][j] = -1;
        }
    }

    for (int t = 0; t < longitud_traza; t++) {
        int pagina = traza[t];

        if (paginaEnMemoria(&sistema, pagina)) 
        {
            actualizarUso(&sistema, pagina);
        } 
        
        else 
        {
            if (sistema.cantidad_marcos < sistema.capacidad) {
                sistema.marcos[sistema.cantidad_marcos++] = pagina;
            } else {
                for (int i = 0; i < sistema.capacidad - 1; i++) {
                    sistema.marcos[i] = sistema.marcos[i + 1];
                }
                sistema.marcos[sistema.capacidad - 1] = pagina;
            }

            fallos_pagina++;
            escrituras++; // Se asume una escritura en disco por fallo
        }

        for (int m = 0; m < sistema.cantidad_marcos; m++) {
            tabla[m][t] = sistema.marcos[m];
        }
    }

    clock_t finCPU = clock();
    gettimeofday(&finReal, NULL);

    double tiempoCPU = (double)(finCPU - inicioCPU) / CLOCKS_PER_SEC;
    double tiempoReal = (finReal.tv_sec - inicioReal.tv_sec) + (finReal.tv_usec - inicioReal.tv_usec) / 1000000.0;
    double tasaFallos = (double)fallos_pagina / longitud_traza * 100.0;
    double usoCPU = (tiempoReal > 0) ? (tiempoCPU / tiempoReal * 100.0) : 0;

    // Imprimir tabla y métricas
    printf("\tsimulacion LRU:\n");
    printf("\nTRAZA:\n");
    for (int t = 0; t < longitud_traza; t++) {
        printf("%2d ", traza[t]);
    }
    printf("\n");
    printf("=============================================================\n");

    for (int i = 0; i < capacidad_marcos; i++) {
        for (int j = 0; j < longitud_traza; j++) {
            if (tabla[i][j] == -1) {
                printf("   ");
            } else {
                printf("%2d ", tabla[i][j]);
            }
        }
        printf("\n");
    }

    printf("\n");
    printf("\t=== RESULTADO DE SIMULACION ===\n");
    printf("total de acceso:             %d\n", longitud_traza);
    printf("fallos de paginas:           %d\n", fallos_pagina);
    printf("tasa de fallo:               %.2f%%\n", tasaFallos);
    printf("escritura en disco:          %d\n", escrituras);
    printf("tiempo de cpu utilizado:     %.2f segundos\n", tiempoCPU);
    printf("tiempo real utilizado:       %.2f segundos\n", tiempoReal);
    printf("utilizacion real de la cpu:  %.2f%%\n", usoCPU);
}

int main()
{
    simularLRUConTrazaFija();
    return 0;
}
