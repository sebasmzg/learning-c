#include <stdio.h>
#include <stdlib.h>

int main()
{
    float *precios;
    int num_productos = 3;

    //Asignar memoria para 3 flotantes, inicializados a 0.0
    precios = (float *) calloc(num_productos, sizeof(float));

    if (precios == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria con calloc.\n");
        return 1;
    }

    printf("VAlores iniciales asignados con calloc (deberían ser cero):\n");
    for (int i = 0; i < num_productos; i++)
    {
        printf("%.2f ", precios[i]); //mostrará 0.00
    }
    printf("\n");

    // Puedo asignarle otros valores después
    precios[0] = 12.50;
    precios[1] = 5.75;

    printf("Valores después de asignación manual: \n");
    for (int i = 0; i < num_productos; i++)
    {
        printf("%.2f ", precios[i]);
    }
    printf("\n");

    // ***** liberar memoria ******
    free(precios);
    precios = NULL;

    return 0;
}
