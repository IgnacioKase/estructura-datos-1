#include "pila.h"

struct _Pila {
    int *datos;
    int largo;
    int ultimo;
};

Pila pila_crear() {
    Pila pila = malloc(sizeof(SPila));
    pila->datos = malloc(sizeof(int) * MAX_PILA);
    pila->largo = MAX_PILA;
    pila->ultimo = -1;
    return pila;
}

int pila_es_vacia(Pila pila) {
    return pila->ultimo == -1;
}

int pila_ultimo(Pila pila) {
    return pila->datos[pila->ultimo];
}

void pila_apilar(Pila pila, int dato) {
    if (pila->largo - 1 == pila->ultimo) {
        pila->datos = realloc(pila->datos, pila->largo * 2);
        pila->largo *= 2;
    }
    pila->ultimo++;
    pila->datos[pila->ultimo] = dato;
}

void pila_desapilar(Pila pila) {
    pila->ultimo--;
}

void pila_imprimir(Pila pila) {
    for (size_t i = 0; i <= pila->ultimo; i++) {
        printf("%d\n", pila->datos[i]);
    }
}

void pila_destruir(Pila pila) {
    free(pila->datos);
    free(pila);
}