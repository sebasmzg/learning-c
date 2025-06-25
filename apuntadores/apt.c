#include <stdio.h>

//apuntador es una variable cuyo valor son direcciones de memoria

void cubo(int *n);

main()
{
   int a = 2;
   int *apt = &a;

    int num = 5;
    printf("num: %i\n", num);
    cubo(&num);
    printf("num al cubo: %i\n", num);

   printf("valor: %i\n", *apt);
   printf("Ubicación memoria en hexadecimal: %p\n", apt);  //%p ubicacion en memoria como entero hexadecimal
}

/*
 * Llamadas a funciones por referencia
 */

void cubo(int *n)
{
    *n = *n * *n * *n;
}