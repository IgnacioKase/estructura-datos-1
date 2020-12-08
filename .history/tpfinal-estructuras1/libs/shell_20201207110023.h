#ifndef __SHELL_H__
#define __SHELL_H__

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "intervalo.h"
#include "itree.h"

/*
    Comentarios de las funciones en el archivo .c
*/


#define MAX_STDIN 80

typedef enum {
    CARGAR_DATASET,
    IMPRIMIR_DATASET,
    AGREGAR_REGISTRO,
    ELIMINAR_REGISTRO,
    BUSCAR_PICO,
    CASOS_ACUMULADOS,
    TIEMPO_DUPLICACION,
    GRAFICAR,
    SALIR,
    IMPRIMIR2D,
    HELP
} Commands;


void help();

int shell_simple_command(char comando[6], ITree itree);

int loop_shell(char buf[MAX_STDIN], ITree* itree);

Commands match_simple_command(char* comando);

ITree shell_interval_command(char comando[6], double* arg, ITree itree);

#endif