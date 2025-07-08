#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct
{
    uint16_t magic_string;
    uint32_t student_count;
    uint32_t course_count;
    uint32_t enrollment_count;
} Headers;

typedef struct
{
    uint32_t student_id;
    uint8_t flags;
    char student_name[23];
    uint32_t age;
} Student;

void mostrarRegistros(const char *nombre_archivo, int edad_minima, int edad_maxima)
{
    FILE *archivo = fopen( nombre_archivo, "rb");
    if (archivo == NULL)
    {
        perror("Error al abrir el archivo binario");
        return;
    }

    fseek(archivo, 2, SEEK_SET);

    uint32_t student_count, course_count, enrollment_count;
    fread(&student_count, sizeof(uint32_t), 1, archivo);
    fread(&course_count, sizeof(uint32_t),1, archivo);
    fread(&enrollment_count, sizeof(uint32_t), 1, archivo);

    printf("Estudiantes entre %d y %d años:\n\n",edad_minima, edad_maxima);
    printf("%-25s %-5s %-8s\n\n", "Nombre", "Edad", "Género");

    int encontrados = 0;

    for (uint32_t i = 0; i < student_count; i++)
    {
        Student student;
        if (fread(&student, sizeof(Student),1,archivo) != 1)
        {
            perror("Error al leer el registro del estudiante");
            fclose(archivo);
            break;
        }

        if (student.age >= edad_maxima && student.age <= edad_maxima)
        {
            const char *gender = (student.flags & 0x80) ? "Mujer" : "Hombre";
            printf("%-25s %-5u %-8s\n", student.student_name, student.age, gender);
            encontrados++;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Uso %s <archivo> <edad_minima> <edad_maxima>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *archivo = NULL;
    const char *nombre_archivo_binario = argv[1];
    int edad_minima = atoi(argv[2]);
    int edad_maxima = atoi(argv[3]);

    if (edad_minima <= 0 || edad_maxima <= 0 || edad_maxima < edad_minima)
    {
        fprintf(stderr, "Rango de edades inválido. Debe ser positivo y la edad mínima debe ser menor que la máxima.\n");
        return EXIT_FAILURE;
    }

    archivo = fopen(nombre_archivo_binario, "rb");
    if (archivo == NULL)
    {
        perror("Error al abrir el archivo binario");
        return EXIT_FAILURE;
    }

    printf("\n--------- Leyendo %s ----------\n\n", nombre_archivo_binario);

    mostrarRegistros(nombre_archivo_binario, edad_minima, edad_maxima);

    return EXIT_SUCCESS;
}
