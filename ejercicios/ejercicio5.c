#include <stdio.h>
#include  <stdlib.h>
#include <string.h>

int* crear(int n)
{
    int* array = (int*) calloc (n,sizeof(int));
    if (array == NULL)
    {
        printf("Error al asignar memoria al array.\n");
        return NULL;
    }
    return array;
}
void asignar(int** arr, int* n, int index, int valor)
{
    if (*arr == NULL || index < 0 || index >= *n)
    {
        printf("Error: indice invàlido.\n");
        return;
    }
    (*arr)[index] = valor;
}
void insertar(int** arr, int* n, int valor)
{
    (*n)++;
    int* nuevo_arr = (int*) realloc(*arr,(*n)*sizeof(int));
    if (nuevo_arr == NULL)
    {
        printf("Error al expandir memoria al array.\n");
        (*n)--;
        return;
    }
    *arr = nuevo_arr;
    (*arr)[*n - 1] = valor;
}
void eliminar(int** arr, int* n, int index)
{
    if (*arr == NULL || index < 0 || index >= *n)
    {
        printf("Error: indice inválido.\n");
        return;
    }
    for (int i = index; i < *n -1; i++)
    {
        (*arr)[i] = (*arr)[i+1];
    }
    (*n)--;
    if (*n == 0)
    {
        free(*arr);
        *arr = NULL;
        return;
    }

    int* nuevo_arr = (int*) realloc(*arr,(*n)*sizeof(int));
    if (nuevo_arr == NULL)
    {
        printf("Error al alocar memoria al array.\n");
        (*n)++;
        return;
    }
    *arr = nuevo_arr;
}
void imprimir(int* arr, int n)
{
    if (arr == NULL) {
        printf("Lista: []\n");
        return;
    }
    printf("Lista: [");
    for (int i = 0; i < n; i++)
    {
        printf("%d", arr[i]);
        if (i != n -1)
        {
            printf(", ");
        }
    }
    printf("]\n");
}

int main()
{
    int n = 5;
    int* arr = crear(n);
    imprimir(arr,n);

    printf("asignar 5 a indice 0\n");
    asignar(&arr, &n, 0, 5);
    imprimir(arr,n);

    printf("insertar 2\n");
    insertar(&arr, &n, 2);
    imprimir(arr,n);

    printf("insertar 3\n");
    insertar(&arr, &n, 3);
    imprimir(arr,n);

    printf("insertar 4\n");
    insertar(&arr, &n, 4);
    imprimir(arr,n);

    printf("insertar 1\n");
    insertar(&arr, &n, 1);
    imprimir(arr, n);

    printf("eliminar indice 1\n");
    eliminar(&arr, &n, 1);
    imprimir(arr, n);

    printf("eliminar indice 0\n");
    eliminar(&arr, &n, 0);
    imprimir(arr, n);

    free(arr);

    return 0;
}