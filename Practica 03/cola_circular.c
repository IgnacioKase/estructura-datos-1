#include "cola.h"

struct _Cola {
    int datos[MAX_COLA];
    int primero, ultimo;
};

Cola cola_crear() {
    Cola cola = malloc(sizeof(SCola));
    cola->primero = 0;
    cola->ultimo = -1;
    return cola;
}

int cola_es_vacia(Cola cola) {
    return cola->ultimo == -1;
}

int cola_primero(Cola cola) {
    return cola->datos[cola->primero];
}

void cola_encolar(Cola cola, int dato) {
    cola->ultimo = (cola->ultimo + 1) % MAX_COLA;
    cola->datos[cola->ultimo] = dato;
}

void cola_desencolar(Cola cola) {
    cola->primero = (cola->primero + 1) % MAX_COLA;
}

int cola_cantidad_en_cola(Cola cola) {
    int dif = cola->ultimo - cola->primero;
    return dif < 0 ? dif + MAX_COLA + 1 : dif + 1;
}

void cola_imprimir(Cola cola) {
    int dif = cola_cantidad_en_cola(cola);
    for (int i = cola->primero; i < dif + cola->primero; i++)
        printf("%d\t", cola->datos[i % MAX_COLA]);
    printf("\n");
}

void cola_destruir(Cola cola) {
    free(cola);
}