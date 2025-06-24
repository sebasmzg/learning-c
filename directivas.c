#include <stdio.h>
#define pi 3.14
#define cubo(a) a*a*a

main()
{
    int suma = pi + cubo(2);
    printf("El resultado es: %d \n", suma);
}
