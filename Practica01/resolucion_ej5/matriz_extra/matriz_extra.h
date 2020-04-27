#ifndef __MATRIZ_EXTRA_H__
#define __MATRIZ_EXTRA_H__

#include "../matriz/matriz.h"
#include <stdlib.h>

/**
 * Función para sumar dos matrices (deben tener el mismo número de columnas
 * y filas).
 */
Matriz* matriz_sumar(Matriz* matrizA, Matriz* matrizB);

/**
 * Función para multiplicar dos matrices (el número de columnas de la primera
 * matriz debe coincidir con el número de filas de la segunda).
 */
Matriz* matriz_multiplicar(Matriz* matrizA, Matriz* matrizB);

#endif /* __MATRIZ_EXTRA_H__ */
