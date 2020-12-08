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

// Procesamiento de los comandos que no reciben intervalo
int shell_simple_command(char comando[6], ITree itree) {
    int continuar = 1;
    switch (match_simple_command(comando)) {
        case CARGAR_DATASET:
            puts("");
            break;
        case IMPRIMIR_DATASET:
            puts("");
            break;
        case AGREGAR_REGISTRO:
            puts("");
            break;
        case ELIMINAR_REGISTRO:
            puts("");
            break;
        case BUSCAR_PICO:
            puts("");
            break;
        case CASOS_ACUMULADOS:
            puts("");
            break;
        case TIEMPO_DUPLICACION:
            puts("");
            break;
        case GRAFICAR:
            puts("");
            break;
        case SALIR:
            continuar = 0;
            break;
        case HELP:
            help();
            break;
        case IMPRIMIR2D:
            itree_imprimir_2d(itree);
            break;
        default:
            printf("ERROR: comando invalido.\n");
            printf("Ingrese 'help' para informacion sobre los comandos.\n");
            break;
    }
    return continuar;
}

// Procesamiento de los comandos que reciben intervalo
ITree shell_interval_command(char comando[6], double* arg, ITree itree) {
    /* los comandos que reciben intervalo tienen 1 caracter
       y se debe chequear que el intervalo sea valido
       (que el final no sea menor al comienzo) */
    if (!intervalo_es_valido(arg)) {
        printf("ERROR: intervalo invalido.\n");
        printf("El extremo izquierdo no puede superar al derecho\n");
        return itree;
    }
    if (strlen(comando) != 1) {
        printf("ERROR: comando invalido.\n");
        printf("Ingrese 'help' para informacion sobre los comandos.\n");
        return itree;
    }

    switch (match_interval_command(comando[0])) {
        case INSERTAR:
            itree = itree_insertar(itree, arg);
            break;
        case ELIMINAR:
            itree = itree_eliminar(itree, arg);
            break;
        case INTERSECAR:
            if (itree_intersecar(itree, arg))
                printf("Si\n");
            else
                printf("No\n");
            break;
        default:
            printf("ERROR: comando invalido.\n");
            printf("Ingrese 'help' para informacion sobre los comandos.\n");
            break;
    }
    return itree;
}

/* Identifica el comando guardado en buf
   (recibido por interprete o test_shell),
   ejecuta la operacion (o el error) correspondiente
   y retorna 0 si el comando indica salir del programa
   o 1 en otro caso, y se usa en loop en los programas anteriores */
int loop_shell(char *buf, ITree* itree) {
    int continuar = 1;
    
    char *token = strtok(buf, " ");

    while(token != NULL)

    return continuar;
}
