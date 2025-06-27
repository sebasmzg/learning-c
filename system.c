#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("--- Ejecutando comando del sistema ---\n\n");

    // ejemplo 1: Listar archivos del directorio actual
    printf("Comando: 'ls -l (o 'dir' en windows)\n");
    // Puede adaptar el comando según OS
    #ifdef _WIN32
        int status1 = system("dir");
    #else
        int status1 = system("ls -l");
    #endif
    printf("Estado de salida del comando 1: %d\n\n", status1);

    // Ejemplo 2: Crear un directorio
    printf("comando: 'mkdir nueva_carpeta'\n");
    int status2 = system("mkdir nueva_carpeta");
    if (status2 == 0)
    {
        printf("Directorio 'nueva_carpeta' creado exitosamente.\n\n");
    } else
    {
        printf("Error al creaer el directorio. Estado de salida: %d\n\n", status2);
    }

    // Ejemplo 3: Intentar ejecutar un comando que no existe
    printf("Comando: 'comando_inexistente'\n");
    int status3 = system("comando_inexistente");
    printf("Estado de la salida del comando 3 (inexistente): %d\n\n",status3);

    // Ejemplo 4: Abrir un editor de texto
    printf("Comando: 'notepad.exe' (windows) o 'getedit'/'nano' (linux)\n");
    #ifdef _WIN32
        printf("Se abrira el Bloc de Notas. Cierralo para continuar.\n");
        system("notepad.exe");
    #else
        printf("Intentando abrir gedit/nano. Cierralo para continuar.\n");
        system("nano"); // O "nano" en Linux
    #endif
    printf("Programa en c continua después de cerrar el editor.\n\n");

    printf("--- Fin de la ejecución de comandos --- \n");

    return 0;
}