#ifndef __REGISTRO_H__
#define __REGISTRO_H__

#include "stdlib.h"
#include "string.h"

#include "fecha.h"

typedef struct _Registro {
    Fecha *fecha;
    char *departamento;
    char *localidad;
    int confirmados;
    int descartados;
    int en_estudio;
    int notificaciones;
} *Registro;

Registro registro_crear(Fecha *fecha, char *departamento, char *localidad, int confirmados, int descartados, int en_estudio, int notificaciones); 

void registro_destruir(Registro registro);

#endif
