#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Matriz_ Matriz;

Matriz* matriz_crear(size_t numFilas, size_t numColumnas);
void matriz_destruir(Matriz* matriz);
double matriz_leer(Matriz* matriz, size_t fil, size_t col);
void matriz_escribir(Matriz* matriz, size_t fil, size_t col, double val);
size_t matriz_num_filas(Matriz* matriz);
size_t matriz_num_columnas(Matriz* matriz);
void matriz_cero(Matriz* matriz);
void matriz_imprimir(Matriz* matriz);
void matriz_intercambiar_filas(Matriz* matriz, size_t fil, size_t nfil);

int main(){
  Matriz *matriz = matriz_crear(5,5);
  matriz_cero(matriz);
  
  size_t cols = matriz_num_columnas(matriz);
  size_t fils = matriz_num_filas(matriz);
  printf("%d\n", cols);
  printf("%d\n", fils);
  matriz_escribir(matriz, 2, 2, 6.0);
  double resp = matriz_leer(matriz, 2, 2);
  printf("%.2f\n", resp);
  matriz_imprimir(matriz);
  matriz_intercambiar_filas(matriz, 2, 4);
  matriz_imprimir(matriz);
  matriz_destruir(matriz);
  return 0;
}

struct Matriz_ {
  double **direccion;
  size_t columnas;
  size_t filas;
};

Matriz* matriz_crear(size_t numFilas, size_t numColumnas) {
  Matriz *matriz = malloc(sizeof(Matriz));
  matriz->direccion = malloc(sizeof(double)*numFilas);
  int i;
  for(i = 0; i < numFilas; i++)
    *(matriz->direccion+i) = malloc(sizeof(double)*numColumnas);
  matriz->columnas = numColumnas;
  matriz->filas = numFilas;
  return matriz;
}

void matriz_destruir(Matriz* matriz) {
  int i;
  for(i = 0; i < matriz_num_filas(matriz); i++)
    free(*(matriz->direccion+i));
  free(matriz->direccion);
  free(matriz);
}

double matriz_leer(Matriz* matriz, size_t fil, size_t col) {
  return *(*(matriz->direccion+fil)+col);
}

void matriz_escribir(Matriz* matriz, size_t fil, size_t col, double val) {
  *(*(matriz->direccion+fil)+col) = val;
}

size_t matriz_num_filas(Matriz* matriz) {
  return matriz->filas;
}

size_t matriz_num_columnas(Matriz* matriz) {
  return matriz->columnas;
}

void matriz_cero(Matriz* matriz){
  int i,j;
  for(i = 0; i < matriz->filas; i++)
    for(j = 0; j < matriz->columnas; j++)
      matriz->direccion[i][j] = 0;
}

void matriz_imprimir(Matriz* matriz){
  int i,j;
  printf("\n");
  for(i = 0; i < matriz->filas; i++){
    for(j = 0; j < matriz->columnas; j++)
      printf("%.2f ", matriz->direccion[i][j]);
    printf("\n");
  }
  printf("\n");
}

void matriz_intercambiar_filas(Matriz* matriz, size_t fil, size_t nfil){
  double *temp = matriz->direccion[fil];
  matriz->direccion[fil] = matriz->direccion[nfil];
  matriz->direccion[nfil] = temp;
}
