#ifndef __FECHA_H__
#define __FECHA_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct _Fecha {
    int dia;
    int mes;
    int anio;
} *Fecha;

Fecha fecha_crear(int dia, int mes, int anio);

void fecha_destruir(Fecha fecha);

int fecha_es_anio_bisiesto(int anio);

int fecha_obtener_dias_en_mes(Fecha fecha);

int fecha_es_menor(Fecha a, Fecha b);

int fecha_es_igual(Fecha a, Fecha b);

int fecha_dias_diferencia(Fecha a, Fecha b);

Fecha fecha_analizar(const char *fecha);

#endif
