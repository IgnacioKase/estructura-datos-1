#include "matriz_triang_inf.h"
#include <assert.h>
#include <stdio.h>

struct MatrizTriangularInf_ {
  double* direccion;
  size_t tamanio;
};

MatrizTriangularInf* matriz_triangular_inf_crear(size_t tamanio) {
  MatrizTriangularInf* matriz = malloc(sizeof(MatrizTriangularInf));
  assert(matriz);
  matriz->direccion = malloc((tamanio * (tamanio + 1) / 2) * sizeof(double));
  assert(matriz->direccion);
  matriz->tamanio = tamanio;
  return matriz;
}

void matriz_triangular_inf_destruir(MatrizTriangularInf* matriz) {
  assert(matriz);
  free(matriz->direccion);
  free(matriz);
}

double matriz_triangular_inf_leer(MatrizTriangularInf* matriz, size_t fil,
                                  size_t col) {
  assert(matriz);
  assert(fil < matriz->tamanio);
  assert(col < matriz->tamanio);
  if (fil < col)
    return 0;
  return matriz->direccion[fil * (fil + 1) / 2 + col];
}

void matriz_triangular_inf_escribir(MatrizTriangularInf* matriz, size_t fil,
                                    size_t col, double val) {
  assert(matriz);
  assert(fil < matriz->tamanio);
  assert(col < matriz->tamanio);
  assert(fil >= col);
  matriz->direccion[fil * (fil + 1) / 2 + col] = val;
}

size_t matriz_triangular_inf_num_filas(MatrizTriangularInf* matriz) {
  return matriz->tamanio;
}

size_t matriz_triangular_inf_num_columnas(MatrizTriangularInf* matriz) {
  return matriz->tamanio;
}

void matriz_triangular_inf_imprimir(MatrizTriangularInf* matriz) {
  size_t numColumnas = matriz_triangular_inf_num_columnas(matriz);
  size_t numFilas = matriz_triangular_inf_num_filas(matriz);

  for (size_t i = 0; i < numFilas; ++i) {
    if (i)
      printf("\n");
    for (size_t j = 0; j < numColumnas; ++j)
      printf("%lf ", matriz_triangular_inf_leer(matriz, i, j));
  }
  printf("\n");
}

