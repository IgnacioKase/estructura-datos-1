#ifndef __REGISTRO_H__
#define __REGISTRO_H__


typedef enum _Mes { ENE = 1, FEB, MAR, ABR, MAY, JUN,
              JUL, AGO, SEP, OCT, NOV, DEC } Mes;


int is_leap_year()
              
typedef struct _Fecha {
    short int dia;
    Mes mes;
    short int año;
} Fecha;

#endif
