#include "registro.h"

Registro registro_crear(Fecha *fecha, char *departamento, char *localidad, int confirmados, int descartados, int en_estudio, int notificaciones) {
    Registro nuevo = malloc(sizeof(Registro));
    nuevo->fecha = fecha;
    nuevo->departamento = departamento;
    nuevo->localidad = localidad;
    nuevo->confirmados = confirmados;
    nuevo->descartados = descartados;
    nuevo->en_estudio = en_estudio;
    nuevo->notificaciones = notificaciones;
    return nuevo;
} 

char* registro_obtener_clave(Registro registro) {
    char *s = malloc(sizeof(char*) * (strlen(registro->departamento) + strlen(registro->localidad) + 2));
    strcpy(s, registro->departamento);
    strcat(s, "-");
    strcat(s, registro->localidad);
    return s;
}

void registro_destruir(Registro registro) {
    free(registro->fecha);
    free(registro->departamento);
    free(registro->localidad);
    free(registro);
}

void registro_imprimir(Registro registro) {
    Fecha fecha = registro->fecha;
    printf("%d-%d-%d,%s,%s,%d,%d,%d,%d\n", registro->fecha->anio, fecha->mes, fecha->dia, registro->departamento, registro->localidad, registro->confirmados, registro->descartados, registro->en_estudio, registro->notificaciones);
}