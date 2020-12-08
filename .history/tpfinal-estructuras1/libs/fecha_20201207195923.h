#ifndef __REGISTRO_H__
#define __REGISTRO_H__


typedef enum mes { ENE = 1, FEB, MAR, ABRIL, MAYI, JUNIIO,
              JUL, AUG, SEP, OCT, NOV, DEC } mes;
              
typedef struct _Fecha {
    short int dia;
    short int mes;
    short int año;
} Fecha;

#endif
