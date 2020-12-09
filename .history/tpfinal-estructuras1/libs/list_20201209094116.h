#ifndef __LIST_H__
#define __LIST_H__

#include <stddef.h>

/*
    Comentarios de las funciones en el archivo .c
*/

typedef void (*Destruir)(void *dato);

typedef void (*FuncionVisitante)(void *dato);

typedef void (*VisitanteExtra)(void *dato, void *extra);

typedef int (*FuncionMenor)(void *a, void *b);

typedef int (*FuncionIgual)(void *a, void *b);

typedef struct _Nodo {
    void *dato;
    struct _Nodo *sig, *ant;
} Nodo;

typedef Nodo *List;

typedef enum {
    LIST_RECORRIDO_HACIA_ADELANTE,
    LIST_RECORRIDO_HACIA_ATRAS
} ListOrdenDeRecorrido;

List list_crear();

void list_destruir(List lista, Destruir destruir);

int list_vacia(List lista);

List list_agregar_final(List lista, void *dato);

List list_agregar_inicio(List lista, void *dato);

List list_agregar_ordenado(List lista, void *dato, FuncionMenor menor);

List list_buscar(List lista, void *clave, FuncionIgual);

void list_recorrer(List lista, FuncionVisitante visit, ListOrdenDeRecorrido sentido);

void list_recorrer_extra(List lista, VisitanteExtra visit, void *extra, ListOrdenDeRecorrido sentido);

void list_swap(Nodo *a, Nodo *b);

List list_dividir(List list);

#endif
