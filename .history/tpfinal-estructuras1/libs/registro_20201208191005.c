#include "registro.h"

char* _registro_obtener_clave(Registro registro) {
    char *s = malloc(sizeof(char*) * (strlen(registro->departamento) + strlen(registro->localidad) + 2));
    strcpy(s, registro->departamento);
    strcat(s, "-");
    strcat(s, registro->localidad);
    return s;
}

Registro registro_crear(Fecha fecha, char *departamento, char *localidad, int confirmados, int descartados, int en_estudio, int notificaciones) {
    Registro nuevo = malloc(sizeof(struct _Registro));
    nuevo->fecha = fecha;
    nuevo->departamento = departamento;
    nuevo->localidad = localidad;
    nuevo->confirmados = confirmados;
    nuevo->descartados = descartados;
    nuevo->en_estudio = en_estudio;
    nuevo->notificaciones = notificaciones;
    nuevo->clave = _registro_obtener_clave(nuevo);
    return nuevo;
} 

void registro_destruir(Registro registro) {
    free(registro->fecha);
    free(registro->departamento);
    free(registro->localidad);
    free(registro->clave);
    free(registro);
}

void registro_imprimir((void *registro_void) {
    registro = ()
    printf("%d-%d-%d,%s,%s,%d,%d,%d,%d\n", registro->fecha->anio, ((int) registro->fecha->mes), registro->fecha->dia, registro->departamento, registro->localidad, registro->confirmados, registro->descartados, registro->en_estudio, registro->notificaciones);
}

int registro_menor(void *a, void *b) {
    return fecha_es_menor(((Registro)a)->fecha, ((Registro)b)->fecha);
}