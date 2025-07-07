#include <stdio.h>
#include <stdarg.h>

// Prototipo de la función variádica
// El primer parámetro 'count' es fijo e indica cuantos enteros siguen
int sumar_numeros(int count,...);

int main()
{
    printf("--- Uso de funciones variádicas ---\n\n");

    // Ejemplo 1: Sumar 3 números.
    int suma1 = sumar_numeros(3, 10,20,30);
    printf("Suma de 10,20,30 = %d\n\n", suma1);

    // Ejemplo 2: Sumar 5 números.
    int suma2 = sumar_numeros(5, 1, 2, 3 ,4 ,5);
    printf("Suma de 1,2,3,4,5 = %d\n\n", suma2);

    // Ejemplo 3: Sumar 1 número.
    int suma3 = sumar_numeros(1,100);
    printf("Suma de 100 = %d\n\n", suma3);

    // Advertencia: si 'count' no coindcide con el numero de argumnentos reales,
    // o si los tipos no coinciden, el comportamiento será indefinido.
    // Cuando el count es menor quie la cantidad de argumentos, la función rellenerá con datos basura
    // que estén almacenados en ese espacio de memoria
    return 0;
}

// Implementación de la función variádica
int sumar_numeros(int count,...)
{
    va_list args; // Declara una variable de tipo va_list
    int suma = 0;
    int i;

    // 1. Inicializa 'args' para que apunte al primer argumento variable
    // 'count' es el último parámetro fijo.
    va_start(args, count);

    // 2. Itera 'count' veces para recuperar cada argumento.
    // Es crítico saber cuantos argumentos hay y de qué tipo son.
    // En este caso, 'count' nos dice cuantos 'int' esperar.
    for (i = 0; i < count; i++)
    {
        int num = va_arg(args, int); // Recuper el siguiente argumento como un 'int'
        suma += num;
        printf(" Recuperado argumento #%d: %d\n", i+1, num);
    }

    // 3. Limpia la lista de argumentos variables.
    va_end(args);

    return suma;
}