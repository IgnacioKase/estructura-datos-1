#include "pila.h"

struct _Pila {
    int datos[MAX_PILA];
    int ultimo;
};

Pila pila_crear() {
    Pila pila = malloc(sizeof(SPila));
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
    free(pila);
}