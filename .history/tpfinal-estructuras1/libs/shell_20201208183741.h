#ifndef __SHELL_H__
#define __SHELL_H__

#define  _GNU_SOURCE
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tablahash.h"
#include "list.h"
#include "registro.h"
#include "fecha.h"
#include "merge_sort.h"

#define MAXTABLA 10000000
#define DATASET_TAMANIO 7

/*
    Comentarios de las funciones en el archivo .c
*/


#define MAX_ARGS 100

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

int shell_command(const char *comando, TablaHash *tabla, const char *args[], int argc);

int loop_shell(char *buf, TablaHash *tabla);

Command match_command(const char* comando);

#endif