#include "../libs/shell.h"

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

unsigned long hash(void *str_arg)
{   
    unsigned char *str = (unsigned char *) str_arg;

    unsigned long hash = 5381;
    int c;

    while ((c = *str++), c)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int igualdad (void* a, void* b) {
    return !strcmp((const char *) a, (const char *) b);
}

int main() {
    // setlocale(LC_CTYPE, "");

    printf("\nIngrese 'help' para informacion sobre los comandos\n");

    TablaHash *tabla = tablahash_crear(MAXTABLA, hash, igualdad);
    char *line = NULL;
    int continuar = 1;
    size_t len = 0;
    // size_t lineSize = 0;

    // Bucle de Shell
    while (continuar) {
        printf(">> ");

        // lineSize = getline(&line, &len, stdin);
        getline(&line, &len, stdin);
        
        /* continuar = 0 indica que el usuario
        pidio salir */
        continuar = loop_shell(line, tabla);
    }
    
    tablahash_destruir(tabla);
    free(line);

    return 0;
}
