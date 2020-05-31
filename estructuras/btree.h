#ifndef __BTREE_H__
#define __BTREE_H__

#include <stdlib.h>

#include "gpila.h"

typedef void (*FuncionVisitante)(int dato);

typedef enum {
    BTREE_RECORRIDO_IN,
    BTREE_RECORRIDO_PRE,
    BTREE_RECORRIDO_POST
} BTreeOrdenDeRecorrido;

typedef struct _BTNodo {
    int dato;
    struct _BTNodo *left;
    struct _BTNodo *right;
} BTNodo;

typedef BTNodo *BTree;

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear();

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo);

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo);

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(int dato, BTree left, BTree right);

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden,
                    FuncionVisitante visit);

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer_iterativo(BTree arbol, BTreeOrdenDeRecorrido orden,
                              FuncionVisitante visit);
/**
 * Devuelve el maximo entre a y b
 */
int max(int a, int b);

/**
 * Devuelve la suma de los nodos del arbol
 */
int btree_suma(BTree arbol);

/**
 * Devuelve la cantidad de nodos del arbol
 */
int btree_nodos(BTree arbol);

/**
 * Devuelve la altura del arbol
 */
int btree_altura(BTree arbol);

#endif /* __BTREE_H__ */
