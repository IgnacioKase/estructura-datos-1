#include <stdio.h>
#include <stdlib.h>

#include "tablahash_lse.h"

int igualdad(void* clave1, void* clave2) {
    int* p = clave1;
    int* q = clave2;
    return *p == *q;
}

unsigned hash(void* clave) {
    int* p = clave;
    return *p;
}

int main() {
    TablaHash* tabla = tablahash_crear(10, hash, igualdad);
    return 0;
}