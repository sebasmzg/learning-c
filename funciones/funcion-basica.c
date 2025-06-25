#include <stdio.h>

void Saludo(char *nombre)
{
    printf("Hola %s\n", nombre);
    return;
}

main()
{
    Saludo("sebas");
}