#include <stdio.h>
#define lenght 2



struct perro
{
    char nombre[30];
    int edadMeses;
    float peso;
}perros[3];

//struct perro perro1 = {"Laia",10,8.6};

//estructuras anidadas
struct owner
{
    char name[50];
    char address[50];
};

struct dog
{
    char name[20];
    int age;
    struct owner ownerDog;
}dogs[lenght];

main()
{
    //printf("el nombre del mi mascota es %s, pesa: %.2fkg y tiene %i meses", perro1.nombre, perro1.peso, perro1.edadMeses);

    /* Arreglos de estructuras */
    /*
    for (int i= 0; i < 3; i++)
    {
        printf("perro %i\n", i+1);
        printf("nombre\n");
        scanf("%s", perros[i].nombre);
        printf("peso\n");
        scanf("%f", &perros[i].peso);
        printf("edad\n");
        scanf("%i", &perros[i].edadMeses);
    }

    for (int i = 0; i < 3; i++)
    {
        printf("el perro %i se llama %s, pesa %.2fkg y tiene %i meses.\n", i+1, perros[i].nombre, perros[i].peso, perros[i].edadMeses);
    }
    */
    for (int i = 0; i < lenght; i++)
    {
        printf("nombre perro: \n");
        scanf("%s", &dogs[i].name);
        printf("edad años: \n");
        scanf("%i",&dogs[i].age);
        printf("nombre dueño:\n");
        scanf("%s",&dogs[i].ownerDog.name);
        printf("direccion:\n");
        scanf("%s",&dogs[i].ownerDog.address);
    }

    for (int i = 0; i < lenght; i++)
    {
        printf("perro %i se llama %s, tiene %i años, su dueño es %s y vive en %s\n", i+1, dogs[i].name, dogs[i].age, dogs[i].ownerDog.name, dogs[i].ownerDog.address);
    }
}