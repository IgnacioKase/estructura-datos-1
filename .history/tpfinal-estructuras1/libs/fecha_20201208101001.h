#ifndef __FECHA_H__
#define __FECHA_H__


typedef enum _Mes { ENE = 1, FEB, MAR, ABR, MAY, JUN,
              JUL, AGO, SEP, OCT, NOV, DEC } Mes;
              
typedef struct _Fecha {
    short int dia;
    Mes mes;
    short int anio;
} Fecha;


int fecha_es_anio_bisiesto(short int anio);

int fecha_obtener_dias_en_mes(Fecha fecha);

int fecha_es_menor(Fecha a, Fecha b);

int fecha_dias_diferencia(Fecha a, Fecha b);

#endif
