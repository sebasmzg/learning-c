#include <stdio.h>

int main()
{
    FILE *log_file;
    char my_buffer[1024]; // Buffer personalizado de 1kb

    log_file = fopen("app.log", "wb");
    if (log_file == NULL)
    {
        perror("Error al abrir 'log.txt'");
        return 1;
    }

    // Configurar buffering completo con el buffer personalizado
    setvbuf(log_file, my_buffer, _IOFBF, sizeof(my_buffer));

    fprintf(log_file, "Este es el primer mensaje\n");
    fprintf(log_file, "Este es el segundo mensaje\n");
    // Los mensajes no se escribirán en el archivo hasta que el buffer se llene
    // o se llame a fflush, o se cierre el archivo

    fflush(log_file); // Forzar la escritura al archivo
    printf("Mensajes escritos y buffer vaciado.\n");

    fclose(log_file);

    return 0;
}