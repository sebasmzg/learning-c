#include <stdio.h>

main()
{
    int num1, num2, result;
    printf("Ingrese el primer valor: \n");
    scanf("%d", &num1); /* el & es un operador de dirección, ruta donde se almacenará el valor*/
    printf("Ingrese el segundo valor: \n");
    scanf("%d", &num2);
    result = num1 + num2;
    printf("El resultado es: %d \n", result);
}