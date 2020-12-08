#include <stdio.h>
#include <stdlib.h>
#include <matriz.h>

typedef struct { int* direccion; int capacidad; } ArregloEnteros;
ArregloEnteros* arreglo_enteros_crear(int capacidad);
void arreglo_enteros_destruir(ArregloEnteros* arreglo);
int arreglo_enteros_leer(ArregloEnteros* arreglo, int pos);
void arreglo_enteros_escribir(ArregloEnteros* arreglo, int pos, int dato);
int arreglo_enteros_capacidad(ArregloEnteros* arreglo);
void arreglo_enteros_imprimir(ArregloEnteros* arreglo);
void arreglo_enteros_ajustar(ArregloEnteros* arreglo, int capacidad);
void arreglo_enteros_insertar(ArregloEnteros* arreglo, int pos, int dato);
void arreglo_enteros_eliminar(ArregloEnteros* arreglo, int pos);

int main(){
  ArregloEnteros arreglo = *arreglo_enteros_crear(4);
  ArregloEnteros *list = &arreglo;
  arreglo_enteros_escribir(list, 0, 4);
  arreglo_enteros_escribir(list, 1, 3);
  arreglo_enteros_escribir(list, 2, 2);
  arreglo_enteros_escribir(list, 3, 1);
  printf("La capacidad del arreglo es: %d\n", arreglo_enteros_capacidad(list));
  arreglo_enteros_imprimir(list);
  arreglo_enteros_insertar(list, 2, 10);
  arreglo_enteros_imprimir(list);
  arreglo_enteros_insertar(list, 4, 5);
  arreglo_enteros_imprimir(list);
  arreglo_enteros_eliminar(list, 2);
  arreglo_enteros_imprimir(list);
  arreglo_enteros_ajustar(list, 2);
  arreglo_enteros_imprimir(list);
  arreglo_enteros_destruir(list);
  return 0;
}

//O(1)
ArregloEnteros* arreglo_enteros_crear(int capacidad){
  ArregloEnteros *list = (ArregloEnteros *) malloc(sizeof(ArregloEnteros));
  list->direccion = malloc(capacidad*sizeof(int));
  list->capacidad = capacidad;
  return list;
}

//O(1)
void arreglo_enteros_destruir(ArregloEnteros* arreglo){
  free(arreglo->direccion);
  free(arreglo);
  return;
}

//O(1)
int arreglo_enteros_leer(ArregloEnteros* arreglo, int pos){
  return *(arreglo->direccion + pos);
}

//O(1)
void arreglo_enteros_escribir(ArregloEnteros* arreglo, int pos, int dato){
  *(arreglo->direccion + pos) = dato;
  return;
}

//O(1)
int arreglo_enteros_capacidad(ArregloEnteros* arreglo){
  return arreglo->capacidad;
}

//O(n)
void arreglo_enteros_imprimir(ArregloEnteros* arreglo){
  int i;
  for(i = 0; i < arreglo_enteros_capacidad(arreglo); i++)
    printf("%d\t", arreglo_enteros_leer(arreglo, i));
  printf("\n");
  return;
}

void arreglo_enteros_ajustar(ArregloEnteros* arreglo, int capacidad){
  arreglo->direccion = realloc(arreglo->direccion, capacidad);
  arreglo->capacidad = capacidad;
  return;
}
void arreglo_enteros_insertar(ArregloEnteros* arreglo, int pos, int dato){
  int i;
  arreglo_enteros_ajustar(arreglo, arreglo->capacidad + 1);
  for(i = arreglo->capacidad - 1; i > pos; i--)
    (arreglo->direccion)[i] = (arreglo->direccion)[i-1];
  *(arreglo->direccion+pos) =  dato;
  return;
}

void arreglo_enteros_eliminar(ArregloEnteros* arreglo, int pos){
  int i;
  for(i = pos; i < arreglo->capacidad-1; i++)
    *(arreglo->direccion + i) = *(arreglo->direccion + i + 1);
  arreglo_enteros_ajustar(arreglo, arreglo->capacidad - 1);
  return;
}

