#include "../libs/shell.h"
#include "tablahash.h"

#define MAXTABLA 10000000

/*
 TRABAJO PRÁCTICO 2
 ÁRBOL AVL DE INTERVALOS DOUBLE CON INTERPRETE
 INTEGRANTES:
       - VALENTINA, PRATO
       - IGNACIO, KASEVICH
 GIT: https://github.com/IgnacioKase/tp2-estructuras1
 10/06/2020
*/

/*
 LEER PDFs/Informe.pdf
*/

unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int main() {
    printf("\nIngrese 'help' para informacion sobre los comandos\n");

    TablaHash *tabla = tablahash_crear(MAXTABLA, hash, strcmp);
    int continuar = 1;
    char buf[MAX_STDIN];

    // Bucle de Shell
    while (continuar) {
        printf(">> ");

        fgets(buf, MAX_STDIN - 1, stdin);
        
        /* continuar = 0 indica que el usuario
        pidio salir */
        continuar = loop_shell(buf, tabla);
    }
    
    itree_destruir(itree);
    return 0;
}
