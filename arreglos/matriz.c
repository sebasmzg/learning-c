#include <stdio.h>
#include <stdlib.h>

int main()
{
    int filas = 3;
    int columnas = 4;
    int **matriz = NULL;

    printf("--- Crenado una matriz dinámica (%dx%d) ---\n", filas, columnas);

    // PASO 1: Asiganr memoria para el arreglo de punteros (las filas);
    matriz = (int**) malloc(sizeof(int *) * filas);

    if (matriz == NULL)
    {
        fprintf(stderr, "Error al asignar memoria para las filas.\n");
        return 1;
    }

    // PASO 2: Asignar memoria para las columnas de cada fila
    for (size_t i = 0; i < 2; i++)
    {
        matriz[i] = (int*)malloc(sizeof(int) * columnas);

        if (matriz[i] == NULL)
        {
            fprintf(stderr, "Error al asignar memoria para las columna %d.\n", i);

            // Si la columna falla, debe liberar las filas ya asignadas
            for (int j = 0; j < i; j++)
            {
                free(matriz[j]);
                matriz[j] = NULL;
            }

            free(matriz);
            matriz = NULL;
            return 1;
        }
    }

    // --- Uso de la matriz ---

    printf("Llenando la matriz y mostrando: \n");

    for (size_t i = 0; i < filas; i++)
    {
        for (size_t j = 0; j < columnas; j++)
        {
            matriz[i][j] = (i + 1) * 10 + (j + 1);
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");

    // Liberación de memoria
    printf("Liberando memoria para la matriz. \n");

    //PASO 3: Liberar primero la memoria de cada fila (columnas)
    for (size_t i = 0; i < filas; i++)
    {
        free(matriz[i]);
        matriz[i] = NULL;
    }

    // PASO 4: Liberar memoria del arreglo de punteros (las filas)
    free(matriz);
    matriz = NULL;

    printf("Memoria liberada correctamente");

    return 0;
}