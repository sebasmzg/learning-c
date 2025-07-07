#include <stdio.h>
#define IN 1
#define OUT 2

int main()
{
    int c = 0;
    int state = OUT;
    printf("Escribe texto: \n");
    while ((c = getchar()) != EOF)
    {
        if (c == '\n' || c == '\t' || c == ' ')
        {
            if (state == IN)
            {
                putchar('\n');
                state = OUT;
            }
        } else
        {
            state = IN;
            putchar(c);
        }
    }

    return 0;
}