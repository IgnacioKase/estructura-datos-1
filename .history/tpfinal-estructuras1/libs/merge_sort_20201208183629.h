#ifndef __MERGE_SORT_H__
#define __MERGE_SORT_H__

#include "../libs/list.h"
#include "../libs/persona.h"

/*
    Comentarios de las funciones en el archivo .c
*/

List merge(List primero, List segundo, Compara comp);

List merge_sort_inner(List lista, Compara comp);

List merge_sort(List lista, Compara comp);

#endif