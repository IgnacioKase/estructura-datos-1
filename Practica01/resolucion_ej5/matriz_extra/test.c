#include "matriz_extra.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static Matriz* identidad(size_t n) {
  assert(n > 0);

  Matriz* id = matriz_crear(n, n);

  for (size_t i = 0; i < 10; ++i)
    for (size_t j = 0; j < 10; ++j)
      if (i == j)
        matriz_escribir(id, i, j, 1);
      else
        matriz_escribir(id, i, j, 0);

  return id;
}

int main() {
  // Definiciones de Matrices.
  Matriz* matA = matriz_crear(5, 10);
  for (size_t i = 0; i < 5; ++i)
    for (size_t j = 0; j < 10; ++j)
      matriz_escribir(matA, i, j, i);

  Matriz* matB = matriz_crear(5, 10);
  for (size_t i = 0; i < 5; ++i)
    for (size_t j = 0; j < 10; ++j)
      matriz_escribir(matB, i, j, j);

  Matriz* matId = identidad(10);

  // Mostramos las Matrices.
  printf("Matriz A:\n");
  matriz_imprimir(matA);
  printf("\n");

  printf("Matriz B:\n");
  matriz_imprimir(matB);
  printf("\n");

  printf("Matriz I:\n");
  matriz_imprimir(matId);
  printf("\n");

  // Matriz suma.
  Matriz* matSuma = matriz_sumar(matA, matB);
  printf("A + B:\n");
  matriz_imprimir(matSuma);
  printf("\n");
  matriz_destruir(matSuma);

  // Matriz multiplicacion.
  Matriz* matMult = matriz_multiplicar(matA, matId);
  printf("A * I:\n");
  matriz_imprimir(matMult);
  printf("\n");
  matriz_destruir(matMult);

  // Destruimos las Matrices.
  matriz_destruir(matA);
  matriz_destruir(matB);
  matriz_destruir(matId);

  return 0;
}
