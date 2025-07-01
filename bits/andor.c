#include <stdio.h>

// & -> 1 - 1 = 1 verdadero si ambos son verdaderos
// | -> 0 - 0 = 0 falso si los dos son falsos


/*
Escenario: Configuración de Permisos de Usuario
Imagina que estás desarrollando un sistema simple donde un usuario puede tener varios permisos, como:

Lectura (READ): Puede leer archivos.

Escritura (WRITE): Puede modificar archivos.

Ejecución (EXECUTE): Puede ejecutar programas.

Administrador (ADMIN): Tiene todos los permisos.

Podemos representar cada permiso con un bit específico dentro de una variable unsigned char (8 bits).

Bit 0: READ

Bit 1: WRITE

Bit 2: EXECUTE

Bit 3: ADMIN

(Los bits restantes pueden usarse para otras cosas, o simplemente quedan en 0)
 */

// Imprimir binario 8 bits
void imprimirBinario(unsigned char num)
{
    // iterar desde el número más significativo
    for (int i = 7; i >= 0; i--)
    {
        // desplazamos el bit actual a la posición 0 y hacemos un AND con 1
        // máscara & 1 para realizar operacion: si i=> 1 & 1 = 1
        // para obtener su valor (0 o 1)
        printf("%d", (num >> i) & 1);
    }
}

int main()
{
    // Definimos las "màscaras" para cada permiso usando desplazamientos.
    // Esto hace el código más legible que usar números decimales directamente.
    // 1 << 0 -> 00000001 (Decimal 1)
    // 1 << 1 -> 00000010 (Decimal 2)
    // 1 << 2 -> 00000100 (Decimal 4)
    // 1 << 3 -> 00001000 (Decimal 8)

    const unsigned char PERMISO_LECTURA = 1 << 0; // Bit 0
    const unsigned char PERMISO_ESCRITURA = 1 << 1; // Bit 1
    const unsigned char PERMISO_EJECUCION = 1 << 2; // Bit 2
    const unsigned char PERMISO_ADMIN = 1 << 3; // Bit 3

    // Una variable 'flag' para almacenar los permisos de usuario.
    // Inicialmente, el usuario no tiene permisos (todos los bits en cero).
    unsigned char usuario_flags = 0; // Binario 00000000

    printf("--- Operaciones de Bits con Permisos ---\n\n");

    printf("Estado inicial de los permisos de usuario:\n");
    printf("Binario: "); imprimirBinario(usuario_flags); printf("\n");
    printf("Decimal: %d\n\n", usuario_flags);

    // --- 1. Asignar permisos (Usando OR y desplazamiento) ---
    // Darle al usuario permisos para lectura y ejecución
    // Usamos el operador OR (|) para "encender" los bits correspondientes
    usuario_flags = usuario_flags | PERMISO_LECTURA; // Encender bit 0
    usuario_flags |= PERMISO_EJECUCION; // Encender bit 2

    printf("Después de asignar lectura y ejecución: \n");
    printf("Binario: "); imprimirBinario(usuario_flags); printf("\n");
    printf("Decimal: %d\n\n", usuario_flags); // Debería ser 00000101 (5)

    // --- 2. Verificar permisos (Usando AND) ---
    // Queremos saber si el usuario tiene permisos de escritura
    // Usamos el operados AND (&) ccon la máscara del permiso para verificar el bit
    // Si el resultado es distinto de 0; significa que el bit estaba encendido.
    printf("Verificando permisos:\n");
    if ((usuario_flags & PERMISO_LECTURA) != 0)
    {
        printf(" - El usuario TIENE permiso de LECTURA.\n");
    }

    if ((usuario_flags & PERMISO_ESCRITURA) != 0)
    {
        printf(" - El usuario TIENE permiso de ESCRITURA.\n");
    } else
    {
        printf(" - El usuarion NO TIENE permiso de ESCRITURA\n");
    }

    if ((usuario_flags & PERMISO_EJECUCION) != 0)
    {
        printf(" - El usuario TIENE permiso de EJECUCION.\n");
    }

    // --- 3. Eliminar permisos (usando NOT (~) y AND (&) ---
    // Queremos quitarle al usuario el permiso de ejecución.
    // creamos una mascara con el bit de ejecución apagado y los demás encendidos (usando ~)
    // Luego hacemos un AND con esta máscara
    usuario_flags = usuario_flags & (~PERMISO_EJECUCION); // Apagar bit 2
    // (~PERMISO_EJECUCION) -> (00000100) -> 1111011
    // (00000101) & (11111011) -> 00000001

    printf("\nDespués de quitar EJECUCIÓN\n");
    printf("Binario: "); imprimirBinario(usuario_flags); printf("\n");
    printf("Decimal: %d\n\n", usuario_flags); // Debería ser 00000001 (1)

    // Verificar de nuevo para confirmar
    if ((usuario_flags & PERMISO_EJECUCION) != 0) {
        printf(" - El usuario AUN tiene permiso de EJECUCION (ERROR).\n");
    } else {
        printf(" - El usuario YA NO tiene permiso de EJECUCION (Correcto).\n");
    }

    // --- 4. Asignar todos los permisos (ej. rol ADMIN) ---
    // Usamos OR para asignar múltiples permisos a la vez.
    unsigned char admin_flags = PERMISO_EJECUCION | PERMISO_LECTURA | PERMISO_ESCRITURA | PERMISO_ADMIN;
    printf("\nPermisos de una administrador:\n");
    printf("Binario: "); imprimirBinario(admin_flags); printf("\n");
    printf("Decimal: %d\n\n", admin_flags); // Debería ser 00001111 (15)

    if ((admin_flags & PERMISO_ADMIN) != 0) {
        printf(" - Es administrador (confirmado por bit de ADMIN).\n");
    }

    return 0;
}