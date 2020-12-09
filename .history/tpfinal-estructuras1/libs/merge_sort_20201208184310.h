#ifndef __MERGE_SORT_H__
#define __MERGE_SORT_H__

/*
    Comentarios de las funciones en el archivo .c
*/

#include "list.h"

typedef int (*Compara)(void *dato1, void *dato2);

List merge(List primero, List segundo, Compara comp);

List merge_sort_inner(List lista, Compara comp);

List merge_sort(List lista, Compara comp);

#endif