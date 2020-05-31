#ifndef __PILA_H__
#define __PILA_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct _Pila *Pila;
typedef struct _Pila SPila;

/*
     Crea e inicializa una nueva pila vacía
*/
Pila pila_crear();

/*
    Determina si la pila está vacía
*/
int pila_es_vacia(Pila pila);

/*
    Toma una pila y devuelve el elemento en la cima.
*/
void *pila_ultimo(Pila pila);

/*
    toma una pila y un elemento y agrega el elemento a la pila
*/
void pila_apilar(Pila *pila, void *dato);

/*
    Toma una pila y elimina el elemento de la cima
*/
void pila_desapilar(Pila *pila);

/*
    Libera la memoria requerida para la pila
*/
void pila_destruir(Pila pila);

#endif