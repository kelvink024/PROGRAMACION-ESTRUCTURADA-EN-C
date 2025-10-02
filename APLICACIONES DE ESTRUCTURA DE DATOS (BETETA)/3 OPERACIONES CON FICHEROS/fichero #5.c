#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int dia;
    int mes;
    int anno;
} fecha;

typedef struct {
    char nombre[80];
    char calle[80];
    char ciudad[80];
    int cuen_no;
    char cuen_tipo;
    float anteriorsaldo;
    float nuevosaldo;
    float pago;
    fecha ultimopago;
} registro;

registro leerpantalla();
void escribirarchivo(registro cliente, FILE *fpt);
void mostrararchivo(FILE *fpt);

int main() {
    FILE *fpt;
    registro cliente;
    char *continuar=(char*)calloc(4,sizeof(char));
    if(continuar == NULL){
        printf("error al asignar memoria\n");
        exit(1);
    }

    fpt = fopen("C:\\Users\\kelvin_k024\\Desktop\\CUARTO SEMESTRE\\APLICACIONES DE ESTRUCTURA DE DATOS (BETETA)\\APLICACIONES-BETETA\\3 OPERACIONES CON FICHEROS\\DATOS_ESTRUCTURA.TXT", "a");
    if (fpt == NULL) {
        perror("Error al abrir el archivo");
        return EXIT_FAILURE;
    }

    printf("SISTEMA DE CUENTA DE CLIENTES - INICIALIZACION\n\n");

    while (1) {
        cliente = leerpantalla();
        if (strcmp(cliente.nombre, "FIN") == 0) {
            break;
        }
        escribirarchivo(cliente, fpt);
        printf("¿Desea ingresar otro cliente? (S/N): ");
        scanf("%3s", continuar);
        continuar[3] = '\0';  // Asegurar que el string esté terminado en nulo
        if (strcasecmp(continuar, "N") == 0) {
            break;
        }
    }

    fclose(fpt);

    fpt = fopen("C:\\Users\\kelvin_k024\\Desktop\\CUARTO SEMESTRE EN C\\APLICACIONES-BETETA\\3 OPERACIONES CON FICHEROS\\DATOS_ESTRUCTURA.TXT", "r");
    if (fpt == NULL) {
        perror("Error al abrir el archivo para lectura");
        return EXIT_FAILURE;
    }

    printf("\nContenido del archivo:\n");
    mostrararchivo(fpt);

    fclose(fpt);
    free(continuar);

    return 0;
}

registro leerpantalla() {
    registro cliente;

    printf("Ingrese nombre del cliente (o 'FIN' para terminar): ");
    scanf(" %[^\n]", cliente.nombre);

    if (strcmp(cliente.nombre, "FIN") == 0) {
        return cliente;
    }

    printf("Ingrese calle: ");
    scanf(" %[^\n]", cliente.calle);

    printf("Ingrese ciudad: ");
    scanf(" %[^\n]", cliente.ciudad);

    printf("Ingrese número de cuenta: ");
    scanf("%d", &cliente.cuen_no);

    do {
        printf("Ingrese tipo de cuenta (C o D): ");
        scanf(" %c", &cliente.cuen_tipo);
        cliente.cuen_tipo = toupper(cliente.cuen_tipo);
    } while (cliente.cuen_tipo != 'C' && cliente.cuen_tipo != 'D');

    printf("Ingrese saldo anterior: ");
    scanf("%f", &cliente.anteriorsaldo);

    printf("Ingrese nuevo saldo: ");
    scanf("%f", &cliente.nuevosaldo);

    printf("Ingrese pago realizado: ");
    scanf("%f", &cliente.pago);

    printf("Ingrese fecha del último pago (dd mm aaaa): ");
    scanf("%d %d %d", &cliente.ultimopago.dia, &cliente.ultimopago.mes, &cliente.ultimopago.anno);

    return cliente;
}

void escribirarchivo(registro cliente, FILE *fpt) {
    fprintf(fpt, "Nombre: %s\n", cliente.nombre);
    fprintf(fpt, "Calle: %s\n", cliente.calle);
    fprintf(fpt, "Ciudad: %s\n", cliente.ciudad);
    fprintf(fpt, "Número de cuenta: %d\n", cliente.cuen_no);
    fprintf(fpt, "Tipo de cuenta: %c\n", cliente.cuen_tipo);
    fprintf(fpt, "Saldo anterior: %.2f\n", cliente.anteriorsaldo);
    fprintf(fpt, "Nuevo saldo: %.2f\n", cliente.nuevosaldo);
    fprintf(fpt, "Pago realizado: %.2f\n", cliente.pago);
    fprintf(fpt, "Fecha del último pago: %d/%d/%d\n", cliente.ultimopago.dia, cliente.ultimopago.mes, cliente.ultimopago.anno);
    fprintf(fpt, "-----------------------------------------\n");
}

void mostrararchivo(FILE *fpt) {
    char *buffer = (char *)malloc(256 * sizeof(char));
    if(buffer == NULL){
        printf("error al asignarle memoria\n");
        exit(1);
    }

    while (fgets(buffer, sizeof(buffer), fpt) != NULL) {
        printf("%s", buffer);
    }
    free(buffer);
}