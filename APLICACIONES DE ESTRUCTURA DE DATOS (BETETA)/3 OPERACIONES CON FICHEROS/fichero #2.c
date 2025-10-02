#include <stdio.h>

int main() {
    FILE* archivo;
    char nombreArchivo[] = "SALIDA.TXT";
    char *linea = (char *)malloc(100 * sizeof(char));
    if(linea == NULL){
        printf("error al asignar memoria\n");
        exit(1);
    }
    

    int contadorLineas = 0;

    archivo = fopen("C:\\Users\\kelvin_k024\\Desktop\\CUARTO SEMESTRE\\APLICACIONES DE ESTRUCTURA DE DATOS (BETETA)\\APLICACIONES-BETETA\\3 OPERACIONES CON FICHEROS\\SALIDA.TXT", "r");
    if (archivo == NULL) 
    {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        contadorLineas++;
    }

    printf("La cantidad total de lineas en el archivo es de %d\n", contadorLineas);

    fclose(archivo);
    free(linea);

    return 0;
}