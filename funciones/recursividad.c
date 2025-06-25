#include <stdio.h>

// ---- Recursividad es llamar a una función dentro de sí misma

long Factorial( long num);

main()
{
    int num;
    printf("Ingresa un numero:");
    scanf("%i", &num);

    printf("Factoriales\n");

    for (int i = 0; i <= num; i++)
    {
        printf("%i: %ld\n", i, Factorial(i));
    }
}

long Factorial(long num)
{
    if (num <= 1)
    {
        return 1;
    } else
    {
        return (num *  Factorial(num - 1));
    }
}
