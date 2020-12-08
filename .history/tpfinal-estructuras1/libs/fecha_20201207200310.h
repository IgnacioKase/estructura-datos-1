#ifndef __REGISTRO_H__
#define __REGISTRO_H__


typedef enum _Mes { ENE = 1, FEB, MAR, ABR, MAY, JUN,
              JUL, AGO, SEP, OCT, NOV, DEC } Mes;


int es_anio_bisiesto()
              
typedef struct _Fecha {
    short int dia;
    Mes mes;
    short int anio;
} Fecha;

#endif
