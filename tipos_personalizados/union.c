#include <stdio.h>

// Definición de una unión para un valor que puede ser int o float

union DatoNumerico
{
    int entero;
    float flotante;
    char caracter;
};

// Otro ejemplo: Interpretar bytes de un entero
union InterpretacionBytes
{
    int valor_entero;
    char bytes[sizeof(int)]; // Un Array del tamaño de un int
};

int main()
{
    union DatoNumerico mi_dato;

    // Asignar un valor entero
    mi_dato.entero = 123;
    printf("Cuando se asgina un entero (123):\n", mi_dato.entero);
    // Los otros miembros tendrán datos basura
    printf("  flotante: %f (puede ser basura)\n", mi_dato.flotante);
    printf("  caracter: %c (puede ser basura)\n", mi_dato.caracter);
    printf("Tamano de la union DatoNumerico: %zu bytes (igual que el mas grande, float o int)\n\n", sizeof(mi_dato));

    // Asignar un valor flotante (esto sobrescribe el valor entero)
    mi_dato.flotante = 3.14;
    printf("Cuando se asigna flotante (3.14):\n");
    printf("  flotante: %f\n", mi_dato.flotante);
    // Ahora 'entero' tendrá una interpretación binaria de 3.14, no 123.
    printf("  entero: %d (puede ser basura)\n", mi_dato.entero);
    printf("  caracter: %c (puede ser basura)\n\n", mi_dato.caracter);


    // Asignar un caracter (esto sobrescribe todo lo anterior)
    mi_dato.caracter = 'A';
    printf("Cuando se asigna caracter ('A'):\n");
    printf("  caracter: %c\n", mi_dato.caracter);
    printf("  entero: %d (puede ser basura)\n", mi_dato.entero);
    printf("  flotante: %f (puede ser basura)\n\n", mi_dato.flotante);


    // Ejemplo InterpretacionBytes
    union InterpretacionBytes num_bytes;
    num_bytes.valor_entero = 0x12345678; // Un entero hexadecimal (en little-endian, el byte 78 estara primero)

    printf("Interpretacion de bytes de un entero (0x12345678):\n");
    printf("  Valor entero: 0x%X\n", num_bytes.valor_entero);
    for (size_t i = 0; i < sizeof(int); i++) {
        // Imprimir cada byte en formato hexadecimal
        printf("  Byte %zu: 0x%02X\n", i, (unsigned char)num_bytes.bytes[i]);
    }
    printf("Tamano de la union InterpretacionBytes: %zu bytes\n", sizeof(num_bytes));


    return 0;
}