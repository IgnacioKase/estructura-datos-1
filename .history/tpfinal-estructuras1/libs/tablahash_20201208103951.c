#include "tablahash_lse.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Crea una nueva tabla Hash vacía, con la capacidad dada.
 */
TablaHash* tablahash_crear(unsigned capacidad, FuncionHash hash, FuncionIgualdad igualdad) {
    // Pedimos memoria para la estructura principal y las casillas.
    TablaHash* tabla = malloc(sizeof(TablaHash));
    tabla->hash = hash;
    tabla->igualdad = igualdad;
    tabla->capacidad = capacidad;
    tabla->tabla = malloc(sizeof(CasillaHash) * capacidad);
    tabla->numElems = 0;

    // Inicializamos las casillas con datos nulos.
    for (unsigned idx = 0; idx < capacidad; ++idx) {
        tabla->tabla[idx].clave = NULL;
        tabla->tabla[idx].dato = NULL;
        tabla->tabla[idx].areaRebalse = list_crear();
    }

    return tabla;
}

/**
 * Inserta el dato en la tabla, asociado a la clave dada.
 */
void tablahash_insertar(TablaHash* tabla, void* clave, void* dato) {
    // Calculamos la posición de la clave dada, de acuerdo a la función hash.
    unsigned idx = tabla->hash(clave);
    idx = idx % tabla->capacidad;

    tabla->numElems++;

    if (tabla->tabla[idx].clave == NULL) {
        tabla->tabla[idx].clave = clave;
        tabla->tabla[idx].dato = dato;
    } else {
        CasillaHashOuter* new = malloc(sizeof(CasillaHashOuter));
        new->dato = dato;
        new->clave = clave;
        tabla->tabla[idx].areaRebalse = list_agregar_final(tabla->tabla[idx].areaRebalse, (void*)new);
    }
}

/**
 * Busca un elemento dado en la tabla, y retorna un puntero al mismo.
 * En caso de no existir, se retorna un puntero nulo.
 */
void* tablahash_buscar(TablaHash* tabla, void* clave) {
    // Calculamos la posición de la clave dada, de acuerdo a la función hash.

    unsigned idx = tabla->hash(clave);
    idx = idx % tabla->capacidad;

    // Si el lugar esta vacío, retornamos un puntero nulo.
    if (tabla->tabla[idx].clave == NULL)
        return NULL;

    if (tabla->igualdad(clave, tabla->tabla[idx].clave))
        return tabla->tabla[idx].dato;

    for (List temp = tabla->tabla[idx].areaRebalse; temp->sig != NULL; temp = temp->sig) {
        CasillaHashOuter* tempCasilla = (CasillaHashOuter*)temp->dato;
        if (tabla->igualdad(clave, (void*)tempCasilla->clave))
            return tempCasilla->dato;
    }

    return NULL;
}

/**
 * Elimina un elemento de la tabla.
 */
void tablahash_eliminar(TablaHash* tabla, void* clave) {
    // Calculamos la posición de la clave dada, de acuerdo a la función hash.
    unsigned idx = tabla->hash(clave);
    idx = idx % tabla->capacidad;

    // Si el lugar estaba ocupado, decrementamos el número de elementos.
    if (tabla->tabla[idx].clave != NULL)
        tabla->numElems--;

    // Vaciamos la casilla.
    tabla->tabla[idx].clave = NULL;
    tabla->tabla[idx].dato = NULL;
}

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash* tabla) {
    free(tabla->tabla);
    free(tabla);
}
