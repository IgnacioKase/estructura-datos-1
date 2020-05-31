#ifndef __COLA_H__
#define __COLA_H__

#include <stdio.h>
#include <stdlib.h>

#include "slist.h"

typedef struct _Cola *Cola;
typedef struct _Cola SCola;

struct _Cola {
    SNodo *primero, *ultimo;
};

/*
     Crea e inicializa una nueva Cola vacía
*/
Cola cola_crear();

/*
    Determina si la Cola está vacía
*/
int cola_es_vacia(Cola Cola);

/*
    Toma una Cola y devuelve el elemento en la primera posición.
*/
int cola_primero(Cola Cola);

/*
    toma una Cola y un elemento y agrega el elemento al fin de la Cola
*/
void cola_encolar(Cola Cola, int dato);

/*
    Toma una Cola y elimina su primer elemento
*/
void cola_desencolar(Cola Cola);

/*
    Toma una Cola y la imprime en orden
*/
void cola_imprimir(Cola Cola);

/*
    Libera la memoria requerida para la Cola
*/
void cola_destruir(Cola Cola);

#endif