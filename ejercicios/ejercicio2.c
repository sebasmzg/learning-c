#include <stdio.h>
#include <stdlib.h>
/*
1. Pregunte al usuario el tamaño deseado para un array de enteros.
2. **Asigne dinámicamente** memoria para este array usando `malloc`.
3. Verifique si la asignación de memoria fue exitosa. Si no, imprime un error y sal del programa.
4. Pida al usuario que ingrese los elementos del array, uno por uno.
5. **Imprime** todos los elementos del array.
6. **Redimensiona** el array para que sea el doble de su tamaño original usando `realloc`.
7. Verifica si la redimensión fue exitosa. Si no, imprime un error y sal del programa.
8. Pide al usuario que ingrese los nuevos elementos para la parte extendida del array.
9. **mprime** todos los elementos del array redimensionado.
10. **Libera** la memoria asignada dinámicamente usando `free`.
 */

int main()
{
 int size;
 int *array;
 // a
 printf("Ingrese el tamaño de la lista de enteros:\n");
 scanf("%d", &size);
 // b
 array = (int*) malloc(size * sizeof(int));
 // c
 if (array == NULL)
 {
  printf("No se pudo alocar memoria\n");
  return 1;
 }
// d
 printf("Ingrese los elementos de la lista:\n");
 for (int i = 0; i < size; i++)
 {
  scanf("%d", &array[i]);
 }
 // e
 printf("Elementos de la lista:\n");
 for (int i = 0; i < size; i++)
 {
  printf("| %d ", array[i]);
 }
 // f
 int size2 = size * 2;
 int *temp_array = (int *) realloc(array, size2 * sizeof(int));
 // g
 if (temp_array == NULL)
 {
  printf("No se pudo realocar memoria\n");
  free(array);
  return 1;
 }
 array = temp_array;
 printf("\nMemoria reasignada a %d enteros.\n",size2);
 printf("Ingresa los nuevos elementos de la lista:\n");
 // h
 for (int i = size; i < size2; i++)
 {
  scanf("%d",&array[i]);
 }
 // i
 printf("Elementos de la nueva lista:\n");
 for (int i = 0; i < size2; i++)
 {
  printf("| %d ", array[i]);
 }
 // j
 free(array);
 array = NULL;
 return 0;
}