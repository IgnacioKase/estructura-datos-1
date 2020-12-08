#include "matriz.h"

/*
** Implmentacion utilizando un unico arreglo unidimensional
*/

struct Matriz_ {
  double *direccion;
  size_t columnas;
  size_t filas;
};


Matriz* matriz_crear(size_t numFilas, size_t numColumnas) {
  Matriz *matriz = malloc(sizeof(Matriz));
  matriz->direccion = malloc(sizeof(double)*numFilas*numColumnas);
  matriz->columnas = numColumnas;
  matriz->filas = numFilas;
  return matriz;
}

void matriz_destruir(Matriz* matriz) {
  free(matriz->direccion);
  free(matriz);
}

double matriz_leer(Matriz* matriz, size_t fil, size_t col) {
  return *(matriz->direccion+fil*col+col);
}

void matriz_escribir(Matriz* matriz, size_t fil, size_t col, double val) {
  *(matriz->direccion+fil*col+col) = val;
}

size_t matriz_num_filas(Matriz* matriz) {
  return matriz->filas;
}

size_t matriz_num_columnas(Matriz* matriz) {
  return matriz->columnas;
}
