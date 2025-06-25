#include <stdio.h>
#include <stdlib.h>

int main()
{
   int *numeros;
   int cantidad = 5;

   //asignar memoria para 5 enteros (5 * tamaño de un int)
   numeros = (int *) malloc(cantidad * sizeof(int));

   // ***** verificar asignación *****
   if (numeros == NULL)
   {
      printf("Error: No se pudo asignar memoria con malloc. \n");
      return 1;
   }

   // Llenar la memoria (porque malloc no la inicializa)
   printf("Inicializando memoria asignada con malloc:\n");
   for (int i= 0; i < cantidad; i++)
   {
      numeros[i] = (i + 1) * 10;
      printf("%d ", numeros[i]);
   }
   printf("\n");

   // ... Usar 'numeros' ...

   // ****** Liberar memoria ********
   free(numeros);
   numeros = NULL;

   return 0;
}