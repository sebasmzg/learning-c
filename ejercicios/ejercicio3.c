#include <stdio.h>
/*
* Imagina que estás controlando un dispositivo con varias configuraciones, donde cada configuración se representa como un bit en una variable unsigned char.
CONFIG_SENSOR_ACTIVO (Bit 0): El sensor está encendido.
CONFIG_LED_ENCENDIDO (Bit 1): El LED indicador está encendido.
CONFIG_MODO_AHORRO_ENERGIA (Bit 2): El dispositivo está en modo de bajo consumo.
CONFIG_ALARMA_ACTIVADA (Bit 3): La alarma del dispositivo está lista.

Tu programa debe:
1.Define las máscaras de bits para cada configuración.
2.Inicializa una variable estado_dispositivo a 0x00 (todos los bits apagados).
3.Activa el CONFIG_SENSOR_ACTIVO y el CONFIG_ALARMA_ACTIVADA.
4.Verifica si el CONFIG_LED_ENCENDIDO está activo. Imprime el resultado.
5.Alterna el CONFIG_MODO_AHORRO_ENERGIA.
6.Desactiva el CONFIG_ALARMA_ACTIVADA.
En cada paso, imprime el estado actual del dispositivo en formato hexadecimal y binario (puedes reutilizar o adaptar una función de impresión binaria si la tienes).
 */
// 1- Mascaras de bits
#define CONFIG_SENSOR_ACTIVO        0x01 // Bit 0: 00000001
#define CONFIG_LED_ENCENDIDO        0x02 // Bit 1: 00000010
#define CONFIG_MODO_AHORRO_ENERGIA  0x04 // Bit 2: 00000100
#define CONFIG_ALARMA_ACTIVADA      0x08 // Bit 3: 00001000

// print byte in bin
void imprimir_binario(unsigned char valor)
{
    for (int i = 7; i >= 0; i--)
    {
        printf("%d",(valor >>  i) & 1);
    }
}

void imprimir_estado(unsigned char estado, const char* descripcion)
{
    printf("Estado: %s\n", descripcion);
    printf("Estado: 0x%02X | Binario: ", estado);
    imprimir_binario(estado);
    printf("\n\n");
}

int main()
{
    // 2- Inicializar variable status a 0x00 - todos los bits apagados
    unsigned char estado_dispositivo = 0x00;
    imprimir_estado(estado_dispositivo, "Estado inicial: Todos los bits apagados.");
    // 3- Activar el CONFIG_SENSOR_ACTIVO y el CONFIG_ALARMA_ACTIVADA
    estado_dispositivo |= CONFIG_SENSOR_ACTIVO;
    estado_dispositivo |= CONFIG_ALARMA_ACTIVADA;
    imprimir_estado(estado_dispositivo, "Activando SENSOR_ACTIVO y ALARMA");
    //4- Verifica si el CONFIG_LED_ENCENDIDO está activo
    if (estado_dispositivo & CONFIG_LED_ENCENDIDO)
    {
        printf("El LED está activo\n");
    } else
    {
        printf("El LED está apagado\n");
    }
    printf("\n");
    // 5- Alterna el CONFIG_MODO_AHORRO_ENERGIA
    estado_dispositivo ^= CONFIG_MODO_AHORRO_ENERGIA;
    imprimir_estado(estado_dispositivo, "Alternando MODO_AHORRO_ENERGIA");
    // 6- Desactivar CONFIG_ALARMA_ACTIVADA
    estado_dispositivo &= ~CONFIG_ALARMA_ACTIVADA;
    imprimir_estado(estado_dispositivo, "Desactivando ALARMA_ACTIVADA");
    return 0;
}