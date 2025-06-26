#include <stdio.h>
#include <stdlib.h>

// Definición estructura del nodo
struct Nodo
{
    int dato;
    struct Nodo *siguiente;
};

// Puntero para inicio de la lista
struct Nodo *cabeza = NULL;

// función para inserar un nodo al incio de la lista
void insertarAlInicio(int valor)
{
    struct Nodo *nuevoNodo = (struct Nodo *) malloc(sizeof(struct Nodo));
    if (nuevoNodo == NULL)
    {
        perror("Error al asignaar memoria para nuevo nodo");
        exit(EXIT_FAILURE);
    }

    nuevoNodo->dato = valor;
    nuevoNodo->siguiente = cabeza; //El nuevo nodo apunta a la antigua cabeza
    cabeza = nuevoNodo; //la cabeza ahora es el nuevo nodo
}

// Función para imprmir elementos de la lista

void imprimirLista()
{
    struct Nodo *actual = cabeza;
    printf("Lista: ");
    while (actual != NULL)
    {
        printf("%d -> ", actual->dato);
        actual = actual->siguiente;
    }
    printf("NULL\n");
}

void liberarLista()
{
    struct Nodo *actual = cabeza;
    struct Nodo *siguienteNodo;

    while (actual !=NULL)
    {
        siguienteNodo = actual->siguiente; //Guarda el siguiente antes de liberar
        free(actual); // Libera el nodo actual
        actual = siguienteNodo; //mueve al siguiente nodo
    }

    cabeza = NULL; // La lista ahora está vacía
    printf("Memoria de la lista liberada. \n");
}

int main()
{
    printf("Creando lista enlazada... \n");
    insertarAlInicio(30);
    insertarAlInicio(50);
    insertarAlInicio(60);
    imprimirLista();

    printf("\nLiberando lista...\n");
    liberarLista();
    imprimirLista();

    return 0;
}