#include <stdio.h>

#include "../Practica 02/slist/slist.h"
#include "pila_3.h"

SList slist_reverso(SList list) {
    Pila pila = pila_crear();
    SList temp;
    for (temp = list; temp != NULL; temp = temp->sig)
        pila_apilar(&pila, temp->dato);
    for (temp = list; temp != NULL; temp = temp->sig) {
        temp->dato = pila_ultimo(pila);
        pila_desapilar(&pila);
    }
    return list;
}

void slist_imprimir(int dato) {
    printf("%d\t", dato);
}

int main() {
    SList lista = slist_crear();
    lista = slist_agregar_final(lista, 1);
    lista = slist_agregar_final(lista, 2);
    lista = slist_agregar_final(lista, 3);
    lista = slist_agregar_final(lista, 4);
    lista = slist_agregar_final(lista, 5);
    slist_recorrer(lista, slist_imprimir);
    printf("\n");
    lista = slist_reverso(lista);
    slist_recorrer(lista, slist_imprimir);
    printf("\n");
    printf("*** Fin ***\n");
    return 0;
}
