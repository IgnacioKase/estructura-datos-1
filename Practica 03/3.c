#include <stdio.h>

#include "pila_3.h"

int main() {
    Pila pila = pila_crear();
    if (pila_es_vacia(pila))
        printf("La pila es vacia\n");
    else
        printf("La pila no es vacia\n");
    pila_apilar(&pila, 20);
    if (pila_es_vacia(pila))
        printf("La pila es vacia\n");
    else
        printf("La pila no es vacia\n");
    pila_apilar(&pila, 4);
    printf("El ultimo elemento es: %d\n", pila_ultimo(pila));
    pila_desapilar(&pila);
    printf("Ahora el ultimo elemento es: %d\n", pila_ultimo(pila));
    pila_apilar(&pila, 5);
    pila_apilar(&pila, 12);
    pila_apilar(&pila, 4);
    pila_apilar(&pila, 2);
    pila_apilar(&pila, 3);
    pila_apilar(&pila, 1);
    pila_apilar(&pila, 1000);
    pila_imprimir(pila);
    pila_destruir(pila);
    printf("*** Fin ***\n");
    return 0;
}
