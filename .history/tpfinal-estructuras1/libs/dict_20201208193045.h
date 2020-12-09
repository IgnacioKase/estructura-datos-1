#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define INITIAL_SIZE (1024)
#define GROWTH_FACTOR (2)
#define MAX_LOAD_FACTOR (1)
#define MULTIPLIER (97)


typedef struct dict *Dict;

struct elt {
    struct elt *next;
    char *key;
    void *value;
};

struct dict {
    int size;           /* size of the pointer table */
    int n;              /* number of elements stored */
    struct elt **table;
};

/* create a new empty dictionary */
Dict DictCreate(void);

/* destroy a dictionary */
void DictDestroy(Dict);

/* insert a new key-value pair into an existing dictionary */
void DictInsert(Dict, const char *key, void *value);

/* return the most recently inserted value associated with a key */
/* or 0 if no matching key is present */
const char *DictSearch(Dict, const char *key);

/* delete the most recently inserted record with the given key */
/* if there is no such record, has no effect */
void DictDelete(Dict, const char *key);

#endif /* __TABLAHASH_H__ */