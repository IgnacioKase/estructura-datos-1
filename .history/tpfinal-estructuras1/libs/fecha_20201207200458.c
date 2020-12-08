#include "fecha.h"

int es_anio_bisiesto(Fecha fecha){
    if(fecha.anio % 400 == 0)
    printf("%d is a leap year.n", fecha.anio);
    else if(fecha.anio % 100 == 0)
    printf("%d isn't a leap year.n", fecha.anio);
    else if (fecha.anio % 4 == 0)
    printf("%d is a leap year.n", fecha.anio);
    else
    printf("%d isn't a leap year.n", year);
}
