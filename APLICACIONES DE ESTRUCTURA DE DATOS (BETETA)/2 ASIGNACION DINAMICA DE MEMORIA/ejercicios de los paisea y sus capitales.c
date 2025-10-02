#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define tamanio 100

void convertir_minusculas(char *cadena) {
    for (int i = 0; cadena[i]; i++) {
        cadena[i] = tolower(cadena[i]);
    }
}

int main() {
    int i, num_paises;
    char buscar_pais[tamanio];

    printf("cuantos paises deseas que esten dentro de la lista: ");
    scanf("%d", &num_paises);
    getchar();

    printf("\n\n");

    char **paises = (char **)malloc(num_paises * sizeof(char *));
    char **capitales = (char **)malloc(num_paises * sizeof(char *));
    if (paises == NULL || capitales == NULL) {
        printf("error al asignar memoria\n");
        return 1;
    }

    for (i = 0; i < num_paises; i++) {
        paises[i] = (char *)malloc(tamanio * sizeof(char));
        capitales[i] = (char *)malloc(tamanio * sizeof(char));
        if (paises[i] == NULL || capitales[i] == NULL) {
            printf("error al asignar memoria\n");
            return 1;
        }

        printf("ingresa el nombre del pais %d que deseas agregar: ", i + 1);
        fgets(paises[i], tamanio, stdin);
        strtok(paises[i], "\n");

        printf("ahora ingresa la capital del pais %s: ", paises[i]);
        fgets(capitales[i], tamanio, stdin);
        strtok(capitales[i], "\n");

        printf("\n");
    }

    system("cls");

    do {
        int pais_encontrado = 0;

        printf("ingrese el nombre del pais que desea saber su capital o fin para terminar: ");
        fgets(buscar_pais, tamanio, stdin);
        strtok(buscar_pais, "\n");

        if (strcmp(buscar_pais, "fin") == 0)
        {
            break;
        }

        convertir_minusculas(buscar_pais);

        for (i = 0; i < num_paises; i++) 
        {
            char pais_minusculas[tamanio];
            strcpy(pais_minusculas, paises[i]);

            convertir_minusculas(pais_minusculas);

            if (strcmp(buscar_pais, pais_minusculas) == 0) 
            {
                printf("la capital de %s es %s.\n", paises[i], capitales[i]);
                pais_encontrado = 1;
                break;
            }
        }

        if (!pais_encontrado) 
        {
            printf("pais no encontrado\n");
        }

    } while(1);

    for (i = 0; i < num_paises; i++) 
    {
        free(paises[i]);
        free(capitales[i]);
    }
    free(paises);
    free(capitales);

    return 0;
}
