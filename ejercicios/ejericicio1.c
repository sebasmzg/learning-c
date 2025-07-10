#include <stdio.h>

/*
* 1. Declare un array de enteros llamado numeros de tamaño 5 e inicialízalo con valores a tu elección (ej., {10, 20, 30, 40, 50}). Declara un puntero a entero ptr_numeros y haz que apunte al inicio del array numeros. Utiliza la aritmética de punteros (no la indexación con corchetes []) para:
    1. Imprimir el valor del tercer elemento del array (índice 2).
    2. Modificar el valor del cuarto elemento del array (índice 3) a 99.
    3. Imprimir todos los elementos del array usando un bucle for y aritmética de punteros.
    4. Demuestra cómo puedes obtener el tamaño total del array en bytes y el número de elementos utilizando sizeof.
 */
int main() {
    int numeros[5] = {10,20,30,40,50};
    int *ptr_numeros = numeros;
    printf("lista: 10,20,30,40,50\n\n");
    // 1
    printf("%d",*(ptr_numeros + 2));
    // 2
    *(ptr_numeros + 3) = 99;
    printf("Cuarto elemento transformado a 99\n");
    for (int i = 0; i < 5; i++)
    {
        // 3
        printf("elemento %d: %d | ", i, *(ptr_numeros + i));
    }
    // 4
    printf("\nTamaño total del array en bytes: %zu\n",sizeof(numeros));
    printf("Tamaño de un elemento en bytes: %zu\n", sizeof(int));
    printf("Número de elementos: %zu\n", sizeof(numeros)/sizeof(int));
    return 0;
}