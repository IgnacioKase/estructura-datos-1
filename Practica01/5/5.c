#include <matriz.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
  Matriz matriz* = matriz_crear(5,5);
  
  size_t cols = matriz_num_columnas(matriz);
  size_t fils = matriz_num_filas(matriz);
  printf("%d", cols);
  printf("%d", fils);
  matriz_escribir(matriz, 2, 2, 6.0);
  double resp = matriz_leer(matriz, 2, 2);
  printf("%.2f", resp);
  return 0;
}


/*
 * b) La implementación con un unico array y trabajar con los indices
 * parece mas intuitiva y ademas podemos utilizar los operadores [][].
 * es facil leer una posición o escribir en ella.
 * Pero creo que la implementación con un array bidimensional, 
 * 
 * 
 * 
 * 
 * 
 * /
