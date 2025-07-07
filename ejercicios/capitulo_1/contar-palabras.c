#include <stdio.h>
#define IN 1
#define OUT 0

/* Cuenta lineas, palabras y caracteres de la entrada */
int main()
{
    int c, nl, nw, nc, state;

    state = OUT;
    nw = nc = 0;
    nl = 1;

    printf("Escriba el texto: \n");
    while ((c = getchar()) != EOF)
    {
        nc++;
        if (c == '\n')
        {
            nl++;
        }
        if (c == ' ' || c == '\n' || c == '\t')
        {
            state = OUT;
        } else if (state == OUT)
        {
            state = IN;
            nw++;
        }
    }

    printf("\nlineas: %d\npalabras: %d\ncaracteres: %d\n", nl, nw, nc);

    return 0;
}