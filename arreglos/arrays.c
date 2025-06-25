#include <stdio.h>

main()
{
    /*
     int array[4] = {1, 2, 3, 4};
    printf("%i\n",array[2]);
    */
    /*
    int sizeA;
    printf("Ingrese el tamaño del arreglo:\n");
    scanf("%i", &sizeA);

    int age[sizeA];

    for (int i=0; i < sizeA; i++)
    {
        printf("Ingresa el valor %i:\n", i+1);
        scanf("%i", &age[i]);
    }

    printf("Valores del arreglo:\n");
    for (int i=0; i < sizeA; i++)
    {
        printf("%i\n", age[i]);
    */

    /* Arreglo multidimensional */
    int multi[2][3] = {{5, 3, 1},{6,4,2}};
    //col...0 1 2
    //fila0|5 3 1
    //fila1|6 4 2

    printf("col 0, fila 0: %i\ncol 2, fila 1: %i\n", multi[0][0], multi[1][2]);
}
