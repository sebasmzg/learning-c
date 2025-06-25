#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *numeros = NULL; //inicializar puntero a null es buena pràctica
    int cantidad_actual = 0;
    int nueva_cantidad;
    int i;

    // 1. asignación inicial con malloc ------------
    // Pedimos memoria para 3 enteros al incio

    cantidad_actual = 3;
    numeros = ( int * ) malloc(cantidad_actual * sizeof(int));

    if (numeros == NULL)
    {
        fprintf(stderr, "Error: Fallo al asignar memoria inical.\n");
        return 1;
    }

    printf("Memoria inial asignada para %d enteros.\n", cantidad_actual);
    for (i = 0; i < cantidad_actual; i++)
    {
        numeros[i] = (i + 1) * 10; //llenar con 10, 20, 30
        printf("%d ", numeros[i]);
    }
    printf("\n\n");

    // 2. Reasiagnación con realloc (expandir) ------
    printf("cuàntos eneteros más quieres añadir?");
    scanf("%d", &nueva_cantidad);
    int total_nueva_cantidad = cantidad_actual + nueva_cantidad;

    //usamos puntero temporal para realloc por seguridad
    int *temp_numeros = (int *) realloc(numeros, total_nueva_cantidad * sizeof(int));
    if (temp_numeros == NULL)
    {
        fprintf(stderr, "Error: Fallo al reasignar memoria. el bloque original sigue válido.\n");
        //aquí nùmeros sigue apuntando al bloque originar de 3 enteros
        // debemos liberar memoria antes de salir si no lo vmaqops a usar más

        free(numeros);
        numeros = NULL;
        return 1;
    }

    //Si realloc fue exitoso actualizamos puntero principal y cantidad
    numeros = temp_numeros;
    temp_numeros = NULL;
    printf("Memoria reasignada a %d enteros.\n", total_nueva_cantidad);
    for (i = 0; i < total_nueva_cantidad; i++)
    {
        numeros[i] = (i + 1) * 100; //lennar con 400,500,etc
    }
    cantidad_actual = total_nueva_cantidad;

    printf("Contenido actuial del arreglo: \n");
    for (i = 0; i< cantidad_actual; i++)
    {
        printf("%d ", numeros[i]);
    }
    printf("\n\n");

    // 3. Reasignación con realloc (contraer)
    printf("A cuántos enteros quieres reducir el arreglo? (menor o igual a %d)", cantidad_actual);
    scanf("%d", &nueva_cantidad);

    if (nueva_cantidad <= 0 || nueva_cantidad > total_nueva_cantidad)
    {
        printf("Cantidad inválida para reducir. Manteniendo el tamaño actual");
    } else
    {
        temp_numeros = (int *) realloc(numeros, nueva_cantidad * sizeof(int));

        if (temp_numeros == NULL && nueva_cantidad > 0)
        { // realloc(ptr, 0) es como free(ptr)
            fprintf(stderr, "Error: Fallo al reasignar memoria para reducir. El bloque original sigue valido.\n");
            // 'numeros' sigue siendo válido aquí, la memoria no se perdió
        } else
        {
            numeros = temp_numeros;
            temp_numeros = NULL;
            cantidad_actual = nueva_cantidad;
            printf("Memoriareducida a %d enteros.\n",cantidad_actual);
        }
    }

    printf("Contenido actual del arreglo: \n");
    for (i = 0; i< cantidad_actual; i++)
    {
        printf("%d", numeros[i]);
    }
    printf("\n\n");

    // 4. Liberar memoria ---------------
    free(numeros);
    numeros = NULL;
    printf("Memoria liberada exitosamente");

    return 0;
}
