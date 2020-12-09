#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// #include <unistd.h>

/*
    - Devuelve una lista vacia
*/
List list_crear() {
  return NULL;
}

/*
    - Toma una Lista (@list) Y una función del tipo Destruir
    y destruye la lista.
*/
void list_destruir(List lista, Destruir destruir) {
  assert(lista != NULL);
  Nodo *nodoAEliminar;
  while (lista->sig != lista) {
    nodoAEliminar = lista->sig;
    lista->sig = lista->sig->sig;
    destruir(nodoAEliminar->dato);
    free(nodoAEliminar);
  }
  destruir(lista->dato);
  free(lista);
}

/*
    - Toma una Lista (@lista)
    - Determina si la lista es vacía.
    Devuelve 1 si es vacia, caso contrario 0.
*/
int list_vacia(List lista) {
  return lista == NULL;
}

/*
    Agrega un elemento al final de la lista.
*/
List list_agregar_final(List lista, void *dato) {
  Nodo *nuevoNodo = malloc(sizeof(Nodo));
  nuevoNodo->dato = dato;

  if (lista == NULL) {
    nuevoNodo->sig = nuevoNodo;
    nuevoNodo->ant = nuevoNodo;
    return nuevoNodo;
  }

  nuevoNodo->sig = lista;
  nuevoNodo->ant = lista->ant;
  lista->ant->sig = nuevoNodo;
  lista->ant = nuevoNodo;
  return lista;
}

/*
    Agrega un elemento al final de la lista.
*/
List list_agregar_ordenado(List lista, void *dato, FuncionMenor menor) {
  Nodo *nuevoNodo = malloc(sizeof(Nodo));
  nuevoNodo->dato = dato;

  if (lista == NULL) {
    nuevoNodo->sig = nuevoNodo;
    nuevoNodo->ant = nuevoNodo;
    return nuevoNodo;
  }

  Nodo *nodo;

  for (nodo = lista; nodo->sig != lista; nodo = nodo->sig){
    if(menor(nuevoNodo->dato, nodo->dato)) {
      nuevoNodo->sig = nodo;
      nuevoNodo->ant = nodo->ant;
      nodo->ant->sig = nuevoNodo;
      nodo->ant = nuevoNodo;
      return lista;
    }
  }

 if(menor(nuevoNodo->dato, nodo->dato)) {
    nuevoNodo->sig = nodo;
    nuevoNodo->ant = nodo->ant;
    nodo->ant->sig = nuevoNodo;
    nodo->ant = nuevoNodo;
  } else {
    list_agregar_final(lista, dato);
  }

  return lista;
}

List list_buscar(List lista, void *clave, FuncionIgual igual) {
  if (list_vacia(lista) && clave != NULL)
    return NULL;

  List nodo;
  int encontrado = 0;

  printf("nani de fuck x1\n");

  for (nodo = lista; nodo->sig != lista && !encontrado; nodo = nodo->sig) {
      if(nodo->dato != NULL)
        if(igual(clave, nodo->dato))
          return nodo;
  }

  printf("nani de fuck\n");
  
  if(nodo->dato != NULL)
    if(igual(clave, nodo->dato))
      return nodo;

  return NULL;
}

/*
    Agrega un elemento al inicio de la lista.
*/
List list_agregar_inicio(List lista, void *dato) {
  Nodo *nuevoNodo = malloc(sizeof(Nodo));
  nuevoNodo->dato = dato;

  if (lista == NULL) {
    nuevoNodo->sig = nuevoNodo;
    nuevoNodo->ant = nuevoNodo;
    return nuevoNodo;
  }

  nuevoNodo->sig = lista;
  nuevoNodo->ant = lista->ant;
  lista->ant->sig = nuevoNodo;
  lista->ant = nuevoNodo;
  return nuevoNodo;
}

/*
    Recorrido de la lista, utilizando la funcion pasada.
*/
void list_recorrer(List lista, FuncionVisitante visit,
                   ListOrdenDeRecorrido sentido) {
  if (lista == NULL)
    return;
  Nodo *nodo;
  if (sentido == LIST_RECORRIDO_HACIA_ADELANTE) {
    for (nodo = lista; nodo->sig != lista; nodo = nodo->sig){
      visit(nodo->dato);
      // sleep(1);
    }
    visit(nodo->dato);
  } else if (sentido == LIST_RECORRIDO_HACIA_ATRAS) {
    for (nodo = lista->ant; nodo->ant != lista->ant; nodo = nodo->ant)
      visit(nodo->dato);
    visit(nodo->dato);
  }
}

/*
    Recorrido de la lista, utilizando la funcion pasada con un parámetro adicional.
*/
void list_recorrer_extra(List lista, VisitanteExtra visit, void *extra,
                         ListOrdenDeRecorrido sentido) {
  if (lista == NULL)
    return;
  Nodo *nodo;
  if (sentido == LIST_RECORRIDO_HACIA_ADELANTE) {
    for (nodo = lista; nodo->sig != lista; nodo = nodo->sig)
      visit(nodo->dato, extra);
    visit(nodo->dato, extra);
  } else if (sentido == LIST_RECORRIDO_HACIA_ATRAS) {
    for (nodo = lista->ant; nodo->ant != lista->ant; nodo = nodo->ant)
      visit(nodo->dato, extra);
    visit(nodo->dato, extra);
  }
}

/*
    - Toma una lista (@list) y la divide a la mitad.
    - Devuelve el inicio de la nueva lista (la segunda mitad).
    Y en @list queda la primer mitad de la lista.
*/
List list_dividir(List list) {
  List fast = list, slow = list;
  while (fast->sig && fast->sig->sig) {
    fast = fast->sig->sig;
    slow = slow->sig;
  }
  List temp = slow->sig;
  slow->sig = NULL;
  return temp;
}

/*
    - Toma dos nodos (@a y @b) e intercambia sus datos.
*/
void list_swap(Nodo * a, Nodo * b) {
  void *p;
  p = a->dato;
  a->dato = b->dato;
  b->dato = p;
}
