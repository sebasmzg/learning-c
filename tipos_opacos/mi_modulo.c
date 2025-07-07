#include "mi_modulo.h"
#include <stdio.h>
#include <stdlib.h>

// Definición COMPLETA de la estructura
// SOLO visible en este archivo .c
struct MiTipoOpaque
{
    int dato_interno_1;
    char dato_interno_2[50];
    // otros miembros privados
};

struct MiTipoOpaque *mi_tipo_crear(int valor_inicial)
{
    struct MiTipoOpaque *nueva_instancia = (struct MiTipoOpaque * ) malloc(sizeof(struct  MiTipoOpaque));
    if (nueva_instancia == NULL)
    {
        perror("Error al asignar memoria para MiTipoOpaque");
        return NULL;
    }
    nueva_instancia->dato_interno_1 = valor_inicial;
    sprintf(nueva_instancia->dato_interno_2, "Inicializado con %d", valor_inicial);
    printf("DEBUG: MiTipoOpaque creado con dato_interno_1 = %d\n", nueva_instancia->dato_interno_1);
    return nueva_instancia;
}

void mi_tipo_procesar(struct MiTipoOpaque *instancia) {
    if (instancia != NULL) {
        instancia->dato_interno_1++;
        printf("DEBUG: Procesando instancia. Dato interno 1 incrementado a %d. Texto: %s\n",
               instancia->dato_interno_1, instancia->dato_interno_2);
    }
}

int mi_tipo_obtener_dato(struct MiTipoOpaque *instancia) {
    if (instancia != NULL) {
        return instancia->dato_interno_1;
    }
    return -1; // O manejar error de otra forma
}

void mi_tipo_destruir(struct MiTipoOpaque *instancia)
{
    if (instancia != NULL) {
        printf("DEBUG: Destruyendo instancia con dato_interno_1 = %d\n", instancia->dato_interno_1);
        free(instancia);
    }
}