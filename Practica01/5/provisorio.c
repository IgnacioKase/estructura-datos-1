#include <stdio.h>
#include <stdlib.h>

typedef struct Matriz_ Matriz;

/*
** Crea una nueva matriz
*/
Matriz* matriz_crear(size_t numFilas, size_t numColumnas);

/*
** Destruye una matriz
*/
void matriz_destruir(Matriz* matriz);

/*
** Obtiene el dato guardado en la posición dada de la matriz
*/
double matriz_leer(Matriz* matriz, size_t fil, size_t col);

/*
** Modifica el dato guardado en la posición dada de la matriz
*/
void matriz_escribir(Matriz* matriz, size_t fil, size_t col, double val);

/*
** Obtiene número de filas de la matriz
*/
size_t matriz_num_filas(Matriz* matriz);

/*
** Obtiene número de columnas de la matriz
*/
size_t matriz_num_columnas(Matriz* matriz);

int main(){
  Matriz *matriz = matriz_crear(5,5);
  
  size_t cols = matriz_num_columnas(matriz);
  size_t fils = matriz_num_filas(matriz);
  printf("%d\n", cols);
  printf("%d\n", fils);
  matriz_escribir(matriz, 2, 2, 6.0);
  double resp = matriz_leer(matriz, 2, 2);
  printf("%.2f\n", resp);
  return 0;
}

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
