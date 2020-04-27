#ifndef __MATRIZ_TRIANG_INF_H__
#define __MATRIZ_TRIANG_INF_H__

#include <stdlib.h>

// Matrices triangular inferior.
typedef struct MatrizTriangularInf_ MatrizTriangularInf;

/**
 * Crea una nueva matriz.
 */
MatrizTriangularInf* matriz_triangular_inf_crear(size_t tamanio);

/**
 * Destruye una matriz.
 */
void matriz_triangular_inf_destruir(MatrizTriangularInf* matriz);

/**
 * Obtiene el dato guardado en la posición dada de la matriz.
 */
double matriz_triangular_inf_leer(MatrizTriangularInf* matriz, size_t fil,
        size_t col);

/**
 * Modifica el dato guardado en la posición dada de la matriz.
 */
void matriz_triangular_inf_escribir(MatrizTriangularInf* matriz, size_t fil,
                                    size_t col, double val);

/**
 * Obtiene número de filas de la matriz.
 */
size_t matriz_triangular_inf_num_filas(MatrizTriangularInf* matriz);

/**
 * Obtiene número de columnas de la matriz.
 */
size_t matriz_triangular_inf_num_columnas(MatrizTriangularInf* matriz);

/**
 * Imprime la matriz en pantalla.
 */
void matriz_triangular_inf_imprimir(MatrizTriangularInf* matriz);

#endif /* __MATRIZ_TRIANG_INF_H__ */
