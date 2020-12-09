#include "registro.h"

Registro registro_crear(Fecha *fecha, char *departamento, char *localidad, int confirmados, int descartados, int en_estudio, int notificaciones) {
    Registro nuevo;
    nuevo->fecha = fecha;
    nuevo->departamento = departamento;
    nuevo->localidad = localidad;
    nuevo->confirmados = confirmados;
    nuevo->descartados = descartados;
    nuevo->en_estudio = en_estudio;
    nuevo->notificaciones = notificaciones;
    return nuevo;
} 

void registro_destruir(Registro registro) {
    free(registro->fecha);
    free(registro->departamento);
    free(registro->localidad);
    free(registro);
}
