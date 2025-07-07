//
// Created by sebastian-m on 7/7/25.
//
#ifdef MI_MODULO_H
#define MI_MODULO_H

// Declaración incompleta de la estructura
// El contenido de esta estructura es opaco para quien incluye este .h
typedef struct MiTipoOpaque MiTipoOpaque; // Ahora se puede usar el tipo

// Prototipos de funciones publicas (API)

MiTipoOpaque *mi_tipo_crear(int valor_inicial); // Función para crear/inicializar
void mi_tipo_procesar(MiTipoOpaque *instancia); // Función para operar
int mi_tipo_obtener_dato(MiTipoOpaque *instancia); // Función para obtener datos
void mi_tipo_destruir(MiTipoOpaque *instancia); // Función para liberar recursos

#endif
