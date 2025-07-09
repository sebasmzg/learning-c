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

typedef struct
{
    uint32_t course_id;
    char course_name[32];
    uint32_t credit_hours;
} Courses;

typedef struct
{
    uint32_t student_id;
    uint32_t course_id;
    uint32_t year;
    uint32_t semester;
} Enrollment;

void averageAgePerCourse(const char *file_name)
{
    FILE *file = fopen(file_name, "rb");
    if (file == NULL)
    {
        perror("Error al abrir el archivo binario");
        return;
    }

    fseek(file, 2, SEEK_SET);

    uint32_t student_count, course_count, enrollment_count;
    fread(&student_count, sizeof(uint32_t), 1, file);
    fread(&course_count, sizeof(uint32_t),1, file);
    fread(&enrollment_count, sizeof(uint32_t), 1, file);

    Student *students = malloc(student_count * sizeof(Student));
    if (students == NULL)
    {
        perror("Error al asignar memoria para estudiantes");
        fclose(file);
        return;
    }

    for (uint32_t i = 0; i < student_count;i++)
    {
        fread(&students[i], sizeof(Student), 1, file);
    }

    Courses *course = malloc(course_count * sizeof(Courses));
    if (course == NULL)
    {
        perror("Error al asignar memoria para cursos");
        free(students);
        fclose(file);
        return;
    }

    for (uint32_t i = 0; i < course_count;i++)
    {
        fread(&course[i], sizeof(Courses), 1, file);
    }

    printf("Average age per course:\n\n");
    printf("%-35s %-10s\n\n", "Course Name", "Average Age");


    for (uint32_t i = 0; i < course_count; i++)
    {
        uint32_t ages_sum = 0;
        uint32_t course_students = 0;

        fseek(file, 2 + 3*sizeof(uint32_t) + student_count*sizeof(Student) + course_count * sizeof(Courses), SEEK_SET);

        for (uint32_t j = 0; j < enrollment_count; j++)
        {
            Enrollment enrollment;
            fread(&enrollment, sizeof(Enrollment), 1, file);

            if (enrollment.course_id == course[i].course_id)
            {
                for (uint32_t s = 0; s < student_count; s++)
                {
                    if (students[s].student_id == enrollment.student_id)
                    {
                        ages_sum += students[s].age;
                        course_students++;
                        break;
                    }
                }
            }
        }

        if (course_students > 0)
        {
            double avg_age = (double)ages_sum / course_students;
            printf("%-35.*s %-10.1f\n", 32, course[i].course_name, avg_age);
        }
    }

    free(students);
    free(course);
    fclose(file);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Use %s <archivo>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *bin_file_name = argv[1];

    printf("\n--------- Reading %s ----------\n\n", bin_file_name);

    averageAgePerCourse(bin_file_name);

    return EXIT_SUCCESS;
}
