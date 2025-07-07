#include <stdio.h>

int main()
{
    int c = 0;
    int prev = 0;

    printf("Escribe texto: \n");
    while ((c = getchar()) != EOF)
    {
        if (c != ' ')
        {
            putchar(c);
            prev = c;
        } else
        {
            if (prev != ' ')
            {
                putchar(prev);
            }
            prev = c;
        }
    }

    return 0;
}