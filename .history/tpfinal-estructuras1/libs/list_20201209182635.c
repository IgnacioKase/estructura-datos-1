#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "registro.h"

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
  if(list_vacia(lista))
    return;
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
void list_agregar_final(List *lista, void *dato) {
  Nodo *nuevoNodo = malloc(sizeof(Nodo));
  nuevoNodo->dato = dato;

  if (*lista == NULL) {
    nuevoNodo->sig = nuevoNodo;
    nuevoNodo->ant = nuevoNodo;
    (*lista) = nuevoNodo;
    return;
  }

  nuevoNodo->sig = (*lista);
  nuevoNodo->ant = (*lista)->ant;
  (*lista)->ant->sig = nuevoNodo;
  (*lista)->ant = nuevoNodo;
  (*lista) = nuevoNodo;
}

//insert:: List List -> void
//inserta el primer nodo entre el segundo y el siguiente al segundo
void insert(List nodo, List ant) {
  nodo->ant = ant;
  nodo->sig = ant->sig;
  ant->sig->ant = nodo;
  ant->sig = nodo;
}

//insertion: List List Compara -> List
//compara el dato de nodo con los nodos desde su nodo anterior hasta start
//usando la funcion comp, hasta encontrar la posicion donde insertarlo
List insertion(List start, List nodo, FuncionMenor comp) {
// void list_agregar_ordenado(List *lista, void *dato, FuncionMenor menor) {
  int flag = 0;
  //usa flag para saber si ya se inserto el nodo
  List sig = nodo->sig;
  //guarda un puntero al nodo siguiente para poder seguir luego de
  //reinsertar el nodo actual

  if (sig == start && comp(nodo->dato, sig->dato)) {
    //si es el ultimo nodo que falta y confirmo la coparacion
    //con el primer nodo, evita pasar por toda la lista
    //y devuelve el nodo actual que ya es anterior al primero
    return nodo;
  }

  if (!comp(nodo->dato, nodo->ant->dato)) {
    //si la comparacion a su nodo anterior es negativa
    //el nodo actual ya esta en la posicion correcta
    flag++;
  } else {
    nodo->ant->sig = sig;
    sig->ant = nodo->ant;
    //conecta los nodos anterior y siguiente
    //porque va a cambiar el nodo actual de lugar

    for (List n = nodo->ant->ant; n != start->ant && !flag; n = n->ant) {
      if (!comp(nodo->dato, n->dato)) {
        //itera hacia atras hasta que la comparacion de negativa
        //e inserta el nodo luego del que comparo
        insert(nodo, n);
        flag++;
      }
    }
  }

  if (!flag) {
    //si no se inserto todavia es porque la comparacion
    //con el primer nodo dio positiva
    //entonces se debe insertar al principio
    insert(nodo, start->ant);
    if (sig == start) {
      //si el siguiente a insertar es el primero
      //ya no quedan nodos por insertar
      //y devuelve el nuevo primero
      return nodo;
    }
    //sino sigue insertando y apunto al nuevo primero
    return insertion(nodo, sig, comp);
  }

  if (sig == start)
    return start;
  return insertion(start, sig, comp);
}

/*
    Agrega un elemento al final de la lista.
*/
// void list_agregar_ordenado(List *lista, void *dato, FuncionMenor menor) {
//   Nodo *nuevoNodo = malloc(sizeof(Nodo));
//   nuevoNodo->dato = dato;

//   if (*lista == NULL) {
//     nuevoNodo->sig = nuevoNodo;
//     nuevoNodo->ant = nuevoNodo;
//     (*lista) = nuevoNodo;
//     return;
//   }

//   Nodo *nodo;

//   printf("\n\n**Nuevo**\n");

//   for (nodo = *lista; nodo->sig != (*lista); nodo = nodo->sig){
//     printf("Nuevo: ");
//     registro_imprimir((Registro)nuevoNodo->dato);
//     printf("\nActual: ");
//     registro_imprimir((Registro)nodo->dato);
//     if(!menor(nuevoNodo->dato, nodo->dato)) {
//       printf("Insertado");
//       nuevoNodo->sig = nodo;
//       nuevoNodo->ant = nodo->ant;
//       nodo->ant->sig = nuevoNodo;
//       nodo->ant = nuevoNodo;
//       if(menor(nuevoNodo->dato, (*lista)->dato)) {
//         *lista = nuevoNodo;
//       }
//       return;
//     }
//   }

//   printf("Fuera del for\n");
//   printf("Nuevo:");
//   registro_imprimir((Registro)nuevoNodo->dato);
//   printf("\nActual:");
//   registro_imprimir((Registro)nodo->dato);
//   printf("\n");

//  if(menor(nuevoNodo->dato, nodo->dato)) {
//    printf("Penultimo\n");
//     nuevoNodo->sig = nodo;
//     nuevoNodo->ant = nodo->ant;
//     nodo->ant->sig = nuevoNodo;
//     nodo->ant = nuevoNodo;
//   } else {
//     printf("Al final\n");
//     list_agregar_final(lista, dato);
//   }
//   if(menor(nuevoNodo->dato, (*lista)->dato)) {
//     *lista = nuevoNodo;
//   }
//   printf("Fin\n");
// }

void list_agregar_ordenado(List *lista, void *dato, FuncionMenor menor) {
  list_agregar_final(lista, dato);
}

List list_buscar(List lista, void *clave, FuncionIgual igual) {
  if (list_vacia(lista) && clave != NULL)
    return NULL;

  List nodo;
  int encontrado = 0;

  for (nodo = lista; nodo->sig != lista && !encontrado; nodo = nodo->sig) {
      if(nodo->dato != NULL)
        if(igual(clave, nodo->dato))
          return nodo;
  }

  if(nodo->dato != NULL)
    if(igual(clave, nodo->dato))
      return nodo;

  return NULL;
}

/*
    Agrega un elemento al inicio de la lista.
*/
void list_agregar_inicio(List *lista, void *dato) {
  Nodo *nuevoNodo = malloc(sizeof(Nodo));
  nuevoNodo->dato = dato;

  if (lista == NULL) {
    nuevoNodo->sig = nuevoNodo;
    nuevoNodo->ant = nuevoNodo;
    (*lista) = nuevoNodo;
    return;
  }

  nuevoNodo->sig = *lista;
  nuevoNodo->ant = (*lista)->ant;
  (*lista)->ant->sig = nuevoNodo;
  (*lista)->ant = nuevoNodo;
  (*lista) = nuevoNodo;
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
