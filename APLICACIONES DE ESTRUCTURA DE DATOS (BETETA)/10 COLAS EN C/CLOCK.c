#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

/*#define MAX_MARCOS 10
#define MAX_PAGINAS 100

typedef struct {
    int pagina;
    bool bitUso;
} Marco;

// funciones a utilizar
void algoritmoClock(int paginas[], int longitud, int capacidad);
void imprimirTabla(int tabla[MAX_MARCOS][MAX_PAGINAS], int capacidad, int longitud, int paginas[], int fallos, double tiempoCPU, double tiempoReal, int escrituras);
int main();

void algoritmoClock(int paginas[], int longitud, int capacidad)
{
    Marco marcos[MAX_MARCOS];
    int tabla[MAX_MARCOS][MAX_PAGINAS];
    int puntero = 0;
    int fallos = 0;
    int escrituras = 0;

    clock_t inicioCPU = clock();

    struct timeval inicioReal, finReal;
    gettimeofday(&inicioReal, NULL);

    for (int i = 0; i < capacidad; i++)
    {
        marcos[i].pagina = -1;
        marcos[i].bitUso = false;
    }

    for (int i = 0; i < capacidad; i++)
    {
        for (int j = 0; j < longitud; j++)
        {
            tabla[i][j] = -1;
        }
    }
        
            

    for (int t = 0; t < longitud; t++) 
    {
        int paginaActual = paginas[t];
        bool encontrada = false;

        for (int j = 0; j < capacidad; j++)
        {
            if (marcos[j].pagina == paginaActual) 
            {
                marcos[j].bitUso = true;
                encontrada = true;
                break;
            }
        }

        if (!encontrada) {
            fallos++;
            escrituras++;

            while (true)
            {
                if (!marcos[puntero].bitUso)
                {
                    marcos[puntero].pagina = paginaActual;
                    marcos[puntero].bitUso = true;
                    puntero = (puntero + 1) % capacidad;
                    break;
                } 
                else
                {
                    marcos[puntero].bitUso = false;
                    puntero = (puntero + 1) % capacidad;
                }
            }
        }

        for (int i = 0; i < capacidad; i++) 
        {
            tabla[i][t] = marcos[i].pagina;
        }
    }

    clock_t finCPU = clock();
    gettimeofday(&finReal, NULL);

    double tiempoCPU = (double)(finCPU - inicioCPU) / CLOCKS_PER_SEC;
    double tiempoReal = (finReal.tv_sec - inicioReal.tv_sec) + (finReal.tv_usec - inicioReal.tv_usec) / 1000000.0;

    imprimirTabla(tabla, capacidad, longitud, paginas, fallos, tiempoCPU, tiempoReal, escrituras);
}

void imprimirTabla(int tabla[MAX_MARCOS][MAX_PAGINAS], int capacidad, int longitud, int paginas[], int fallos, double tiempoCPU, double tiempoReal, int escrituras) 
{
    printf("\t === SIMULACION DEL CLOCK ===\n");
    printf("\nTRAZA:\n");
    for (int i = 0; i < longitud; i++) 
    {
        printf("%2d ", paginas[i]);
    }
    printf("\n");
    printf("==================================================================\n");

    for (int i = 0; i < capacidad; i++) 
    {
        for (int j = 0; j < longitud; j++) 
        {
            if (tabla[i][j] == -1)
            {
                printf("   ");
            }
            else
            {
                printf("%2d ", tabla[i][j]);
            }
        }
        printf("\n");
    }

    double tasaFallos = (double)fallos / longitud * 100.0;
    double usoCPU = (tiempoReal > 0) ? (tiempoCPU / tiempoReal * 100.0) : 0;

    printf("\n");
    printf("\t=== RESULTADO DE SIMULACION ===\n");
    printf("total de acceso:             %d\n", longitud);
    printf("fallos de paginas:           %d\n", fallos);
    printf("tasa de fallo:               %.2f%%\n", tasaFallos);
    printf("escritura en disco:          %d\n", escrituras);
    printf("tiempo de cpu utilizado:     %.2f segundos\n", tiempoCPU);
    printf("tiempo real utilizado:       %.2f segundos\n", tiempoReal);
    printf("utilizacion real de la cpu:  %.2f%%\n", usoCPU);
    printf("\n\n");
}

int main() {
    int paginas[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int longitud = sizeof(paginas) / sizeof(paginas[0]);
    int capacidad = 3;

    algoritmoClock(paginas, longitud, capacidad);
    return 0;
}*/


/*int main(){
	int arreglo[7] = {1,2,3,4,5,6,7};
	int i, temp, j;
	
	printf("arreglo aoriginal");
	for(i=0; i<7; i++){
		printf("%d", arreglo[i]);
	}
	 printf("\n");
	 
	for(int i = 0, j=6; i<j; i++, j--){
		temp = arreglo[i];
		
		arreglo[i] = arreglo[j];
		arreglo[j] =  temp;		
	}
	/*printf("%d", arreglo[i]);
	for (i = 0; i<7/2; i++){
		temp = arreglo[i];
		
		arreglo[i] = arreglo[6-i];
		arreglo[6-i]= temp;
	}
	
	printf("arreglo invertido");
	
	for(i=0; i<7; i++){
		printf("%d", arreglo[i]);
	}
	
	printf("\n");
	
	return 0;
}*/




/*#define tamanio 10


int main(){
	int notas[tamanio];
	
	int suma = 0, max, min;
	
	int nota, resultado;
	
	for(int i = 0; i<tamanio; i++){
		while(1){
			printf("ingrrese la nota de estudfiante %d", i+1);
			
			resultado = scanf("%d", &nota);
			
			if(resultado != 1 || nota <0 || nota > 100){
				printf("entrada invalida ingrese entre 0 y 100 \n");
				
				while(getchar() ! = "\n");
			}else{
				notas[i]= notas;
				suma +=nota;
				
				if( i == 0) max =  min = nota;
				
				else{
					if(nota>max) max = nota;
					if(nota<min) min = nota;
				}
				break;
			}
		}
	}
	
	float proedio = suma / (float ) tamanio;
	
	printf("el promedio de notas es = %2f\n", %promedio);
	
	printf("nota alta:  %d\n", max);
	printf("nota mas baja %d", min);
	
	return 0;
	}*/