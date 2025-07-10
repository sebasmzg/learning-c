#include <stdio.h>
#include <stdlib.h>
#define CAPACIDAD_MAX 10
/*
* implementa las siguientes funciones para un array estático de enteros, simulando una lista de capacidad limitada.
void imprimir_array(int arr[], int tam_logico): Imprime los elementos válidos.
int buscar_elemento(int arr[], int tam_logico, int elemento): Busca un elemento y retorna su índice, o -1 si no lo encuentra.
int insertar_elemento(int arr[], int *tam_logico, int capacidad_max, int elemento, int posicion): Inserta un elemento en una posición dada. Retorna 0 si es exitoso, -1 si el array está lleno o la posición es inválida. Desplaza los elementos existentes.
int eliminar_elemento(int arr[], int *tam_logico, int posicion): Elimina un elemento en una posición dada. Retorna 0 si es exitoso, -1 si la posición es inválida. Desplaza los elementos restantes.
void ordenar_array(int arr[], int tam_logico): Ordena el array usando la función qsort de stdlib.h.

En tu main, demuestra el uso de estas funciones:
1. Inicializa un array de int de CAPACIDAD_MAX = 10 y un tam_logico = 0.
2. Inserta algunos elementos.
3. Busca un elemento.
4. Elimina un elemento.
5. Inserta otro elemento.
6. Ordena el array.
7. Imprime el array después de cada operación significativa.
 */
void imprimir_array(int arr[], int tam_logico)
{
    if (tam_logico == 0)
    {
        printf("Array vacío\n");
        return;
    }

    printf("Array: [");
    for (int i = 0; i < tam_logico; i++)
    {
        printf("%d", arr[i]);
        if (i < tam_logico - 1)
        {
            printf(", ");
        }
    }
    printf("]");
    printf("\n");
}
int buscar_elemento(int arr[], int tam_logico, int elemento)
{
    for (int i = 0; i < tam_logico; i++)
    {
        if (arr[i] == elemento)
        {
            return i;
        }
    }
    return -1;
}
int insertar_elemento(int arr[], int *tam_logico, int capacidad_max, int elemento, int posicion)
{
    // verificar si esta lleno el array
    if (*tam_logico >= capacidad_max)
    {
        return -1;
    }
    // verificar si la posicion es válida
    if (posicion < 0 || posicion > *tam_logico)
    {
        return -1;
    }
    // Mover elementos a la derecha
    for (int i = *tam_logico; i > posicion; i--)
    {
        arr[i] = arr[i - 1];
    }
    arr[posicion] = elemento;
    (*tam_logico)++;
    return 0;
}
int eliminar_elemento(int arr[], int *tam_logico, int posicion)
{
    // verificar posicion
    if (posicion < 0 || posicion > *tam_logico)
    {
        return -1;
    }
    // Mover elementos a la izquierda
    for (int i = posicion; i < *tam_logico - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
    (*tam_logico)--;
    return 0;
}
int comparar(const void *a, const void *b)
{
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;

    if (int_a < int_b) return -1;
    else if (int_a > int_b) return 1;
    else return 0;
}
void ordenar_array(int arr[], int tam_logico)
{
    qsort(arr, tam_logico, sizeof(int), comparar);
}
int main()
{
    //1. inicializar con capacidad_,max y tam_logico = 0
    int array[CAPACIDAD_MAX];
    int tam_logico = 0;
    printf("Funciones array:\n\n");
    // estado inicial
    printf("1. Estado incial:\n");
    imprimir_array(array, tam_logico);
    printf("\n");

    //insertar elementos
    printf("2. Insertando elementos;\n");
    insertar_elemento(array, &tam_logico, CAPACIDAD_MAX, 50, 0);
    printf("Insertado 50 en posición 0: \n");
    imprimir_array(array, tam_logico);

    insertar_elemento(array, &tam_logico, CAPACIDAD_MAX, 20, 0);
    printf("Insertado 20 en posición 0: \n");
    imprimir_array(array, tam_logico);

    insertar_elemento(array, &tam_logico, CAPACIDAD_MAX, 100, 1);
    printf("Insertado 100 en posición 1: \n");
    imprimir_array(array, tam_logico);

    insertar_elemento(array, &tam_logico, CAPACIDAD_MAX, 80, 2);
    printf("Insertado 80 en posición 2: \n");
    imprimir_array(array, tam_logico);
    printf("\n\n");

    // 3. Buscar elemento
    printf("3. Buscando elementos: \n");
    int pos = buscar_elemento(array, tam_logico, 50);
    if (pos != -1)
    {
        printf("elemento 50 encontrado en posición: %d\n", pos);
    } else
    {
        printf("Elemento 50 no encontrado");
    }

    pos = buscar_elemento(array, tam_logico, 100);
    if (pos != -1) {
        printf("Elemento 100 encontrado en posición: %d\n", pos);
    } else {
        printf("Elemento 100 no encontrado\n");
    }
    printf("\n");

    // 4. Elminar un elemento
    printf("4. Eliminando un elemento en posición 1:\n");
    if (eliminar_elemento(array, &tam_logico, 1) == 0)
    {
        printf("Elemento eliminado exitosamente: \n");
        imprimir_array(array, tam_logico);
    } else
    {
        printf("error al eliminar elemento");
    }
    printf("\n");

    // 5. Insertar otro elemento
    printf("5. Insertando otro elemento 15 en posicion 1:\n");
    if (insertar_elemento(array, &tam_logico, CAPACIDAD_MAX, 15, pos) == -1)
    {
        printf("Elemento insertado exitosamente: \n");
        imprimir_array(array, tam_logico);
    } else
    {
        printf("Error al insertar elemento\n");
    }
    printf("\n");

    // 6. Sort the array
    printf("6. Ordenando el array:\n");
    printf("Antes del ordenamiento: ");
    imprimir_array(array, tam_logico);
    ordenar_array(array, tam_logico);
    printf("Después del ordenamiento: ");
    imprimir_array(array, tam_logico);
    return 0;
}