#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libs/list.h"
#include "libs/persona.h"

#define MAX_STR_LENGTH 200

void imprimir_lista(List *list);
int checkFiles(FILE *files[], int n);

int main(int argc, char *argv[])
{
    //Abrimos los archivos correspondientes
    //char *PATH_IN = argv[1];
    char *PATH_IN = "output/out.out";

    FILE *fIn = fopen(PATH_IN, "r");
    FILE *files[] = {fIn};

    //Si no se puede abrir algún archivo, cortamos la ejecución
    if (checkFiles(files, (int)(sizeof(files) / sizeof(files[0]))) == -1)
        return -1;
    ///////////////////////////////////////////////////

    List list = list_crear();
    char *line = malloc(sizeof(char) * MAX_STR_LENGTH); //buffer para lectura

    while (fgets(line, MAX_STR_LENGTH - 1, fIn) != NULL)
    {
        printf(line);
        persona_cargar(line, list);
    }
    ///////////////////////////////////////////////////

    //list_recorrer(list, persona_imprimir, LIST_RECORRIDO_HACIA_ADELANTE);
    //list_destruir(list, persona_destruir);
    getchar();
    fclose(fIn);
    return 0;
}

/*
    Recibe una linea del archivo de entrada
    y carga los datos en @p, siendo los datos
    Nombre
    Apellido
    Ciudad (código numerico)
    Edad
    Género (char correspondiente)
    Género de interés (char correspondiente)
*/

/*
    Recibe un array de FILE* y chequea que no
    sean NULL, si alguno lo es, devuelve -1
    en caso contrario, devuelve 0
*/
int checkFiles(FILE *files[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (files[i] == NULL)
        {
            perror("Error opening: a file.");
            return -1;
        }
    }
    return 0;
}