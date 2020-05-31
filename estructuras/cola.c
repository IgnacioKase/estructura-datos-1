#include "cola.h"

Cola cola_crear() {
    Cola cola = malloc(sizeof(SCola));
    cola->primero = NULL;
    cola->ultimo = NULL;
    return cola;
}

int cola_es_vacia(Cola cola) {
    return cola->primero == NULL;
}

int cola_primero(Cola cola) {
    return cola->primero->dato;
}

void cola_encolar(Cola cola, int dato) {
    cola->ultimo = slist_agregar_final(cola->ultimo, dato);
    if (!cola->primero && cola->ultimo)
        cola->primero = cola->ultimo;
}

void cola_desencolar(Cola cola) {
    cola->primero = cola->primero ? cola->primero->sig : NULL;
}

void cola_imprimir(Cola cola) {
    for (SNodo *temp = cola->primero; temp != NULL; temp = temp->sig)
        printf("%d\t", temp->dato);
    printf("\n");
}

void cola_destruir(Cola cola) {
    slist_destruir(cola->primero);
    free(cola);
}