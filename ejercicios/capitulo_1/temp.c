#include <stdio.h>
#define LOWER 0
#define UPPER 300
#define STEP 20

/* imprimir tabla de temps de 0 a 300ºC con su equivalente en fahr con intervalos de 20ºC */
/*formula: ºC = (5/9)(ºF-32) */

void farhToCelsius(void)
{
    float fahr, celsius;
    //int upper, step;

    // const int lower = 0; /*const porque no cambia*/
    // upper = 300;
    // step = 20;

    fahr = LOWER;
    printf("convert from ºF to ºC\n");
    printf("%3s\t%6s\n", "ºF", "ºC");
    while (fahr <= UPPER)
    {
        celsius = 5 * (fahr - 32) / 9; /*como 5 y 9 son enteros, la division se trunca y darìa 0*/
        printf("%3.0f\t%6.1f\n", fahr, celsius); /*%d para enteros %f para floats el %3.0 por lo menos 3 char de ancho y sin fraccionarios y %6.1 => 6 ancho y 1 fraccion*/
        /* % 6f indica que el número es por lo menos de seis caracteres de ancho */
        /* %.2f indica dos caracteres después del punto decimal*/
        /*
            %o para octal,
            %x para hexadecimal,
            %c para carácter,
            %s para cadena de caracteres y
            %% para % en sí
         */
        fahr = fahr + STEP;
    }
    printf("--- Usando For ---\n");
    for (fahr = 0; fahr <= UPPER; fahr += STEP)
    {
        printf("%3.0f %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
    }
}

void celsiusToFahrenheit(void)
{
    float celsius, fahr;
    // int lower, upper, step;
    // lower = 0;
    // upper = 300;
    // step = 20;

    celsius = LOWER;

    printf("convert from ºC to ºF\n");
    printf("%3s\t%6s\n", "ºC", "ºF");

    while (celsius <= UPPER)
    {
        fahr = celsius * 9.0 / 5.0 + 32;
        printf("%3.0f\t%6.1f\n", celsius, fahr);
        celsius = celsius + STEP;
    }
}

main()
{
    farhToCelsius();
    celsiusToFahrenheit();
}
