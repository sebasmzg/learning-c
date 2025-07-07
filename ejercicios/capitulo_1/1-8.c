#include <stdio.h>

int main()
{
    int c;
    int blanks = 0;
    int tabs = 0;
    int nl = 0;

    printf("Escribe texto: \n");
    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
        {
            blanks++;
        }
        if (c == '\t')
        {
            tabs++;
        }
        if (c == '\n')
        {
            nl++;
        }
    }

    printf("\nBlanks: %d\n", blanks);
    printf("Tabs: %d\n", tabs);
    printf("New lines: %d\n", nl);

    return 0;
}