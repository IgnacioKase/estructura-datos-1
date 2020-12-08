#include "shell.h"

/* Funcion auxiliar para obtener comando*/
Command match_command(char* comando) {
    if (!strcmp(comando, "cargar_dataset"))
        return CARGAR_DATASET;
    if (!strcmp(comando, "imprimir_dataset"))
        return IMPRIMIR_DATASET;
    if (!strcmp(comando, "agregar_registro"))
        return AGREGAR_REGISTRO;
    if (!strcmp(comando, "eliminar_registro"))
        return ELIMINAR_REGISTRO;
    if (!strcmp(comando, "buscar_pico"))
        return BUSCAR_PICO;
    if (!strcmp(comando, "casos_acumulados"))
        return CASOS_ACUMULADOS;
    if (!strcmp(comando, "tiempo_duplicacion"))
        return TIEMPO_DUPLICACION;
    if (!strcmp(comando, "graficar"))
        return GRAFICAR;
    if (!strcmp(comando, "salir"))
        return SALIR;
    if (!strcmp(comando, "help"))
        return HELP;
    if (!strcmp(comando, "print"))
        return IMPRIMIR2D;
    return -1;
}


// Informacion sobre los comandos posibles
void help() {
    printf("\nComandos:\n");
    printf("i [a,b]: inserta el intervalo [a,b] en el arbol\n");
    printf("e [a,b]: elimina el intervalo [a,b] del arbol\n");
    printf("? [a,b]: interseca el intervalo [a,b] ");
    printf("con los intervalos del arbol\n");
    printf("dfs: imprime los intervalos del arbol ");
    printf("con recorrido primero en profundidad\n");
    printf("bfs: imprime los intervalos del arbol ");
    printf("con recorrido primero a lo ancho\n");
    printf("print: imprime los intervalos en forma de arbol\n");
    printf("salir: destruye el arbol y termina el programa\n\n");
    printf("Recuerde que los intervalos deben contener numeros\n\n");
}

void error() {
                printf("ERROR: comando invalido.\n");
            printf("Ingrese 'help' para informacion sobre los comandos.\n");
}

// Procesamiento de los comandos que no reciben intervalo
int shell_command(char *comando) {
    int continuar = 1;
    switch (match_simple_command(comando)) {
        case CARGAR_DATASET:
            break;
        case IMPRIMIR_DATASET:
            break;
        case AGREGAR_REGISTRO:
            break;
        case ELIMINAR_REGISTRO:
            break;
        case BUSCAR_PICO:
            break;
        case CASOS_ACUMULADOS:
            break;
        case TIEMPO_DUPLICACION:
            break;
        case GRAFICAR:
            break;
        case SALIR:
            continuar = 0;
            break;
        case HELP:
            help();
            break;
        case IMPRIMIR2D:
            break;
        default:

            break;
    }
    return continuar;
}


/* Identifica el comando guardado en buf
   (recibido por interprete o test_shell),
   ejecuta la operacion (o el error) correspondiente
   y retorna 0 si el comando indica salir del programa
   o 1 en otro caso, y se usa en loop en los programas anteriores */
int loop_shell(char *buf, ITree* itree) {
    int continuar = 1;
    
    char *token = strtok(buf, " ");

    if(token != NULL) {
        continuar = shell_command(token);
    } else {
        printf("ERROR: comando invalido.\n");
        printf("Ingrese 'help' para informacion sobre los comandos.\n");
    }

    return continuar;
}
