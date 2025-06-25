#include <stdio.h>

 size_t getSize(float *ptr)
 {
     return sizeof(ptr);
 }

main()
{
    float array[20];
    printf("Numero de bytes en arreglo es: %lu\n", sizeof(array)); //%lu => long unsigned

     printf("numero de bytes devuektos por getsize es: %lu\n", getSize(array    ));
}