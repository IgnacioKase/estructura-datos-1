#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__

#include <stdlib.h>
#include <assert.h>
#include <string.h> 

#define INITIAL_SIZE (1024)
#define GROWTH_FACTOR (2)
#define MAX_LOAD_FACTOR (1)
#define MULTIPLIER (97)


typedef struct tablaHash *TablaHash;

/**
 * Tipo de las funciones hash a ser consideradas por las tablas hash.
 */

typedef void (*DestruirExterno)(void *dato, void *func);
typedef void (*DestruirInterno)(void *dato);
typedef unsigned long (*FuncionHash)(void* clave);
typedef int (*FuncionIgualdad)(void*, void*);

struct elt {
    struct elt *next;
    void *key;
    void *value;
};

struct tablaHash {
    int size;           /* size of the pointer table */
    int n;              /* number of elements stored */
    FuncionHash hash;
    FuncionIgualdad igualdad;
    DestruirExterno destruir;
    DestruirInterno destruir_interno;
    struct elt **table;
};

/* create a new empty dictionary */
TablaHash tablahash_crear(FuncionHash fun, FuncionIgualdad igualdad, DestruirExterno destruir, DestruirInterno destruir_interno);

/* destroy a dictionary */
void tablahash_destruir(TablaHash d);

/* insert a new key-value pair into an existing dictionary */
void tablahash_insertar(TablaHash d, char *key, void *value);

/* return the most recently inserted value associated with a key */
/* or 0 if no matching key is present */
void * tablahash_buscar(TablaHash d, const char *key);

/* delete the most recently inserted record with the given key */
/* if there is no such record, has no effect */
void tablahash_eliminar(TablaHash d, const char *key);

#endif /* __TABLAHASH_H__ */