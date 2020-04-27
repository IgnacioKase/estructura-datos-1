#include "matriz_extra.h"
#include <assert.h>

Matriz* matriz_sumar(Matriz* matrizA, Matriz* matrizB) {
  assert(matrizA && matrizB);
  assert(matriz_num_filas(matrizB) == matriz_num_filas(matrizA));
  assert(matriz_num_columnas(matrizB) == matriz_num_columnas(matrizA));

  size_t numFil = matriz_num_filas(matrizA);
  size_t numCol = matriz_num_columnas(matrizA);

  Matriz* matrizRes = matriz_crear(numFil, numCol);

  for (size_t i = 0; i < numFil; ++i)
    for (size_t j = 0; j < numCol; ++j)
      matriz_escribir(matrizRes, i, j, matriz_leer(matrizA, i, j) +
                                       matriz_leer(matrizB, i, j));

  return matrizRes;
}

Matriz* matriz_multiplicar(Matriz* matrizA, Matriz* matrizB) {
  assert(matrizA && matrizB);
  assert(matriz_num_columnas(matrizA) == matriz_num_filas(matrizB));

  size_t numFil = matriz_num_filas(matrizA);
  size_t numCol = matriz_num_columnas(matrizB);
  size_t dim = matriz_num_columnas(matrizA);

  Matriz* matrizRes = matriz_crear(numFil, numCol);

  for (size_t i = 0; i < numFil; ++i)
    for (size_t j = 0; j < numCol; ++j) {
      double sum = 0;
      for (size_t k = 0; k < dim; ++k)
        sum += matriz_leer(matrizA, i, k) * matriz_leer(matrizB, k, j);
      matriz_escribir(matrizRes, i, j, sum);
    }

  return matrizRes;
}
