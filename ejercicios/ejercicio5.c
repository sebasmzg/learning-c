#include <stdio.h>   // Para printf, perror
#include <stdlib.h>  // Para calloc, realloc, free
#include <string.h>  // Para memcpy (usada en la funcion corregida)

// --- Funciones de Utilidad ---

// Imprime los elementos actuales del array dinámico.
void imprimir(int* arr, int n) {
    if (arr == NULL || n == 0) {
        printf("Lista: [] (Vacia)\n");
        return;
    }
    printf("Lista: [");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i != n - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

// --- Funciones de Gestion del Array Dinamico ---

// Crea un nuevo array dinámico inicializado con ceros.
// Es util para la primera asignacion de memoria.
int* crear(int n_inicial) {
    if (n_inicial < 0) {
        printf("Error: El tamaño inicial no puede ser negativo.\n");
        return NULL;
    }
    // calloc inicializa la memoria a cero.
    int* array = (int*) calloc(n_inicial, sizeof(int));
    if (array == NULL) {
        perror("Error al asignar memoria inicial al array");
        return NULL;
    }
    printf("Array inicializado con capacidad para %d elementos.\n", n_inicial);
    return array;
}

// Asigna un valor a un indice especifico.
// arr: puntero al array dinamico (puntero a puntero para poder modificar 'arr' en main si es NULL).
// n: puntero al tamaño logico actual del array.
// index: indice donde se desea asignar el valor.
// valor: el valor a asignar.
void asignar(int** arr, int* n, int index, int valor) {
    // Validacion basica del indice.
    // El indice debe estar dentro del rango [0, *n - 1].
    if (*arr == NULL || index < 0 || index >= *n) {
        printf("Error: Indice invalido para asignar. No existe tal posicion.\n");
        return;
    }
    (*arr)[index] = valor; // Accede al array y asigna el valor.
    printf("Valor %d asignado al indice %d.\n", valor, index);
}

// Inserta un valor al final del array dinámico.
// arr: puntero al array dinamico (puntero a puntero para permitir realloc).
// n: puntero al tamaño logico actual del array.
// valor: el valor a insertar.
void insertar(int** arr, int* n, int valor) {
    // Incrementa el tamaño logico para el nuevo elemento.
    (*n)++;

    // Reasigna memoria para el nuevo tamaño.
    // realloc(NULL, size) es equivalente a malloc(size).
    int* nuevo_arr = (int*) realloc(*arr, (*n) * sizeof(int));

    // Verifica si la reasignacion de memoria fue exitosa.
    if (nuevo_arr == NULL) {
        perror("Error al expandir memoria al array para insercion al final");
        (*n)--; // Deshace el incremento de n si la reasignacion falla.
        return;
    }

    // Actualiza el puntero del array original al nuevo bloque de memoria.
    *arr = nuevo_arr;

    // Asigna el valor al ultimo elemento del array.
    (*arr)[*n - 1] = valor;
    printf("Valor %d insertado al final. Nuevo tamaño: %d\n", valor, *n);
}

// Inserta un valor en una posicion especifica del array dinamico.
// arr: puntero al array dinamico (puntero a puntero para permitir realloc).
// n: puntero al tamaño logico actual del array.
// index: la posicion donde se desea insertar el valor.
// valor: el valor a insertar.
void insertar_en_posicion(int** arr, int *n, int index, int valor) {
    // Validar el indice para insercion: debe estar en [0, *n].
    // Si index == *n, se inserta al final, lo cual es valido.
    if (index < 0 || index > *n) {
        printf("Error: Indice invalido para insercion en posicion (%d). Debe ser entre 0 y %d.\n", index, *n);
        return;
    }

    // Incrementar el tamaño logico para el nuevo elemento.
    (*n)++;

    // Reasignar memoria para el nuevo tamaño.
    int* nuevo_arr = (int*) realloc(*arr, (*n) * sizeof(int));

    // Verificar si realloc falló.
    if (nuevo_arr == NULL) {
        perror("Error al reasignar memoria en insertar_en_posicion");
        (*n)--; // Deshacer el incremento de n si falla.
        return;
    }

    // **CRÍTICO**: Actualizar el puntero del array original al nuevo bloque de memoria.
    // Esto es fundamental antes de intentar acceder a cualquier elemento.
    *arr = nuevo_arr;

    // Desplazar elementos para abrir espacio en la posicion 'index'.
    // Los elementos desde 'index' en adelante deben moverse una posicion a la derecha.
    // Esto se hace eficientemente con memmove.
    // memmove(destino, origen, numero_de_bytes)
    // El destino es la posicion 'index + 1'
    // El origen es la posicion 'index'
    // El numero de bytes es la cantidad de elementos a mover * su tamaño.
    // Cantidad de elementos a mover: (*n - 1) - index (desde el nuevo ultimo elemento hasta el indice a desplazar)
    // Pero si usamos arr[index+1] como destino y arr[index] como origen,
    // debemos mover los elementos desde index hasta el penultimo (antes de la insercion).
    // La cantidad de elementos a mover es el (tamaño actual - 1 - indice de insercion).
    if (index < *n - 1) { // Solo desplaza si no se inserta al final
        memmove(&(*arr)[index + 1], &(*arr)[index], (*n - 1 - index) * sizeof(int));
    }
    // Alternativa al memmove usando un bucle (menos eficiente pero mas explicito):
    /*
    for (int i = *n - 1; i > index; i--) {
        (*arr)[i] = (*arr)[i - 1];
    }
    */

    // Insertar el nuevo valor en la posicion deseada.
    (*arr)[index] = valor;
    printf("Valor %d insertado en posicion %d. Nuevo tamaño: %d\n", valor, index, *n);
}

int buscar(int* arr, int* n, int valor){
    // 1. Validar que el array no sea NULL y no esté vacío.
    // No podemos buscar en un array que no existe o no tiene elementos.
    if (arr == NULL || n <= 0) {
        // En un caso real, podrías imprimir un mensaje de error aquí,
        // pero para una función de búsqueda, -1 ya indica "no encontrado".
        return -1;
    }
    // 2. Recorrer el array desde el inicio hasta el final (n-1).
    // Usamos un bucle for tradicional para iterar por los índices.
    for (int i = 0; i < *n; i++)
    {
        // 3. Comprobar si el elemento actual coincide con el valor buscado.
        if (arr[i] == valor)
        {
            return i; // Si lo encontramos, devolvemos su índice inmediatamente.
        }
    }
    // 4. Si el bucle termina sin encontrar el valor, significa que no está en el array.
    return -1;
}

// Elimina un elemento en una posicion especifica y redimensiona el array.
// arr: puntero al array dinamico (puntero a puntero para permitir realloc y free).
// n: puntero al tamaño logico actual del array.
// index: la posicion del elemento a eliminar.
void eliminar(int** arr, int* n, int index) {
    // Validacion del indice.
    // El indice debe estar dentro del rango [0, *n - 1].
    if (*arr == NULL || index < 0 || index >= *n) {
        printf("Error: Indice invalido para eliminacion (%d). Debe ser entre 0 y %d.\n", index, *n - 1);
        return;
    }

    int valor_eliminado = (*arr)[index]; // Guardar el valor a informar

    // Desplazar elementos para "tapar" el espacio del elemento eliminado.
    // Los elementos desde 'index + 1' se mueven una posicion a la izquierda.
    // Se puede usar memmove para mayor eficiencia.
    // El origen es la posicion 'index + 1'
    // El destino es la posicion 'index'
    // El numero de bytes es la cantidad de elementos restantes * su tamaño.
    // Cantidad de elementos restantes: (*n - 1) - index.
    if (index < *n - 1) { // Solo desplaza si no es el ultimo elemento
        memmove(&(*arr)[index], &(*arr)[index + 1], (*n - 1 - index) * sizeof(int));
    }
    // Alternativa al memmove usando un bucle:
    /*
    for (int i = index; i < *n - 1; i++) {
        (*arr)[i] = (*arr)[i + 1];
    }
    */

    // Decrementar el tamaño logico.
    (*n)--;

    // Si el array queda vacio, liberar la memoria y establecer el puntero a NULL.
    if (*n == 0) {
        free(*arr);
        *arr = NULL;
        printf("Valor %d eliminado del indice %d. Array vacio. Memoria liberada.\n", valor_eliminado, index);
        return;
    }

    // Redimensionar el array a su nuevo tamaño mas pequeño.
    int* nuevo_arr = (int*) realloc(*arr, (*n) * sizeof(int));

    // Nota: realloc puede devolver NULL si falla, pero en el caso de reduccion de tamaño
    // o liberacion a cero, no es tan critico perder el puntero original si la
    // operacion previa (desplazamiento) ya se realizo. Sin embargo, sigue siendo
    // buena practica verificar y manejar el error apropiadamente.
    // Si la reasignacion falla, el puntero original (*arr) sigue siendo valido
    // y apunta al bloque de memoria con el tamaño anterior, aunque el tamaño logico (*n)
    // ya se haya reducido.
    if (nuevo_arr == NULL) {
        perror("Advertencia: Fallo al reducir la memoria del array despues de eliminar. El puntero original sigue siendo valido.");
        // No deshacer (*n)++ aqui, ya que el elemento ya se elimino logicamente.
        // El array simplemente ocupa mas memoria de la necesaria temporalmente.
    } else {
        *arr = nuevo_arr; // Actualiza el puntero si realloc fue exitoso
    }
    printf("Valor %d eliminado del indice %d. Nuevo tamaño: %d\n", valor_eliminado, index, *n);
}

void invertir(int** arr, int* n)
{
    // 1. Validar que el array no sea NULL y tenga al menos 2 elementos para invertir.
    // Un array con 0 o 1 elemento ya está "invertido" o no necesita inversión.
    if (arr == NULL || *n <= 1) {
        printf("No se puede invertir: el array es nulo o tiene 0 o 1 elemento.\n");
        return;
    }
    // 2. Usar dos índices: 'izquierda' que empieza al principio y 'derecha' que empieza al final.
    int izquierda = 0;
    int derecha = *n - 1;
    int temp; // Variable temporal para el intercambio.
    // 3. Iterar mientras 'izquierda' sea menor que 'derecha'.
    // Esto asegura que no se invierta un elemento consigo mismo o se crucen sin necesidad.
    while (izquierda < derecha) {
        // 4. Intercambiar los elementos en las posiciones 'izquierda' y 'derecha'.
        temp = (*arr)[izquierda];    // Guarda el valor de la izquierda.
        (*arr)[izquierda] = (*arr)[derecha]; // Asigna el valor de la derecha a la izquierda.
        (*arr)[derecha] = temp;      // Asigna el valor guardado (original de izquierda) a la derecha.

        // 5. Mover los índices hacia el centro.
        izquierda++; // Mueve el índice izquierdo una posición a la derecha.
        derecha--;   // Mueve el índice derecho una posición a la izquierda.
    }
}

int* concatenar(int* arr1, int n1 ,int* arr2, int n2, int* n_resultado)
{
    // Validar parámetros de entrada
    if (n_resultado == NULL) {
        printf("Error: Puntero n_resultado es NULL\n");
        return NULL;
    }

    // Calcular el tamaño del nuevo array
    int new_size = n1 + n2;
    *n_resultado = new_size;

    // Si ambos arrays están vacíos, retornar NULL
    if (new_size == 0) {
        printf("Ambos arrays están vacíos. Retornando NULL.\n");
        return NULL;
    }

    // Asignar memoria para el nuevo array
    int* new_arr = (int*) malloc(new_size * sizeof(int));
    if (new_arr == NULL)
    {
        printf("Error: Al asignar memoria en concatenar arreglos");
        *n_resultado = 0;
        return NULL;
    }

    // Copiar elementos de arr1 al inicio del nuevo array
    if (arr1 != NULL && n1 > 0)
    {
        memcpy(new_arr, arr1, n1 * sizeof(int));
    }
    // Copiar elementos de arr2 después de los elementos de arr1
    if (arr2 != NULL && n2 > 0) {
        memcpy(new_arr + n1, arr2, n2 * sizeof(int));
    }

    return new_arr;
}

void eliminar_duplicados(int** arr, int* n)
{
    // Validar parámetros de entrada
    if (*arr == NULL || *n <= 1) {
        printf("No hay duplicados que eliminar: array NULL o tiene 0 o 1 elemento.\n");
        return;
    }

    int nuevo_size = 0; // Tamaño del array sin duplicados

    // Recorrer cada elemento del array original
    for (int i = 0; i < *n; i++) {
        int elemento_actual = (*arr)[i];
        int es_duplicado = 0;

        // Verificar si el elemento actual ya existe en la parte "limpia" del array
        for (int j = 0; j < nuevo_size; j++) {
            if ((*arr)[j] == elemento_actual) {
                es_duplicado = 1;
                break;
            }
        }

        // Si no es duplicado, mantenerlo en la posición correspondiente
        if (!es_duplicado) {
            (*arr)[nuevo_size] = elemento_actual;
            nuevo_size++;
        }
    }

    // Si no se eliminó ningún duplicado, no hay cambios
    if (nuevo_size == *n) {
        printf("No se encontraron duplicados en el array.\n");
        return;
    }

    // Actualizar el tamaño lógico
    *n = nuevo_size;

    // Si el array queda vacío (caso muy raro), liberar memoria
    if (*n == 0) {
        free(*arr);
        *arr = NULL;
        printf("Array vacío después de eliminar duplicados. Memoria liberada.\n");
        return;
    }

    // Redimensionar el array al nuevo tamaño más pequeño
    int* nuevo_arr = (int*) realloc(*arr, (*n) * sizeof(int));

    if (nuevo_arr == NULL) {
        printf("Advertencia: No se pudo reducir la memoria después de eliminar duplicados.\n");
        // El array original sigue siendo válido, solo ocupa más memoria de la necesaria
    } else {
        *arr = nuevo_arr;
    }

    printf("Duplicados eliminados. Nuevo tamaño: %d\n", *n);
}

int contar_bits_totales(int* arr, int n)
{
    // Validar parámetros de entrada
    if (arr == NULL || n <= 0) {
        printf("Error: Array NULL o tamaño inválido\n");
        return 0;
    }
    int total_bits = 0; // Contador total de bit activos

    // Recorrer cada número del array
    for (int i = 0; i < n; i++)
    {
        int numero = arr[i];
        int bits_activos = 0;

        // Contar bits activos del número actual
        // Nota: Usamos unsigned para manejar números negativos correctament
        unsigned int num_unsigned = (unsigned int)numero;

        while (num_unsigned > 0)
        {
            bits_activos += num_unsigned & 1; // Verificar si el bit menos significatico es 1
            num_unsigned >>= 1; // Desplazar todos los bits a la derecha
        }
        total_bits += bits_activos;
        printf("Número %d tiene %d bits activos\n", numero, bits_activos);
    }

    printf("Total de bits activos en el array: %d\n", total_bits);
    return total_bits;
}

// Libera la memoria del array y establece el puntero a NULL.
void liberar_array(int** arr, int* n) {
    if (*arr != NULL) {
        free(*arr);
        *arr = NULL; // Es crucial establecer el puntero a NULL despues de free
        *n = 0;      // Establecer el tamaño logico a cero
        printf("Memoria del array liberada.\n");
    } else {
        printf("El array ya esta NULL o vacio. Nada que liberar.\n");
    }
}

// --- Funcion Principal (Main) para Pruebas ---

int main() {
    int n = 0;       // Tamaño lógico actual del array (número de elementos)
    int* arr = NULL; // Puntero al array dinámico, inicialmente NULL

    printf("--- Pruebas de Lista Dinamica en C ---\n");
    imprimir(arr, n);

    // --- PRUEBAS DE INSERCION AL FINAL ---
    printf("\n--- INSERTAR AL FINAL ---\n");
    insertar(&arr, &n, 10); // Insertar 10
    imprimir(arr, n);
    insertar(&arr, &n, 20); // Insertar 20
    imprimir(arr, n);
    insertar(&arr, &n, 30); // Insertar 30
    imprimir(arr, n);

    // --- PRUEBAS DE ASIGNAR ---
    printf("\n--- ASIGNAR VALOR --- \n");
    asignar(&arr, &n, 0, 5); // Asignar 5 en indice 0
    imprimir(arr, n);
    asignar(&arr, &n, 2, 25); // Asignar 25 en indice 2
    imprimir(arr, n);
    asignar(&arr, &n, 5, 99); // Error: Indice fuera de rango
    imprimir(arr, n);

    // --- PRUEBAS DE INSERTAR EN POSICION ---
    printf("\n--- INSERTAR EN POSICION ---\n");
    insertar_en_posicion(&arr, &n, 1, 15); // Insertar 15 en posicion 1
    imprimir(arr, n); // Esperado: [5, 15, 20, 25]

    insertar_en_posicion(&arr, &n, 0, 1); // Insertar 1 en posicion 0
    imprimir(arr, n); // Esperado: [1, 5, 15, 20, 25]

    insertar_en_posicion(&arr, &n, n, 100); // Insertar 100 al final (usando 'n' como indice)
    imprimir(arr, n); // Esperado: [1, 5, 15, 20, 25, 100]

    insertar_en_posicion(&arr, &n, 99, 500); // Error: Indice invalido
    imprimir(arr, n); // Lista no cambia

    // --- PRUEBAS DE BUSQUEDA ---
    printf("\n--- PRUEBAS DE BUSQUEDA ---\n");
    int valor_a_buscar;
    int indice_encontrado;

    valor_a_buscar = 15;
    indice_encontrado = buscar(arr, &n, valor_a_buscar);
    if (indice_encontrado != -1) {
        printf("El valor %d fue encontrado en el indice: %d\n", valor_a_buscar, indice_encontrado); // Esperado: 2
    } else {
        printf("El valor %d NO fue encontrado.\n", valor_a_buscar);
    }

    valor_a_buscar = 5;
    indice_encontrado = buscar(arr, &n, valor_a_buscar);
    if (indice_encontrado != -1) {
        printf("El valor %d fue encontrado en el indice: %d\n", valor_a_buscar, indice_encontrado); // Esperado: 0
    } else {
        printf("El valor %d NO fue encontrado.\n", valor_a_buscar);
    }

    valor_a_buscar = 40;
    indice_encontrado = buscar(arr, &n, valor_a_buscar);
    if (indice_encontrado != -1) {
        printf("El valor %d fue encontrado en el indice: %d\n", valor_a_buscar, indice_encontrado); // Esperado: 5
    } else {
        printf("El valor %d NO fue encontrado.\n", valor_a_buscar);
    }

    valor_a_buscar = 99; // Valor que no esta en la lista
    indice_encontrado = buscar(arr, &n, valor_a_buscar);
    if (indice_encontrado != -1) {
        printf("El valor %d fue encontrado en el indice: %d\n", valor_a_buscar, indice_encontrado);
    } else {
        printf("El valor %d NO fue encontrado.\n", valor_a_buscar); // Esperado: NO encontrado
    }

    // --- PRUEBAS DE INVERTIR ---
    printf("\n--- PRUEBAS DE INVERTIR ARREGLO ---\n");
    printf("Array antes de invertir: ");
    imprimir(arr, n);

    invertir(&arr, &n); // Invertimos el array
    printf("Array despues de invertir: ");
    imprimir(arr, n); // Esperado: [40, 30, 20, 15, 10, 5]

    // Probar invertir un array con un número impar de elementos
    insertar(&arr, &n, 50); // Agregamos un elemento para hacerlo impar
    printf("\nArray impar antes de invertir: ");
    imprimir(arr, n); // Esperado: [40, 30, 20, 15, 10, 5, 50]

    invertir(&arr, &n);
    printf("Array impar despues de invertir: ");
    imprimir(arr, n); // Esperado: [50, 5, 10, 15, 20, 30, 40]

    // Probar invertir un array con 1 elemento
    printf("\nProbando invertir un array con 1 elemento...\n");
    liberar_array(&arr, &n); // Vaciar el array
    insertar(&arr, &n, 99);
    imprimir(arr, n);
    invertir(&arr, &n);
    imprimir(arr, n); // Deberia seguir siendo [99]

    // Probar invertir un array vacío
    printf("\nProbando invertir un array vacio...\n");
    liberar_array(&arr, &n); // Asegurarse de que esta vacio
    invertir(&arr, &n);
    imprimir(arr, n); // Deberia seguir siendo []


    // --- PRUEBAS DE ELIMINAR ---
    printf("\n--- ELIMINAR ELEMENTOS ---\n");
    eliminar(&arr, &n, 2); // Eliminar elemento en indice 2 (era 15)
    imprimir(arr, n); // Esperado: [1, 5, 20, 25, 100]

    eliminar(&arr, &n, 0); // Eliminar elemento en indice 0 (era 1)
    imprimir(arr, n); // Esperado: [5, 20, 25, 100]

    eliminar(&arr, &n, n - 1); // Eliminar el ultimo elemento (era 100)
    imprimir(arr, n); // Esperado: [5, 20, 25]

    eliminar(&arr, &n, 99); // Error: Indice fuera de rango
    imprimir(arr, n); // Lista no cambia

    // --- VACIAMIENTO Y LIBERACION ---
    printf("\n--- VACIAR Y LIBERAR ---\n");
    while (n > 0) {
        eliminar(&arr, &n, 0); // Eliminar repetidamente el primer elemento
        imprimir(arr, n);
    }

    // Intentar liberar un array ya liberado/NULL (deberia imprimir mensaje)
    liberar_array(&arr, &n);
    imprimir(arr, n); // Deberia mostrar vacia y puntero NULL

    // Intentar asignar a un array NULL (deberia dar error)
    printf("\nIntentando asignar a un array NULL...\n");
    asignar(&arr, &n, 0, 999);

    // --- PRUEBAS DE CONCATENAR ---
    printf("\n--- PRUEBAS DE CONCATENAR ARRAYS ---\n");

    // Crear dos arrays para concatenar
    int* arr1 = crear(3);
    int* arr2 = crear(2);
    int n1 = 3, n2 = 2;

    // Llenar el primer array
    asignar(&arr1, &n1, 0, 1);
    asignar(&arr1, &n1, 1, 2);
    asignar(&arr1, &n1, 2, 3);
    printf("Array 1: ");
    imprimir(arr1, n1);

    // Llenar el segundo array
    asignar(&arr2, &n2, 0, 4);
    asignar(&arr2, &n2, 1, 5);
    printf("Array 2: ");
    imprimir(arr2, n2);

    // Concatenar los arrays
    int n_resultado;
    int* arr_concatenado = concatenar(arr1, n1, arr2, n2, &n_resultado);
    printf("Array concatenado: ");
    imprimir(arr_concatenado, n_resultado);

    // Liberar memoria
    free(arr1);
    free(arr2);
    free(arr_concatenado);

    // --- PRUEBAS DE ELIMINAR DUPLICADOS ---
    printf("\n--- PRUEBAS DE ELIMINAR DUPLICADOS ---\n");

    // Crear un array con duplicados
    int* arr_duplicados = crear(8);
    int n_duplicados = 8;

    // Llenar con números que incluyen duplicados: [1, 2, 2, 3, 1, 4, 3, 5]
    asignar(&arr_duplicados, &n_duplicados, 0, 1);
    asignar(&arr_duplicados, &n_duplicados, 1, 2);
    asignar(&arr_duplicados, &n_duplicados, 2, 2);
    asignar(&arr_duplicados, &n_duplicados, 3, 3);
    asignar(&arr_duplicados, &n_duplicados, 4, 1);
    asignar(&arr_duplicados, &n_duplicados, 5, 4);
    asignar(&arr_duplicados, &n_duplicados, 6, 3);
    asignar(&arr_duplicados, &n_duplicados, 7, 5);

    printf("Array con duplicados: ");
    imprimir(arr_duplicados, n_duplicados);

    // Eliminar duplicados (esperado: [1, 2, 3, 4, 5])
    eliminar_duplicados(&arr_duplicados, &n_duplicados);
    printf("Array sin duplicados: ");
    imprimir(arr_duplicados, n_duplicados);

    // Probar con array sin duplicados
    printf("\nProbando eliminar duplicados en array que ya no tiene duplicados:\n");
    eliminar_duplicados(&arr_duplicados, &n_duplicados);
    imprimir(arr_duplicados, n_duplicados);

    // Liberar memoria
    free(arr_duplicados);

    // --- PRUEBAS DE CONTAR BITS TOTALES ---
    printf("\n--- PRUEBAS DE CONTAR BITS TOTALES ---\n");

    // Crear un array de prueba
    int* arr_bits = crear(4);
    int n_bits = 4;

    // Llenar con números de ejemplo: [5, 3, 7, 1]
    asignar(&arr_bits, &n_bits, 0, 5);  // 5 = 101 (2 bits)
    asignar(&arr_bits, &n_bits, 1, 3);  // 3 = 011 (2 bits)
    asignar(&arr_bits, &n_bits, 2, 7);  // 7 = 111 (3 bits)
    asignar(&arr_bits, &n_bits, 3, 1);  // 1 = 001 (1 bit)

    printf("Array para contar bits: ");
    imprimir(arr_bits, n_bits);

    // Contar bits totales (esperado: 2 + 2 + 3 + 1 = 8)
    int total = contar_bits_totales(arr_bits, n_bits);
    printf("Resultado esperado: 8, Resultado obtenido: %d\n", total);

    // Probar con array vacío
    printf("\nProbando con array vacío:\n");
    int resultado_vacio = contar_bits_totales(NULL, 0);

    // Liberar memoria
    free(arr_bits);

    return 0;
}