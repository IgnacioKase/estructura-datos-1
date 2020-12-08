#ifndef __REGISTRO_H__
#define __REGISTRO_H__


typedef enum _Mes { ENE = 1, FEB, MAR, ABR, MAY, JUN,
              JUL, AGO, SEP, OCT, NOV, DEC } mes;
              
typedef struct _Fecha {
    short int dia;
    mes mes;
    short int año;
} Fecha;

#endif
