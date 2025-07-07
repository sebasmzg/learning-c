#include <stdio.h>

int main()
{
    int c;
    printf("Escriba algo y presione Ctrl+D (en Linux/mac) o Ctrl+Z (en Windows) para finalizar:\n");

    while ((c = getchar()) != EOF)
    {
        printf("Resultado de (getchar() != EOF): %d\n", c != EOF);
    }

    return 0;
}