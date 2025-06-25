#include <stdio.h>

main()
{
    //break temrina ejecución
    //continue permite ejecutar pero salta un paso

    int num = 0;
    while (num <= 5)
    {

/*
        printf("%i \n", num);
        if (num == 2)
        {
            printf("chaito");
            break;
        }
*/
        //aumentar el valor antes del continue para evitar bucles
        num++;
        if (num == 2)
        {
            printf("llegué a 2\n");
            continue;
        }
        printf("%i \n", num);

    }
}