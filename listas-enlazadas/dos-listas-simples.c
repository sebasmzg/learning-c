#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura de nodo para una lista enlazada simple
typedef struct Nodo
{
    int dato;
    struct Nodo *siguiente;
} Nodo;

// Función para insertar un nodo final (útil para construir las listas).
// Recibe un puntero a la cabeza de la lista
void insertarAlFinal (Nodo **cabezaRef, int valor)
{
    Nodo *nuevoNodo = (Nodo *) malloc(sizeof(Nodo));

    if (nuevoNodo == NULL)
    {
        perror("Error al asignar memoria");
        exit(EXIT_FAILURE);
    }

    nuevoNodo->dato = valor;
    nuevoNodo->siguiente = NULL;

    printf(" [Insertar %d] Nodo creado en dirección: %p\n", valor, (void*)nuevoNodo);

    if (*cabezaRef == NULL) // Si la lista está vacía, el nuevo nodo es la cabeza
    {
        *cabezaRef = nuevoNodo;
    } else // Si la lista está vacía, recorremos hasta el final
    {
        Nodo *temp = *cabezaRef;

        while (temp->siguiente != NULL)
        {
            temp = temp->siguiente;
        }

        temp->siguiente = nuevoNodo;
    }
}

// Imprimir la lista
// parametro nombre de lista solo para ver ubicación
void imprimirLista (const char* nombre_lista, Nodo *cabeza)
{
    Nodo *actual = cabeza;

    if (actual == NULL)
    {
        printf("%s: Vacía (Cabeza: %p)\n",nombre_lista, (void*)cabeza);
        return;
    }

    printf("%s (Cabeza: %p)\n",nombre_lista, (void*)cabeza);
    int i = 0;
    while (actual != NULL)
    {
        printf("Nodo %d: Dato = %d, Dir = %p, Siguiente = %p\n",i++, actual->dato, (void*)actual, (void*)actual->siguiente);
        actual = actual->siguiente;
    }
    printf("NULL\n");
}

// Liberar memoria de la lista
void liberarLista(Nodo **cabezaRef)
{
    Nodo *actual = *cabezaRef;
    Nodo *siguienteNodo;
    printf("\n--- LIBERANDO LISTA ---\n");
    while (actual != NULL)
    {
        siguienteNodo = actual->siguiente;
        printf("  Liberando nodo en: %p (Dato: %d)\n", (void*)actual, actual->dato);
        free(actual);
        actual = siguienteNodo;
    }
    *cabezaRef = NULL; // La lista ahora está vacía
    printf("Memoria de la lista liberada. Cabeza ahora es %p.\n", (void*)*cabezaRef);
}

// --- Enlazar dos listas enlazadas simples ---
// Toma las cabezas de la lista A y la lista
// Modifica la lista A para que su ultimo nodo apunte al primer nodo de la lista B.
// Retorna la cabeza de la lista A (que ahora es el inicio de la lista combinada).
Nodo* enlazarListas(Nodo *cabezaA, Nodo *cabezaB)
{
    printf("\n--- ENLAZANDO LISTAS ---\n");
    printf(" Cabeza lista A (entrada): %p\n",(void*)cabezaA);
    printf(" Cabeza lista B (entrada): %p\n",(void*)cabezaB);
    // Si la Lista A está vacía, simplemente devolvemos la Lista B..
    // En este caso, Lista B se convierte en la nueva Lista A.
    if (cabezaA == NULL)
    {
        printf("  Lista A esta vacia. Devolviendo Lista B como combinada.\n");
        return cabezaB;
    }

    // Si la lista B está vacía, no hay nada que enlazar, devolvemos la Lista A.
    if (cabezaB == NULL)
    {
        printf("  Lista B esta vacia. Devolviendo Lista A como combinada.\n");
        return cabezaA;
    }

    // Encontrar último nodo de la lista A.
    Nodo *actualA = cabezaA;
    while (actualA->siguiente != NULL)
    {
        actualA = actualA->siguiente;
    }
    printf(" Último nodo de la lista A encontrado en: %p (Dato: %d)\n", (void*)actualA, actualA->dato);
    printf(" Su puntero 'siguiente' actual es: %p\n", (void*)actualA->siguiente);

    // Hacer que el último nodo de la lista A apunte a la cabeza de la lista B
    actualA->siguiente = cabezaB;
    printf("  Puntero 'siguiente' del ultimo nodo de Lista A actualizado a: %p (apunta a la cabeza de Lista B)\n", (void*)actualA->siguiente);

    printf("--- ENLACE COMPLETADO ---\n");

    // La cabeza de la lista A es ahora la cabeza de la lista combinada
    return cabezaA;
}

int main()
{
    // Declarar las cabezas de las dos listas
    Nodo *listaA = NULL;
    Nodo *listaB = NULL;

    printf("--- Creando Lista A ---\n");
    insertarAlFinal(&listaA, 10);
    insertarAlFinal(&listaA, 20);
    insertarAlFinal(&listaA, 30);
    imprimirLista("Lista A (original)", listaA);

    printf("--- Creando Lista B ...\n");
    insertarAlFinal(&listaB,40);
    insertarAlFinal(&listaB,50);
    insertarAlFinal(&listaB,60);
    imprimirLista("Lista B (original)", listaB);

    printf("\n--- Enlazando lista A y lista B ---\n");
    // Al enlazar lista A se convierte en la cabeza de la lista combinada
    listaA = enlazarListas(listaA, listaB);

    printf("\n--- Mostrando lista combinada ---\n");
    imprimirLista("Lista combinada", listaA);

    // NOTA:
    // Ahora lista B ya no es el inicio de una lista separada,
    // sino que es un puntero que apunta a la mitad de la  nueva lista combinada.
    // si se trata de imprimir lista B solo se verà el resto de la lista desde 40.
    printf("Contenido lista B después de enlazar (no se debe liberar aparte):\n");
    imprimirLista("Puntero listaB", listaB);

    // Solo necesitamos liberar la cabeza de la lista combinada (lista A)
    // para liberar toda la memoria.
    liberarLista(&listaA);

    printf("\n--- ESTADO FINAL ---\n");
    imprimirLista("Lista A (despues de liberar)", listaA); // Debería ser vacía
    imprimirLista("Puntero listaB (despues de liberar listaA)", listaB); // Su contenido es ahora inválido/liberado
    // Es buena práctica poner listaB a NULL también, ya que la memoria a la que apuntaba ya no es válida.
    listaB = NULL;

    return 0;
}