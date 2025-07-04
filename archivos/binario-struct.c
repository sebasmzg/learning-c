#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para representar un registro de datos
typedef struct
{
    int id;
    char nombre[20];
    float valores[3]; // Array para ecaluar distintos casos
    unsigned char activo; // Una bandera (0 o 1)
} RegistroDatos;

// Mostrar contenido de un RegistroDatos
void mostrarRegistro(const RegistroDatos *reg)
{
    printf("ID: %d\n", reg->id);
    printf("Nombre: %s\n", reg->nombre);
    printf("Valores: %.2f, %.2f, %.2f\n", reg->valores[0], reg->valores[1], reg->valores[2]);
    printf("Activo: %d\n", reg->activo);
    printf("---------------------------\n");
}

int main()
{
    FILE *archivo_binario = NULL;
    RegistroDatos reg1 = {101,"Ana", {1.1f, 2.2f, 3.3f}, 1};
    RegistroDatos reg2 = {102, "Bob Dylan", {4.4f, 5.5f, 6.6f}, 0};
    RegistroDatos reg_leido; // estructura para almacenar datos leidos

    const char *nombre_archivo_binario = "datos.bin";


    // --- Parte 1: Escribir estructuras en modo binario ---
    printf("--- Escritura binaria de estructuras ---\n");

    archivo_binario = fopen(nombre_archivo_binario, "wb");
    if (archivo_binario == NULL)
    {
        perror("Error al abrir el archivo binario para escritura");
        return EXIT_FAILURE;
    }

    // Escribir reg1
    size_t escritos1 = fwrite(&reg1, sizeof(reg1), 1, archivo_binario);
    if (escritos1 != 1)
    {
        perror("Error al escribir reg1");
        fclose(archivo_binario);
        return EXIT_FAILURE;
    }
    printf("Registro 1 escrito (%zu bytes).\n", sizeof(RegistroDatos));

    // Escribir reg2
    size_t escritos2 = fwrite(&reg2, sizeof(reg2), 1, archivo_binario);
    if (escritos2 != 1)
    {
        perror("Error al escribir reg2");
        fclose(archivo_binario);
        return EXIT_FAILURE;
    }
    printf("Registro 2 escrito (%zu bytes).\n", sizeof(RegistroDatos));

    fclose(archivo_binario);
    printf("Archivo binario '%s' creado y cerrado.\n\n", nombre_archivo_binario);


    // --- Parte 2: Leer estructuras desde un archivo binario ---
    printf("--- Lectura binaria de estructuras ---");

    archivo_binario = fopen(nombre_archivo_binario, "rb");
    if (archivo_binario == NULL)
    {
        perror("Error al abrir archivo binario para lectura");
        return EXIT_FAILURE;
    }

    printf("Contenido leido del archivo:\n");

    // Leer primer registro
    size_t leidos1 = fread(&reg_leido, sizeof(reg_leido), 1, archivo_binario);
    if (leidos1 != 1)
    {
        printf("No se pudo leer el Registro 1.\n");
    } else
    {
        printf("Registro 1 leido:\n");
        mostrarRegistro(&reg_leido);
    }

    // Leer segundo registro
    size_t leidos2 = fread(&reg_leido, sizeof(reg_leido), 1, archivo_binario);
    if (leidos2 != 1)
    {
        printf("No se pudo leer el Registro 2.\n");
    } else
    {
        printf("Registro 2 leido:\n");
        mostrarRegistro(&reg_leido);
    }

    fclose(archivo_binario);
    printf("Archivo binario cerrado.\n\n");

    // --- Parte 3: Ver el contenido binario con hexdump (instrucción para terminal Linux) ---
    printf("Para ver el contenido hexadecimal del archivo en Linux Ubuntu, \n");
    printf("abre una terminal y ejecuta:\n");
    printf("  hexdump -C %s\n\n", nombre_archivo_binario);
    printf("Observa los bytes crudos de los enteros, flotantes y la cadena.\n");
    printf("La representacion de flotantes y enteros puede variar por 'endianness'.\n");

    return EXIT_SUCCESS;
}