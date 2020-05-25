#include <stdio.h>

#include "cola.h"

int main() {
    Cola cola = cola_crear();
    if (cola_es_vacia(cola))
        printf("La pila es vacia\n");
    else
        printf("La pila no es vacia\n");
    cola_encolar(cola, 20);
    if (cola_es_vacia(cola))
        printf("La pila es vacia\n");
    else
        printf("La pila no es vacia\n");
    cola_encolar(cola, 4);
    printf("El primer elemento es: %d\n", cola_primero(cola));
    cola_desencolar(cola);
    printf("Ahora el primer elemento es: %d\n", cola_primero(cola));
    cola_encolar(cola, 5);
    cola_encolar(cola, 12);
    cola_encolar(cola, 4);
    cola_encolar(cola, 2);
    cola_encolar(cola, 3);
    cola_encolar(cola, 1);
    cola_encolar(cola, 1000);
    cola_imprimir(cola);
    cola_destruir(cola);
    printf("*** Fin ***\n");
    return 0;
}
