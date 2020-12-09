#ifndef __REGISTRO_H__
#define __REGISTRO_H__

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "fecha.h"

#define REGISTRO_CABECERA "Fecha,Departamento,Localidad,Confirmados,Descartados,En estudio,Notificaciones"
#define FORMATO_IMPRIMIR "%d%c%d%c%d,%s,%s,%d,%d,%d,%d\n", registro->fecha->anio, 45, ((int) registro->fecha->mes), 45, registro->fecha->dia, registro->departamento, registro->localidad, registro->confirmados, registro->descartados, registro->en_estudio, registro->notificaciones

typedef struct _Registro {
    Fecha fecha;
    char *departamento;
    char *localidad;
    int confirmados;
    int descartados;
    int en_estudio;
    int notificaciones;
    char *clave;
} *Registro;

Registro registro_crear(Fecha fecha, char *departamento, char *localidad, int confirmados, int descartados, int en_estudio, int notificaciones); 

void registro_destruir(Registro registro);

void registro_destruir_void(void *registro);

void registro_imprimir(void *registro_void);

void registro_imprimir_archivo(void *registro_void, void* archivo);

int registro_menor(void *a, void *b);

char* registro_construir_clave(const char *departamento, const char *localidad);

#endif
