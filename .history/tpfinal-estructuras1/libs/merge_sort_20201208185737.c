#include "merge_sort.h"

/*
    Se encarga de unir las listas de forma correcta
    a partir de la función @comp.
*/
List merge(List primero, List segundo, Compara comp) {
  if (!primero)
    return segundo;

  if (!segundo)
    return primero;

  if (comp(primero->dato, segundo->dato)) {
    primero->sig = merge(primero->sig, segundo, comp);
    primero->sig->ant = primero;
    primero->ant = NULL;
    return primero;
  } else {
    segundo->sig = merge(primero, segundo->sig, comp);
    segundo->sig->ant = segundo;
    segundo->ant = NULL;
    return segundo;
  }
}

/*
    Aplicamos la estrategia de "divide y venceras".
    Dividimos la lista en mitades y volvemos a llamar
    esta función hasta que quede 1 o ningun elemento.
    
    Luego las unimos con la función merge.
*/
List merge_sort_inner(List lista, Compara comp) {
  if (!lista || !lista->sig)
    return lista;
  List mitad = list_dividir(lista);

  lista = merge_sort_inner(lista, comp);
  mitad = merge_sort_inner(mitad, comp);

  return merge(lista, mitad, comp);
}

/*
    - Toma una Lista (@lista) y una función de comparación
    (@comp) y ordena la lista a partir del método merge sort
    comparando con @comp.
    - Devuelve la lista ordenada.
*/
void merge_sort(List *lista, Compara comp) {
  if ((*lista) == NULL)
    return lista;

  // Hago que la lista ya no sea circular para facilitar el merge
  if ((*lista)->ant != NULL) {
    (*lista)->ant->sig = NULL;
    (*lista)->ant = NULL;
  }

  
 = merge_sort_inner(lista, comp);

  // Vuelvo a hacerla circular
  List temp = lista;
  while (temp->sig != NULL)
    temp = temp->sig;
  (*lista)->ant = temp;
  temp->sig = lista;
};
