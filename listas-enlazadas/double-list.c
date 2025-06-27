#include <stdio.h>
#include <stdlib.h>

// estructura básica de nodo doblemente enlazado

typedef struct NodoDoble
{
    int dato;
    struct NodoDoble *anterior;
    struct NodoDoble *siguiente;
} NodoDoble;

// Punteros para la cabeza y la cola
NodoDoble *cabeza = NULL;
NodoDoble *cola = NULL;

// --- Función insertar al incio *****************

// Paso 1: Crear nuevo nodo y asignar dato
// Paso 2: El siguiente del nuevo nodo apunta a la cabeza actual
// Paso 3: El anterior del nuevo nodo apunta a NULL( porque es el nuevo primero )
// Paso 4: Si la lista no estaba vacía, el anterior de la antigua cabeza debe apuntar al nuevo nodo
// Paso 5: El cabeza ahora es el nuevo nodo
// Paso 6: Si la lista estaba vacía, la cola tambièn debe ser el nuevo nodo

void insertarAlInicio(int valor)
{
    NodoDoble *nuevoNodo = (NodoDoble * ) malloc(sizeof(NodoDoble));
    if (nuevoNodo == NULL)
    {
        perror("Error al asignar memoria a nuevo nodo");
        exit(EXIT_FAILURE);
    }

    nuevoNodo->dato = valor;
    nuevoNodo->anterior = NULL; // Es el nuevo primero

    if (cabeza == NULL)
    {
        nuevoNodo->siguiente = NULL;
        cabeza = nuevoNodo;
        cola = nuevoNodo;
    } else
    {
        nuevoNodo->siguiente = cabeza; // Nuevo nodo apunta a la antigua cabeza
        cabeza->anterior = nuevoNodo; // La antigua cabeza apunta hacia atrás al nuevo nodo
        cabeza = nuevoNodo; // Actualiza la cabeza
    }
}


// --- Función insertar al final *****************

// Paso 1: Crear nuevo nodo y asignar nuevo dato
// Paso 2: el anterior del nuevo apunta a la cola actual
// Paso 3: El siguiente del nuevo apunta a NULL ( porque es el nuevo último )
// Paso 4: Si la lista no estaba vacía, el siguiente de la antigua cola debe apuntar al nuevo nodo
// Paso 5: La cola ahora es el nuevo nodo
// Paso 6: Si la lista estaba vacía, la cabeza también debe ser el nuevo nodo

void insertarAlFinal(int valor)
{
    NodoDoble *nuevoNodo = (NodoDoble *) malloc(sizeof(NodoDoble));
    if (nuevoNodo == NULL)
    {
        perror("Error al asignar memoria a nuevo nodo");
        exit(EXIT_FAILURE);
    }

    nuevoNodo->dato = valor;
    nuevoNodo->anterior = NULL;

    if (cola == NULL)
    {
        nuevoNodo->siguiente = NULL;
        cabeza = nuevoNodo;
        cola = nuevoNodo;
    }else
    {
        nuevoNodo->anterior = cola; // Nuevo apunta a la antigua cola
        cola->siguiente = nuevoNodo; // La antigua cola apunta adelante del nuevo nodo
        cola = nuevoNodo; // Actualiza la cola
    }
};

// Hacia adelante
void imprimirListaAdelante()
{
    NodoDoble *actual = cabeza;
    printf("Lista (adelante): ");
    while (actual != NULL)
    {
        printf("%d ", actual->dato);
        if (actual->siguiente != NULL) {
            printf("<-> ");
        }
        actual = actual->siguiente;
    }
    printf("NULL\n");
};

// Hacia atrás
void imprimirListaAtras()
{
    NodoDoble *actual = cola;
    printf("Lista (atras): ");
    while (actual != NULL)
    {
        printf("Lista (atras):   ");
        while (actual != NULL)
        {
            printf("%d ", actual->dato);
            if (actual->anterior != NULL) {
                printf("<-> ");
            }
            actual = actual->anterior;
        }
    }
    printf("NULL\n");
};

// Liberar lista
void liberarLista()
{
    NodoDoble *actual = cabeza;
    NodoDoble *siguienteNodo;
    while (actual != NULL)
    {
        siguienteNodo = actual->siguiente; // Guarda el siguiente antes de liberar
        free(actual);
        actual = siguienteNodo;
    }

    cabeza = NULL;
    cola = NULL;

    printf("Memoria de la lista doblemente enlazada liberada.\n");
};


int main()
{
    printf("Iniciando operaciones con la lista doblemente enlazada.\n");

    insertarAlInicio(10);
    imprimirListaAdelante();
    imprimirListaAtras();

    insertarAlFinal(30);
    imprimirListaAdelante();
    imprimirListaAtras();

    insertarAlInicio(5);
    imprimirListaAdelante();
    imprimirListaAtras();

    insertarAlFinal(40);
    imprimirListaAdelante();
    imprimirListaAtras();

    printf("\n");
    liberarLista();
    imprimirListaAdelante();
    imprimirListaAtras();

    return 0;
}