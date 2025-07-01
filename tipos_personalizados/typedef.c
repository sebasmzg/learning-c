#include <stdio.h>
#include <stdint.h> // Para int8_8, etc.

// 1. Alias para tipos de datos básicos.
typedef unsigned int U_INT; // Ahora 'U_INT' es un alias para 'uunsigned int'
typedef int INTEGER; // 'INTEGER' es un alias para 'int'

// 2. Alias para estructuras
typedef struct Persona
{
    char nombre[20];
    int edad;
} Persona; // Ahora podemos usar 'Persona' DIRECTAMENTE SIN 'struct Persona'.
//cada miembro del struct ocupa su propio espacio en memoriaç

// 3. Alias para punteros
typedef int *IntPtr; // 'IntPtr' es un alias para 'int *'

//4. Alias para tipos con tamaño específico (para portabilidad)
typedef int8_t BYTE; // Un byte de 8 bits con signo
typedef int16_t WORD; // Una palabra de 16 bits con signo
typedef int32_t DWORD; // Una doble palabra con 32 bits sin signo

int main()
{
    U_INT contador = 100;
    INTEGER temperatura = -5;
    printf("Contador: %u, Temperatura: %d\n", contador, temperatura);

    Persona p1;
    sprintf(p1.nombre, "George");
    p1.edad = 27;
    printf("Persona: %s, Edad: %d\n", p1.nombre, p1.edad);

    IntPtr p_valor;
    int mi_valor = 42;
    p_valor = &mi_valor;
    printf("Valor a través de un puntero: %d\n", *p_valor);

    BYTE b = 0xFF; // -1 en int8_t
    WORD w = 0xFFFF; // -1 en int16_t
    DWORD dw = 0xFFFFFFFF; // 4294967295 en uint32_t
    printf("Byte: %d, Word: %d, DWord: %u\n", b, w, dw);

    return 0;
}