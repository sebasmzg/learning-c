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

void enrollmentStatistics(const char *file_name)
{
    FILE *file = fopen(file_name, "rb");
    if ( file == NULL)
    {
        perror("Error opening binary file");
        return;
    }

    fseek(file, 2, SEEK_SET);

    uint32_t student_count, course_count, enrollment_count;
    fread(&student_count, sizeof(uint32_t), 1, file);
    fread(&course_count, sizeof(uint32_t), 1, file);
    fread(&enrollment_count, sizeof(uint32_t), 1, file);

    Student *students = malloc(sizeof(Student) * student_count);
    if (students == NULL)
    {
        perror("Error allocating memory for students");
        fclose(file);
        return;
    }
    for (uint32_t i = 0; i < student_count; i++)
    {
        fread(&students[i], sizeof(Student), 1, file);
    }

    Courses *course = malloc(sizeof(Courses) * course_count);
    if (course == NULL)
    {
        perror("Error allocating memory for courses");
        free(students);
        fclose(file);
        return;
    }
    for (uint32_t i = 0; i < course_count; i++)
    {
        fread(&course[i], sizeof(Courses), 1, file);
    }

    Enrollment *enrollments = malloc(sizeof(Enrollment) * enrollment_count);
    if (enrollments == NULL)
    {
        perror("Error allocating memory for enrollments");
        free(students);
        free(course);
        fclose(file);
        return;
    }
    for (uint32_t i=0; i < enrollment_count; i++)
    {
        fread(&enrollments[i], sizeof(Enrollment), 1, file);
    }

    printf("Enrollment Statistics:\n\n");

    printf("%-6s %-10s %-18s %-20s %-12s %-14s\n", "Year","Semester","Male Undergrad", "Female Undergrad", "Male Grad", "Female Grad");

    for (uint32_t year = 2020; year < 2030; year++)
    {
        for (uint32_t semester = 1; semester <= 2; semester++)
        {
            uint32_t male_undergrad = 0, female_undergrad = 0;
            uint32_t male_grad = 0, female_grad = 0;

            uint8_t *student_counted = calloc(student_count, sizeof(uint8_t));

            for (uint32_t i = 0; i <  enrollment_count; i++)
            {
                if (enrollments[i].year == year && enrollments[i].semester == semester)
                {
                    for (uint32_t j = 0; j < student_count; j++)
                    {
                        if (students[j].student_id == enrollments[i].student_id)
                        {
                            student_counted[j] = 1;

                            uint8_t is_female = (students[j].flags & 0x80) != 0;
                            uint8_t is_grad = (students[j].flags & 0x40) != 0;

                            if (is_grad)
                            {
                                if (is_female)
                                {
                                    female_grad++;
                                } else
                                {
                                    male_grad++;
                                }
                            }else
                            {
                                if (is_female)
                                {
                                    female_undergrad++;
                                } else
                                {
                                    male_undergrad++;
                                }
                                break;
                            }
                        }
                    }
                }
            }
            if (male_undergrad + female_undergrad + male_grad + female_grad > 0)
            {
                printf("%-6u %-10u %-18u %-20u %-12u %-14u\n", year, semester, male_undergrad, female_undergrad, male_grad, female_grad);
            }

            free(student_counted);
        }
    }

    free(students);
    free(course);
    free(enrollments);
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

    enrollmentStatistics(bin_file_name);
    return EXIT_SUCCESS;
}