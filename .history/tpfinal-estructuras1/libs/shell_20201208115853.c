#include "shell.h"

#define MAX_ARGS 10

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

void cargar_dataset(char *archivo) {

}

void imprimir_dataset(char *archivo) {

}

void agregar_registro(char *archivo) {

}

void eliminar_registro(char *archivo) {

}

void buscar_pico(char *archivo) {

}

void casos_acumulados(char *archivo) {

}

void tiempo_duplicacion(char *archivo) {

}

void graficar(char *archivo) {

}

// Procesamiento de los comandos que no reciben intervalo
int shell_command(char *comando, char *args[], int argc) {
    int continuar = 1;
    int has_error = 0;
    switch (match_command(comando)) {
        case CARGAR_DATASET:
            has_error = argc != 1;
            if (!has_error)
                cargar_dataset(args[1]);
            break;
        case IMPRIMIR_DATASET:
            has_error = argc != 1;
            if (!has_error)
                imprimir_dataset(args);
            break;
        case AGREGAR_REGISTRO:
            has_error = argc != 1;
            if (!has_error)
                agregar_registro(args);
            break;
        case ELIMINAR_REGISTRO:
            has_error = argc != 1;
            if (!has_error)
                eliminar_registro(args);
            break;
        case BUSCAR_PICO:
            has_error = argc != 1;
            if (!has_error)
                buscar_pico(args);
            break;
        case CASOS_ACUMULADOS:
            has_error = argc != 1;
            if (!has_error)
                casos_acumulados(args);
            break;
        case TIEMPO_DUPLICACION:
            has_error = argc != 1;
            if (!has_error)
                tiempo_duplicacion(args);
            break;
        case GRAFICAR:
            has_error = argc != 1;
            if (!has_error)
                graficar(args);
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
            has_error = 1;
            break;
    }
    if(has_error)
        error();
    return continuar;
}


/* Identifica el comando guardado en buf
   (recibido por interprete o test_shell),
   ejecuta la operacion (o el error) correspondiente
   y retorna 0 si el comando indica salir del programa
   o 1 en otro caso, y se usa en loop en los programas anteriores */
int loop_shell(char *buf, TablaHash *tabla) {
    int continuar = 1;

    char *token = strtok(buf, " ");
    char *argv[MAX_ARGS];
    int argc = 0;

    while(token != NULL && argc < MAX_ARGS) {
        argv[argc] = token;
        argc++;
        *token = strtok(NULL, " ");
    }

    if(argv[0] != NULL && argc < MAX_ARGS)
        continuar = shell_command(argv[1], *(argv + 1), (argc - 1));
    else
        error();

    return continuar;
}
