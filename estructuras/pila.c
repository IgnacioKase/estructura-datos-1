#include "pila.h"

struct _Pila {
    int dato;
    struct _Pila *sig;
};

Pila pila_crear() {
    Pila pila = NULL;
    return pila;
}

int pila_es_vacia(Pila pila) {
    return pila == NULL;
}

int pila_ultimo(Pila pila) {
    return pila->dato;
}

void pila_apilar(Pila *pila, int dato) {
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

void pila_imprimir(Pila pila) {
    for (Pila temp = pila; temp->sig != NULL; temp = temp->sig)
        printf("%d\n", temp->dato);
}

void pila_destruir(Pila pila) {
    Pila pilaAEliminar;
    while (pila != NULL) {
        pilaAEliminar = pila;
        pila = pila->sig;
        free(pilaAEliminar);
    }
}