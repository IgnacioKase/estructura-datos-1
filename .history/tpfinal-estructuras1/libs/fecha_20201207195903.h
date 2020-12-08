#ifndef __REGISTRO_H__
#define __REGISTRO_H__


typedef enum mes { ENERO = 1, FEBRERO, MARZO, ABRIL, MAY, JUN,
              JUL, AUG, SEP, OCT, NOV, DEC } mes;
              
typedef struct _Fecha {
    short int dia;
    short int mes;
    short int año;
} Fecha;

#endif
