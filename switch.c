#include <stdio.h>

main()
{
    int casos;
    printf("Ingresa un numero de 1 a 3: ");
    scanf("%i", &casos);
    switch(casos)
    {
        case 1:
            printf("Elegiste el caso 1\n");
            break;
        case 2:
            printf("Elegiste el caso 2\n");
            break;
        case 3:
            printf("Elegiste el caso 3\n");
            break;
        default:
            break;
    }
}