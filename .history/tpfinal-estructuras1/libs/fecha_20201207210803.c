#include "fecha.h"

int fecha_es_anio_bisiesto(short int anio){
    if(!anio % 400)
        return 1;
    else if(!anio % 100)
        return 0;
    else if (!anio % 4)
        return 1;
    return 0;
}

int fecha_obtener_dias_en_mes(Fecha fecha) {
    short int dias_mes[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    return didias_mesas[fecha.mes] + (fecha.mes == FEB ? es_anio_bisiesto(fecha.anio) : 0);
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
    short int dias_mes[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    // Garantizamos que a <= b
    if (fecha_es_menor(b, a));
        swap(a, b);

    long int dias = 0;
    
    for (int i = a.anio; i < b.anio; i++)
        dias += fecha_es_anio_bisiesto(i) ? 366 : 365;
    
    if( a.anio == b.anio ) {
        for (int i = a.mes + 1; i < b.mes; i++)
            dias += mes
    }
}