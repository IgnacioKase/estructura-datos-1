#include "gpila.h"

struct _Pila {
    void *dato;
    struct _Pila *sig;
};

Pila pila_crear() {
    Pila pila = NULL;
    return pila;
}

int pila_es_vacia(Pila pila) {
    return pila == NULL;
}

void *pila_ultimo(Pila pila) {
    return pila->dato;
}

void pila_apilar(Pila *pila, void *dato) {
    Pila nuevoNodo = malloc(sizeof(SPila));
    nuevoNodo->sig = *pila;
    nuevoNodo->dato = dato;
    *pila = nuevoNodo;
}

void pila_desapilar(Pila *pila) {
    Pila temp = (*pila)->sig;
    free(pila);
    *pila = temp;
}

void pila_destruir(Pila pila) {
    Pila pilaAEliminar;
    while (pila != NULL) {
        pilaAEliminar = pila;
        pila = pila->sig;
        if (pilaAEliminar->dato != NULL)
            free(pilaAEliminar->dato);
        free(pilaAEliminar);
    }
}