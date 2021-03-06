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

    return dias_mes[fecha.mes] + (fecha.mes == FEB ? es_anio_bisiesto(fecha.anio) : 0);
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

    long int dias = 0;
    Fecha temp;
    
    if( a.anio == b.anio ) {
        temp.anio = a.anio;
        for (temp.mes = a.mes + 1; temp.mes < b.mes; temp.mes++)
            dias += fecha_obtener_dias_en_mes(temp);
    } else {
        for (int i = a.anio; i < b.anio; i++)
            dias += fecha_es_anio_bisiesto(i) ? 366 : 365;

        temp.anio = a.anio;
        for (temp.mes = a.mes + 1; temp.mes < b.mes; temp.mes++)
            dias += fecha_obtener_dias_en_mes(temp);

        temp.anio = b.anio;
        for (temp.mes = a.mes + 1; temp.mes < b.mes; temp.mes++)
            dias += fecha_obtener_dias_en_mes(temp);
    }
}