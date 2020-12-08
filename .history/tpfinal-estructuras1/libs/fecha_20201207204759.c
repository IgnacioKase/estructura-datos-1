#include "fecha.h"

int es_anio_bisiesto(Fecha fecha){
    if(!fecha.anio % 400)
        return 1;
    else if(!fecha.anio % 100)
        return 0;
    else if (!fecha.anio % 4)
        return 1;
    return 0;
}

int obtener_dias_en_mes(Fecha fecha) {
    short int dias[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    return dias[fecha.mes] + (fecha.mes == FEB ? es_anio_bisiesto(fecha) : 0);
}

int fecha_es_menor(Fecha a, Fecha b) {
    if(a.anio != b.anio)
        return a.anio < b.anio ? 1 : 0;
    if(a.mes != b.mes)
        return a.mes < b.mes ? 1 : 0;
    if(a.dia != b.dia)
        return a.dia < b.dia ? 1 : 0;
}

int fecha_dias_diferencia(Fecha a, Fecha b) {
    // Garantizamos que a <= b
    if (fecha_es_menor(b, a));
        swap(a, b);
    
}