#include "registro.h"

char* registro_construir_clave(const char *departamento, const char *localidad) {
    char *s = malloc(sizeof(char*) * (strlen(departamento) + strlen(localidad) + 2));
    strcpy(s, departamento);
    strcat(s, "-");
    strcat(s, localidad);
    return s;
}

char* _registro_obtener_clave(Registro registro) {
    return registro_construir_clave(registro->departamento, registro->localidad);
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
    if (registro == NULL)
        return;
    fecha_destruir(registro->fecha);
    if(strlen(registro->departamento) > 0)
        free(registro->departamento);
    if(strlen(registro->localidad) > 0)
        free(registro->localidad);
    if(strlen(registro->clave) > 0 && registro->clave != NULL)
        free(registro->clave);
    free(registro);
}

void registro_destruir_void(void *registro) {
    registro_destruir((Registro)registro);
}

void registro_imprimir(void *registro_void) {
    Registro registro = (Registro) registro_void;
    printf(FORMATO_IMPRIMIR);
}

void registro_imprimir_archivo(void *registro_void, void* archivo) {
    Registro registro = (Registro) registro_void;
    fprintf((FILE *)archivo, FORMATO_IMPRIMIR);
}

int registro_menor(void *a, void *b) {
    int es_menor = fecha_es_menor(((Registro)a)->fecha, ((Registro)b)->fecha);
    registro_imprimir((Registro)a);
    registro_imprimir((Registro)b);
    return es_menor;
}

int registro_igual_por_fecha(void *a, void *b) {
    // registro_imprimir((Registro)a);
    // registro_imprimir((Registro)b);
    return fecha_es_igual(((Registro)a)->fecha, ((Registro)b)->fecha);
}

// cargar_dataset db/query.csv
// casos_acumulados 2020-11-12 Rosario "PUEBLO URANGA"
// eliminar_registro 2020-11-12 Rosario "PUEBLO URANGA"
// casos_acumulados 2020-11-12 Rosario "PUEBLO URANGA"
// agregar_registro 2020-11-12 Rosario "PUEBLO URANGA" 10 20 0
// casos_acumulados 2020-11-12 Rosario "PUEBLO URANGA"
// agregar_registro 2020-11-12 Rosario "PUEBLO URANGA" 20 30 0
// casos_acumulados 2020-11-12 Rosario "PUEBLO URANGA"
// eliminar_registro 2020-11-12 Rosario "PUEBLO URANGA"
// casos_acumulados 2020-11-12 Rosario "PUEBLO URANGA"
// agregar_registro 2020-11-12 DEPTO "Ciudad de prueba" 20 30 0
// casos_acumulados 2020-11-12 DEPTO "Ciudad de prueba"
// eliminar_registro 2020-11-12 DEPTO "Ciudad de prueba"
// casos_acumulados 2020-11-12 DEPTO "Ciudad de prueba"