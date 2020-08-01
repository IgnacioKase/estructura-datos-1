#include <stdio.h>
#include <stdlib.h>

#include "arboles/btree.h"



int main(int argc, char const *argv[]) {
    BTree ll = btree_unir(1, btree_crear(), btree_crear());
    BTree l = btree_unir(2, ll, btree_crear());
    BTree r = btree_unir(3, btree_crear(), btree_crear());
    BTree raiz = btree_unir(4, l, r);
    int suma = btree_suma(raiz);
    int nodos = btree_nodos(raiz);
    int altura = btree_altura(raiz);
    printf("Suma: %d\nNodos: %d\nAltura: %d\n", suma, nodos, altura);
    return 0;
}