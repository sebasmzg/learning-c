#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *archivo = NULL;   // Declarar puntero a FILE
    char buffer[100];       // Buffer para leer y escribir cadenas


    // --- Parte 1: Escribir en un archivo ---
    printf("--- Escritura en archivo ---\n");

    // Abre el archivo "ejemplo.txt" en modo de escritura ("wb") (incluir b como buena práctica)
    // Si el archivo no existe, lo crea. Si existe, trunca su contenido.
    archivo = fopen("ejemplo.txt", "wb");
    if (archivo == NULL)
    {
        perror("Error al abrir el archivo para escritura"); // Mensaje de error del sistema
        return EXIT_FAILURE; // Sale del programa con un código de error
    }

    fprintf(archivo, "Hooolaaaa mundo!\n");     // Escribir linea formateada
    fputs("Esta es la segunda linea.\n", archivo);  // Escribir una cadena
    fputc('C', archivo);
    fputc('\n', archivo);

    printf("Datos escritos en 'ejemplo.txt'.\n");

    // Siempre cerrar archivo luego de usarlo
    if (fclose(archivo) == EOF)
    {
        perror("Error al cerrar el archivo para escritura");
        return EXIT_FAILURE;
    }
    printf("Archivo de escritura cerrado. \n\n");


    // --- Parte 2: Lectura desde el mismo archivo ---
    printf("--- Lectura desde archivo ---\n");

    // Abrir archivo 'ejemplo.txt' en modo lectura (rb)
    archivo = fopen("ejemplo.txt", "rb");
    if (archivo == NULL)
    {
        perror("Error al abrir el archivo para lectura");
        return EXIT_FAILURE;
    }

    printf("Contenido de 'ejemplo.txt':\n");

    // Leer línea por línea usando fgets
    while (fgets(buffer, sizeof(buffer), archivo) != NULL)
    {
        printf("%s", buffer); // Imprime la linea leída (fgets inclute el \n)
    }

    // Verificar si hubo error de lectura o si se llegó al final del archivo
    if (ferror(archivo))
    {
        perror("Error durante la lectura del archivo.");
    } else if (feof(archivo))
    {
        printf("\nFin del archivo alcanzado\n");
    }

    // Cerrar el archivo
    if (fclose(archivo) == EOF)
    {
        perror("Error al cerrar elarchivo de lectura");
        return EXIT_FAILURE;
    }
    printf("Archivo de lectura cerrado. \n\n");


    // --- Parte 3: Adjuntar a un archivo ---
    printf("Adjuntar a un archivo");
    archivo = fopen("ejemplo.txt", "ab");  // Abre en modo adjuntar (append - agregar al final)

    if (archivo == NULL)
    {
        perror("Error al abrir archivo para adjuntar");
        return EXIT_FAILURE;
    }
    fprintf(archivo, "Esta linea fue adjuntada.\n");
    printf("Linea adjuntada a 'ejemplo.txt'.\n");

    if (fclose(archivo) == EOF)
    {
        perror("Error al cerrar archivo adjunto");
        return EXIT_FAILURE;
    }
    printf("Archivo adjunto cerrado\n\n");


    // --- Parte 4: Demostración fseek/ftell ---
    printf("--- Demostración fseek/ftell ---\n");
    archivo = fopen("ejemplo.txt", "rb");
    if (archivo == NULL)
    {
        perror("Error al abrir el archivo para fseek y ftell");
        return EXIT_FAILURE;
    }

    printf("Posición inicial del puntero: %ld\n", ftell(archivo)); // 0

    // Leer primeros 5 caracteres
    fseek(archivo, 5, SEEK_SET); // Mocer 5 bytes desde el inicio
    printf("Posición después de fseek(5,SEEK_SET): %ld", ftell(archivo));

    fgetc(archivo); // Leer un caracter
    printf("Posición después de fgetc: %ld", ftell(archivo));

    rewind(archivo); // Volver al incio
    printf("Posición después de rewind: %ld", ftell(archivo)); // 0


    // Cambiar nombre de archivo
    /*
    if (rename("ejemplo.txt", "new_ejemplo.txt") == 0)
    {
        printf("Archivo renombrado.\n");
    } else
    {
        perror("Error al renombrar el archivo\n");
    }*/

    if (fclose(archivo) == EOF)
    {
        perror("Error al cerrar archivo fseek / ftell");
    }
    printf("Archivo de fseek cerrado\n\n");


    // Eliminar el archivo
    /*
    if (remove("ejemplo.txt") == 0)
    {
        printf("Archivo eliminado exitosamente");
    } else
    {
        perror("Error al eliminar archivo");
    }
    */

    return EXIT_SUCCESS;
}