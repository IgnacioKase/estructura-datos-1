/*
 TRABAJO PRÁCTICO 1
 METODOS DE ORDENAMIENTO EN LISTAS ENLAZADAS
 INTEGRANTES:
       - VALENTINA, PRATO
       - IGNACIO, KASEVICH
 GIT: https://github.com/IgnacioKase/tp1-estructuras1
 04/05/2020
*/

/*
 LEER Informe.pdf
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <wchar.h>
#include <locale.h>
#include "libs/list.h"
#include "libs/persona.h"
#include "sort_methods/insertion_sort.h"
#include "sort_methods/selection_sort.h"
#include "sort_methods/merge_sort.h"

#define MAX_STRING 45

/*
sort: List const char* -> List
recibe una lista List y el nombre de archivo de salida
(const char* para recibirlo desde los argumentos del programa),
pide al usuario el atributo a ordenar y metodo a usar
luego ordena la lista e imprime en el archivo cuanto tardo
(calculado segun la cantidad de tics del reloj del sistema)
y la lista, la cual luego retorna
*/
List sort(List lista, const char *salida, int parametro, int metodo) {
  double comienzo, final;
  Compara comp;

  assert(parametro > 0 && parametro < 4);
  assert(metodo > 0 && metodo < 4);

  switch (parametro) {
  case 1:
    comp = persona_comp_nombre;
    break;
  case 2:
    comp = persona_comp_edad;
    break;
  case 3:
    comp = persona_comp_pais;
    break;
  default:
    printf("\nERROR: numero invalido\n");
    break;
  }

  switch (metodo) {
  case 1:
    comienzo = clock();
    //la cantidad de tics hasta antes de ordenar
    lista = selection_sort(lista, comp);
    final = clock();
    //la cantidad de tics luego de ordenar
    break;
  case 2:
    comienzo = clock();
    lista = insertion_sort(lista, comp);
    final = clock();
    break;
  case 3:
    comienzo = clock();
    lista = merge_sort(lista, comp);
    final = clock();
    break;
  default:
    printf("\nERROR: numero invalido\n");
    break;
  }

  FILE *archivo = fopen(salida, "w, ccs=UTF-8");
  fwprintf(archivo, L"Tiempo: %f segundos\n\n",
           (final - comienzo) / CLOCKS_PER_SEC);
  //imprime en formato wchar_t
  list_recorrer_extra(lista, persona_archivo, archivo,
                      LIST_RECORRIDO_HACIA_ADELANTE);
  fclose(archivo);
  printf("\nArchivo %s editado exitosamente\n\n", salida);

  return lista;
}

/*
se recibe como argumento la cantidad de personas a crear,
el nombre del archivo de entrada y de salida
se crea una lista List con las personas
y se llama a sort para ordenarla como desee el usuario
e imprimirla en un archivo
*/
int main(int argc, char const *argv[]) {
  // para poder leer con wchar_t
  setlocale(LC_CTYPE, "");

  //Checkeamos recibir los parametros correctamente
  if (argc != 5) {
    printf("---------------------------------------\n\n");
    printf
        ("ERROR: ingrese el parámetro a ordenar, el método, y los archivos:\n\n");
    printf("1 - Paŕametro a ordenar\n");
    printf("\t 1 - Nombre\n");
    printf("\t 2 - Edad\n");
    printf("\t 3 - Pais\n");
    printf("2 - Método de ordenamiento\n");
    printf("\t 1 - Selection sort\n");
    printf("\t 2 - Insertion sort\n");
    printf("\t 3 - Merge sort\n");
    printf("3 - Archivo de entrada\n");
    printf("4 - Archivo de salida\n\n");
    printf("Ejemplo:\n\n");
    printf("$ sort 1 1 input/input.in output/output.out\n\n");
    printf("---------------------------------------\n");
    exit(-1);
  }

  List personas = personas_cargar_lista(argv[3]);

  personas = sort(personas, argv[4], atoi(argv[1]), atoi(argv[2]));

  list_destruir(personas, persona_destruir);
  return 0;
}
