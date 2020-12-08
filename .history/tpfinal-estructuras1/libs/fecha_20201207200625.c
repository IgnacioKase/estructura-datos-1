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
