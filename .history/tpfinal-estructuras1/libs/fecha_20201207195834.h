#ifndef __REGISTRO_H__
#define __REGISTRO_H__


typedef enum meses { JAN = 1, FEB, MAR, APR, MAY, JUN,
              JUL, AUG, SEP, OCT, NOV, DEC } months;

typedef struct _Fecha {
    short int dia;
    short int mes;
    short int año;
} Fecha;

#endif
