#include "tablahash.h"


/* dictionary initialization code used in both DictCreate and grow */
TablaHash _tablahash_crear(int size, FuncionHash fun, FuncionIgualdad igualdad, Destruir destruir, DestruirInterno destruirInterno)
{
    TablaHash d;
    int i;

    d = malloc(sizeof(*d));

    assert(d != 0);

    d->size = size;
    d->n = 0;
    d->hash = fun;
    d->igualdad = igualdad;
    d->table = malloc(sizeof(struct elt *) * d->size);

    assert(d->table != 0);

    for(i = 0; i < d->size; i++) d->table[i] = 0;

    return d;
}

TablaHash tablahash_crear(FuncionHash fun, FuncionIgualdad igualdad, Destruir destruir, DestruirInterno destruirInterno)
{
    return _tablahash_crear(INITIAL_SIZE, fun, igualdad, destruir, destruirInterno);
}

void tablahash_destruir(TablaHash d)
{
    int i;
    struct elt *e;
    struct elt *next;

    for(i = 0; i < d->size; i++) {
        for(e = d->table[i]; e != 0; e = next) {
            next = e->next;

            free(e->key);
            destruir(e->value, destruir_extra);
            free(e);
        }
    }

    free(d->table);
    free(d);
}

static void _tablahash_crecer(TablaHash d)
{
    TablaHash d2;            /* new dictionary we'll create */
    struct tablaHash swap;   /* temporary structure for brain transplant */
    int i;
    struct elt *e;

    d2 = _tablahash_crear(d->size * GROWTH_FACTOR, d->hash, d->igualdad);

    for(i = 0; i < d->size; i++) {
        for(e = d->table[i]; e != 0; e = e->next) {
            /* note: this recopies everything */
            /* a more efficient implementation would
             * patch out the strdups inside DictInsert
             * to avoid this problem */
            tablahash_insertar(d2, e->key, e->value);
        }
    }

    /* the hideous part */
    /* We'll swap the guts of d and d2 */
    /* then call DictDestroy on d2 */
    swap = *d;
    *d = *d2;
    *d2 = swap;

    tablahash_destruir(d2);
}

/* insert a new key-value pair into an existing dictionary */
void tablahash_insertar(TablaHash d, char *key, void *value)
{
    struct elt *e;
    unsigned long h;

    assert(key);
    assert(value);

    e = malloc(sizeof(*e));

    assert(e);

    e->key = key;
    e->value = value;

    h = d->hash((void*)key) % d->size;

    e->next = d->table[h];
    d->table[h] = e;

    d->n++;

    /* grow table if there is not enough room */
    if(d->n >= d->size * MAX_LOAD_FACTOR) {
        _tablahash_crecer(d);
    }
}

/* return the most recently inserted value associated with a key */
/* or 0 if no matching key is present */
void * tablahash_buscar(TablaHash d, const char *key)
{
    struct elt *e;

    for(e = d->table[d->hash((void*)key) % d->size]; e != 0; e = e->next) {
        if(d->igualdad((void*)e->key, (void*)key)) {
            /* got it */
            return e->value;
        }
    }

    return 0;
}

/* delete the most recently inserted record with the given key */
/* if there is no such record, has no effect */
void tablahash_eliminar(TablaHash d, const char *key, Destruir destruir)
{
    struct elt **prev;          /* what to change when elt is deleted */
    struct elt *e;              /* what to delete */

    for(prev = &(d->table[d->hash((void*)key) % d->size]); 
        *prev != 0; 
        prev = &((*prev)->next)) {
        if(d->igualdad((void*)(*prev)->key, (void*)key)) {
            /* got it */
            e = *prev;
            *prev = e->next;

            free(e->key);
            destruir(e->value);
            free(e);

            return;
        }
    }
}