#include <stdio.h>
#include <stdlib.h>

struct racional
{
    int numerador;
    int denominador;
};

typedef struct racional fraccion;


fraccion* sumar_facciones(fraccion f1, fraccion f2);
fraccion* restar_fracciones(fraccion f1, fraccion f2);
fraccion* multiplicar_fracciones(fraccion f1, fraccion f2);

fraccion* sumar_facciones(fraccion f1, fraccion f2)
{
    fraccion* resultado = (fraccion*)malloc(sizeof(fraccion));
    if (resultado == NULL)
    {
        printf("error al asignar memoria\n");
        exit(1);
    }
    resultado->numerador = (f1.numerador * f2.denominador) + (f2.numerador * f1.denominador);
    resultado->denominador = f1.denominador * f2.denominador;
    return resultado;
}

fraccion* restar_fracciones(fraccion f1, fraccion f2)
{
    fraccion* resultado = (fraccion*)malloc(sizeof(fraccion));
    if (resultado == NULL)
    {
        printf("error al asignar memoria\n");
        exit(1);
    }
    resultado->numerador = (f1.numerador * f2.denominador) - (f2.numerador * f1.denominador);
    resultado->denominador = f1.denominador * f2.denominador;
    return resultado;
}


fraccion* multiplicar_fracciones(fraccion f1, fraccion f2)
{
    fraccion* resultado = (fraccion*)malloc(sizeof(fraccion));
    if (resultado == NULL)
    {
        printf("error al asignar memoria\n");
        exit(1);
    }
    resultado->numerador = f1.numerador * f2.numerador;
    resultado->denominador = f1.denominador * f2.denominador;
    return resultado;
}


int maximo_comun_divisor(int a, int b) {
    int temporal;
    while (b != 0) {
        temporal = b;
        b = a % b;
        a = temporal;
    }
    return a;
}

void simplificar_fracc (fraccion *resultado){
	int  mcd;
	
    mcd = maximo_comun_divisor(resultado->numerador,resultado->denominador);

	resultado->numerador/=mcd;
	
	resultado->denominador/=mcd;
}

int main()
{
    char operacion;
    fraccion f1, f2;
    fraccion* resultado;

    printf("\ningrese los datos de la primera fraccion\n");

    printf("ingresa el numerador: ");
    scanf("%d", &f1.numerador);

    printf("ahora ingresa el denominador: ");
    scanf("%d", &f1.denominador);
    if (f1.denominador == 0)
    {
        printf("el denominador no puede ser cero\n");
        return 1;
    }

    printf("\nahora ingresa los datos de la segunda fraccion\n");
    
    printf("ingresa el numerador: ");
    scanf("%d", &f2.numerador);

    printf("ahora ingresa el denominador: ");
    scanf("%d", &f2.denominador);
    if (f2.denominador == 0)
    {
        printf("el denominador no puede ser cero\n");
        return 1;
    }

    printf("Seleccione la operacion:\n");
    printf(" S para sumar\n");
    printf(" R para restar\n");
    printf(" M para multiplicar\n");
    scanf(" %c", &operacion);

    switch (operacion) {
        case 's':
            resultado = sumar_facciones(f1, f2);
            simplificar_fracc(resultado);
            if(resultado->numerador % resultado->denominador == 0){
                int datos_exacto = resultado->numerador / resultado->denominador;
                printf("el resultado de la suma de fracciones es: %d\n", datos_exacto);
                exit(1);
            }
            printf("la suma de las fracciones es: %d/%d\n", resultado->numerador, resultado->denominador);
            free(resultado);
            break;
        case 'r':
            resultado = restar_fracciones(f1, f2);
            simplificar_fracc(resultado);
            if(resultado->numerador % resultado->denominador == 0){
                int datos_exacto = resultado->numerador / resultado->denominador;
                printf("el resultado de la suma de fracciones es: %d\n", datos_exacto);
                exit(1);
            }
            printf("la resta de las fracciones es: %d/%d\n", resultado->numerador, resultado->denominador);
            free(resultado);
            break;
        case 'm':
            resultado = multiplicar_fracciones(f1, f2);
            simplificar_fracc(resultado);
            if(resultado->numerador % resultado->denominador == 0){
                int datos_exacto = resultado->numerador / resultado->denominador;
                printf("el resultado de la suma de fracciones es: %d\n", datos_exacto);
                exit(1);
            }
            printf("el producto de las fracciones es: %d/%d\n", resultado->numerador, resultado->denominador);
            free(resultado);
            break;
        default:
            printf("parametro inválido.\n");
    }

    return 0;
}
