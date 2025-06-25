#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *edades;
    int num_personas;

    printf("Cuántas personas va a registrar?\n");
    scanf("%d", &num_personas);

    if (num_personas <= 0)
    {
        printf("Numero de personas debe ser positivo\n");
        return 1;
    }

    //calloc si queremos que las edades empiecen en 0, o malloc si no importa
    edades = (int *) calloc(num_personas, sizeof(int));

    if (edades == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria para las edades.\n");
        return 1;
    }

    printf("Ingresa las edades de las %d personas:\n", num_personas);
    for (int i = 0; i < num_personas; i++)
    {
        printf("Edad persona %d: ", i + 1);
        scanf("%d", &edades[i]);
    }

    printf("\nRegistros: \n");
    for (int i = 0; i < num_personas; i++)
    {
        printf("Persona: %d - Edad: %d\n", i + 1, edades[i]);
    }

    // **** liberar memoria ****
    free(edades);
    edades = NULL;

    return 0;
}