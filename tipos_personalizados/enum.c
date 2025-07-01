#include <stdio.h>

// Definición de un enum para los días de la semana
enum DiasSemana
{
    LUNES, // 0
    MARTES, // 1
    MIERCOLES, // 2
    JUEVES, // 3
    VIERNES, // 4
    SABADO, // 5
    DOMINGO // 6
};

// Otro enum con valores específicos
enum EstadoProceso
{
    INICIADO = 1,
    EN_PROGRESO = 5,
    PAUSADO, // Este será 6 (5 + 1)
    COMPLETADO = 10,
    FALLIDO // Este será 11 (10 + 1)
};

int main()
{
    enum DiasSemana hoy = MARTES;
    printf("Hoy es el dia numero: %d\n", hoy); // 2

    enum EstadoProceso mi_proceso = EN_PROGRESO;
    printf("Estado de proceso: %d\n", mi_proceso); // 5

    mi_proceso = FALLIDO;
    printf("Estado del proceso (después): %d\n", mi_proceso); //11

    switch (hoy) {
    case LUNES:
        printf("Inicio de semana.\n");
        break;
    case VIERNES:
        printf("Casi fin de semana.\n");
        break;
    case SABADO:
    case DOMINGO:
        printf("Fin de semana.\n");
        break;
    default:
        printf("Dia entre semana.\n");
        break;
    }

    return 0;
}