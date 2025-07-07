#include <stdio.h>

#define IN 1
#define OUT 0

int main()
{
    int c= 0;
    int current_length = 0;
    int state = OUT;

    printf("Escribe las palabras: \n");

    while ((c =getchar()) != EOF)
    {
        if (c == ' ' || c == '\n' || c == '\t') // si hay espacios en blanco
        {
            if (state == IN) // si estoy adentro de una palabra
            {
                for (int i = 0; i < current_length; i++)
                {
                    //putchar('\n');
                    putchar('*'); // imprimir * en lugar de los caracteres de la plaabra
                }
                putchar('\n');
                current_length = 0; // reinicio el contador de caracteres de la palabra
            }
            state = OUT; // indica que salgo de la plabra
        } else
        {
            state = IN; // entro auna palabra
            ++current_length; // incremento el contador de caracteres de la palabra
        }
    }

    return 0;
}
