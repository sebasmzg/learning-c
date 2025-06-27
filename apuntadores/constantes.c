#include <stdio.h>
#include <stdlib.h>



int main()
{
    // --- PUNTERO A UNA CONSTANTE
    int num1 = 10;
    int num2 = 20;

    printf("--- PUNTERO A UNA CONSTANTE ---");
    const int *p = &num1; // 'p' es un puntero que apunta a un entero constante
    printf("Valor al que apunta p: %d\n", *p);

    // *p = 15; // ERROR de compilación: no puedes modificar el valor a través de 'p'

    p = &num2; // Esto SÍ es válido: puedes hacer que 'p' apunte a otra variable
    printf("Nuevo valor al que apunta p: %d\n", *p); // Salida: 20


    // --- PUNTERO CONSTANTE
    int *const ptr = &num1; //'p' es un puntero constante a un entero (no constante)
    printf("Valor al que apunta ptr: %d\n", *ptr);
    *ptr = 100; // Sí es válido: puedo modificar el valor a traves del puntero

    printf("Nuevo valor al que apunta ptr: %d\n", *ptr);
    // ptr = &num2; // Error, no  puedo reasignar la dirección a la que apunta


    // --- PUNTERO CONSTANTE QUE APUNTA A UNA CONSTANTE
    const int *const p2 = &num1; // 'p' es un puntero constante que apunta a una constante
    printf("Valor al que apunta p2: %d\n", *p2);
    // *p = 15; // ERROR de compilación: no puedes modificar el valor
    // p = &num2; // ERROR de compilación: no puedes reasignar 'p'

    return 0;
}
