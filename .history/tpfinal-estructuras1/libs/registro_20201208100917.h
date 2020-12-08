#ifndef __REGISTRO_H__
#define __REGISTRO_H__

typedef struct _Registro {
    double intervalo[2];
    double max;
    struct _ITNodo *left;
    struct _ITNodo *right;
} Registro;

#endif
