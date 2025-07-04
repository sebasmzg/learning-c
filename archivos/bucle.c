#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *archivo_lectura = NULL;
    int caracter; // Se usa 'int' para fgetc para poder almacenar EOF

    archivo_lectura = fopen("ejemplo.txt", "rb");
    if (archivo_lectura == NULL)
    {
        perror("Error aL abrir archivo de lectura 'ejemplo.txt'");
        return EXIT_FAILURE;
    }

    printf("Leyendo caracter a caracter (con do-while y feof):\n");

    // El bucle do-while es ideal para leer archivos caracter a caracter
    // porque garantiza que el cuerpo del bucle se ejecute al menos una vez,
    // lo que permite intentar leer un caracter antes de verificar EOF.
    do
    {
        caracter = fgetc(archivo_lectura);
        if (caracter != EOF)
        {
            putchar(caracter); // Imprime el caracter si no es EOF
        }
    } while (caracter != EOF); // Continua mientras no se llegue al final del archivo

    // Después del bucle, feof() o ferror() se usan para determinar la causa del fin
    if (feof(archivo_lectura))
    {
        printf("\n---> Final del archivo alcanzado (EOF).\n");
    } else if (ferror(archivo_lectura))
    {
        perror("---> Error durante la lectura del archivo");
    }

    fclose(archivo_lectura);

    return EXIT_SUCCESS;

}