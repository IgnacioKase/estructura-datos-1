#include "matriz_triang_inf.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int main() {
  // Matriz triangular inferior.
  MatrizTriangularInf* mat = matriz_triangular_inf_crear(10);

  for (size_t i = 0; i < 10; ++i)
    for (size_t j = 0; j <= i; ++j)
      matriz_triangular_inf_escribir(mat, i, j, i);

  assert(matriz_triangular_inf_leer(mat, 3, 4) == 0);
  assert(matriz_triangular_inf_leer(mat, 3, 3) == 3);
  assert(matriz_triangular_inf_leer(mat, 3, 0) == 3);

  printf("Matriz triangular:\n");
  matriz_triangular_inf_imprimir(mat);
  printf("\n");

  matriz_triangular_inf_destruir(mat);

  return 0;
}
