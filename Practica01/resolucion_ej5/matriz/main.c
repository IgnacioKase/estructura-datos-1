#include "matriz.h"
#include <assert.h>
#include <stdio.h>

int main() {
  // Matriz.
  Matriz* mat1 = matriz_crear(5, 10);

  for (size_t i = 0; i < 5; ++i)
    for (size_t j = 0; j < 10; ++j)
      matriz_escribir(mat1, i, j, i);

  printf("Matriz:\n");
  matriz_imprimir(mat1);

  matriz_intercambiar_filas(mat1, 1, 2);
  printf("Despues de intercambiar filas 1 y 2:\n");
  matriz_imprimir(mat1);

  matriz_destruir(mat1);

  return 0;
}
