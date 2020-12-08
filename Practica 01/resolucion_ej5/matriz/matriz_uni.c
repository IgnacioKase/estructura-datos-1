#include "matriz.h"
#include <assert.h>
#include <stdio.h>

/*
** Implementacion utilizando un unico arreglo unidimensional.
*/

struct Matriz_ {
  double* direccion;
  size_t numFilas;
  size_t numColumnas;
};


Matriz* matriz_crear(size_t numFilas, size_t numColumnas){
  Matriz* matriz = malloc(sizeof(Matriz));
  assert(matriz);

  matriz->direccion = malloc(numFilas * numColumnas * sizeof(double));
  assert(matriz->direccion);

  matriz->numFilas = numFilas;
  matriz->numColumnas = numColumnas;

  return matriz;
}

void matriz_destruir(Matriz* matriz){
  free(matriz->direccion);
  free(matriz);
}

double matriz_leer(Matriz* matriz, size_t fil, size_t col){
  assert(matriz);
  assert(fil < matriz->numFilas);
  assert(col < matriz->numColumnas);
  return matriz->direccion[fil * matriz->numColumnas + col];
}

void matriz_escribir(Matriz* matriz, size_t fil, size_t col, double val){
  assert(matriz);
  assert(fil < matriz->numFilas);
  assert(col < matriz->numColumnas);
  matriz->direccion[fil * matriz->numColumnas + col] = val;
}

size_t matriz_num_filas(Matriz* matriz){
  assert(matriz);
  return matriz->numFilas;
}

size_t matriz_num_columnas(Matriz* matriz){
  assert(matriz);
  return matriz->numColumnas;
}

void matriz_intercambiar_filas(Matriz *matriz, size_t i, size_t j) {
  assert(matriz);
  assert(i < matriz->numFilas);
  assert(j < matriz->numFilas);

  for (size_t k = 0; k < matriz->numColumnas; ++k) {
    double tmp = matriz_leer(matriz, i, k);
    matriz_escribir(matriz, i, k, matriz_leer(matriz, j, k));
    matriz_escribir(matriz, j, k, tmp);
  }
}

void matriz_imprimir(Matriz* matriz) {
  assert(matriz);

  size_t numColumnas = matriz_num_columnas(matriz);
  size_t numFilas = matriz_num_filas(matriz);

  for (size_t i = 0; i < numFilas; ++i) {
    for (size_t j = 0; j < numColumnas; ++j)
      printf("%lf ", matriz_leer(matriz, i, j));
    printf("\n");
  }
}
