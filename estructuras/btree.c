#include "btree.h"

BTree btree_crear() {
    return NULL;
}

void btree_destruir(BTree nodo) {
    if (nodo != NULL) {
        btree_destruir(nodo->left);
        btree_destruir(nodo->right);
        free(nodo);
    }
}

int btree_empty(BTree nodo) {
    return nodo == NULL;
}

BTree btree_unir(int dato, BTree left, BTree right) {
    BTree nuevoNodo = malloc(sizeof(BTNodo));
    nuevoNodo->dato = dato;
    nuevoNodo->left = left;
    nuevoNodo->right = right;
    return nuevoNodo;
}

void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden,
                    FuncionVisitante visit) {
    if (arbol == NULL)
        return;
    if (orden == BTREE_RECORRIDO_IN) {
        btree_recorrer(arbol->left, orden, visit);
        visit(arbol->dato);
        btree_recorrer(arbol->right, orden, visit);
    }
    if (orden == BTREE_RECORRIDO_PRE) {
        visit(arbol->dato);
        btree_recorrer(arbol->left, orden, visit);
        btree_recorrer(arbol->right, orden, visit);
    }
    if (orden == BTREE_RECORRIDO_POST) {
        btree_recorrer(arbol->left, orden, visit);
        btree_recorrer(arbol->right, orden, visit);
        visit(arbol->dato);
    }
}

void btree_recorrer_iterativo(BTree arbol, BTreeOrdenDeRecorrido orden,
                              FuncionVisitante visit) {
    Pila pila = pila_crear();
    BTree nodo;
    pila_apilar(&pila, (void*)arbol);
    while (!pila_es_vacia(pila)) {
        nodo = (BTree)pila_ultimo(pila);
        pila_desapilar(&pila);
        if (orden == BTREE_RECORRIDO_IN) {
            pila_apilar(&pila, (void*)nodo->left);
            visit(nodo->dato);
            pila_apilar(&pila, (void*)nodo->right);
        }
        if (orden == BTREE_RECORRIDO_PRE) {
            visit(nodo->dato);
            pila_apilar(&pila, (void*)nodo->left);
            pila_apilar(&pila, (void*)nodo->right);
        }
        if (orden == BTREE_RECORRIDO_POST) {
            pila_apilar(&pila, (void*)nodo->left);
            pila_apilar(&pila, (void*)nodo->right);
            visit(nodo->dato);
        }
    }
    free(nodo);
    pila_destruir(pila);
}

int max(int a, int b) {
    return a > b ? a : b;
}

int btree_suma(BTree arbol) {
    if (btree_empty(arbol))
        return 0;
    if (btree_empty(arbol->left) && btree_empty(arbol->right))
        return arbol->dato;
    return arbol->dato + btree_suma(arbol->left) + btree_suma(arbol->right);
}

int btree_nodos(BTree arbol) {
    if (btree_empty(arbol))
        return 0;
    if (btree_empty(arbol->left) && btree_empty(arbol->right))
        return 1;
    return 1 + btree_nodos(arbol->left) + btree_nodos(arbol->right);
}

int btree_altura(BTree arbol) {
    if (btree_empty(arbol))
        return -1;
    if (btree_empty(arbol->left) && btree_empty(arbol->right))
        return 0;
    return 1 + max(btree_altura(arbol->left), btree_altura(arbol->right));
}
