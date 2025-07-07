#include <stdio.h>
#include "mi_modulo.h" // Solo incluye la declaracion opaca y la API

int main() {
    printf("--- Programa Cliente --- \n\n");

    // Crear una instancia del tipo de dato opaco
    MiTipoOpaque *mi_objeto = mi_tipo_crear(100);

    if (mi_objeto == NULL) {
        fprintf(stderr, "Error: No se pudo crear el objeto opaco.\n");
        return 1;
    }

    printf("Dato inicial del objeto: %d\n", mi_tipo_obtener_dato(mi_objeto));

    // Procesar el objeto usando la funcion publica
    mi_tipo_procesar(mi_objeto);
    printf("Dato despues de procesar: %d\n", mi_tipo_obtener_dato(mi_objeto));

    // Intentar acceder directamente a los miembros (¡Esto causaría un error de compilación!)
    // mi_objeto->dato_interno_1 = 500; // ERROR: miembro 'dato_interno_1' undeclared

    // Destruir el objeto y liberar su memoria
    mi_tipo_destruir(mi_objeto);
    mi_objeto = NULL; // Buena practica para evitar punteros colgantes

    printf("\n--- Programa Cliente Finalizado ---\n");
    return 0;
}