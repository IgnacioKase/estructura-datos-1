#ifndef __SHELL_H__
#define __SHELL_H__

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tablahash.h"
#include "list.h"

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
} Command;


void help();
void error();

int shell_command(char *comando, char *args[], int argc);

int loop_shell(char buf[MAX_STDIN], ITree* itree);

Command match_command(char* comando);

ITree shell_interval_command(char comando[6], double* arg, ITree itree);

#endif