#include <stdio.h>

int main()
{
    int c = 0;
    int prev = 0;

    printf("Escribe texto: \n");
    while ((c = getchar()) != EOF)
    {
        if (c == '\t')
        {
            printf("\\t");
        } else if (c == '\b')
        {
            printf("\\b");
        } else if (c == '\\')
        {
            printf("\\\\");
        } else
        {
            putchar(c);
        }
    }
    return 0;
}