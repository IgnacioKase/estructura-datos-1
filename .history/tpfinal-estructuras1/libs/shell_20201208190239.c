#include "shell.h"

/* Funcion auxiliar para obtener comando*/
Command match_command(const char* comando) {
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

void merge_sort_adaptado(void *lista, void *comp) {
    merge_sort((List *)lista, (Compara)comp);
}

void cargar_dataset(const char *archivo, TablaHash *tabla) {
    FILE *fp;

    printf("%s\n", archivo);

    assert((fp = fopen("query.csv", "r, ccs=UTF-8")));

    char fecha_ignorar[300], departamento[300], localidad[300];
    int confirmados, dia, mes, anio;
    int descartados;
    int en_estudio;
    int notificaciones;

    // Ignoramos los titulos de las columnas
    fgets(fecha_ignorar, 300, fp);

    Fecha fecha_nuevo;
    Registro nuevo;
    List lista;
    
    //2020-11-22T00:00:00-03:00,9 de Julio,POZO BORRADO,8,5,0,13
    while (fscanf(fp, "%d-%d-%dT%39[^,],%39[^,],%39[^,],%d,%d,%d,%d\n", &anio, &mes, &dia, fecha_ignorar, departamento, localidad, &confirmados, &descartados, &en_estudio, &notificaciones) != EOF) {
        fecha_nuevo = fecha_crear(dia, mes, anio);

        nuevo = registro_crear(fecha_nuevo, departamento, localidad, confirmados, descartados, en_estudio, notificaciones);
        
        lista = (List) tablahash_buscar(tabla, (void*) nuevo->clave);

        if(lista != NULL) {
            list_agregar_final(lista, (void *) nuevo);
        } else {
            lista = list_crear();
            list_agregar_final(lista, (void *) nuevo);
            tablahash_insertar(tabla, (void*) nuevo->clave, (void *) lista);
        }
        // registro_imprimir(nuevo);
    }
    
    for (unsigned idx = 0; idx < tabla->capacidad; ++idx) {
        if(tabla->tabla[idx].dato != NULL) {
            lista = (List)tabla->tabla[idx].dato;
            merge_sort((&lista, registro_menor);
        }
        if(tabla->tabla[idx].areaRebalse != NULL){
            list_recorrer_extra(tabla->tabla[idx].areaRebalse, merge_sort_adaptado, registro_menor, LIST_RECORRIDO_HACIA_ADELANTE);
        }
    }

    fclose(fp);
}

void imprimir_dataset(const char *archivo) {
    printf("%s", archivo);
}

void agregar_registro(const char *archivo) {
    printf("%s", archivo);
}

void eliminar_registro(const char *archivo) {
    printf("%s", archivo);
}

void buscar_pico(const char *archivo) {
    printf("%s", archivo);
}

void casos_acumulados(const char *archivo) {
    printf("%s", archivo);
}

void tiempo_duplicacion(const char *archivo) {
    printf("%s", archivo);
}

void graficar(const char *archivo) {
    printf("%s", archivo);
}

// Procesamiento de los comandos que no reciben intervalo
int shell_command(const char *comando, TablaHash *tabla, const char *args[], int argc) {
    int continuar = 1;
    int has_error = 0;
    switch (match_command(comando)) {
        case CARGAR_DATASET:
            has_error = argc != 1;
            if (!has_error)
                cargar_dataset(args[0], tabla);
            break;
        case IMPRIMIR_DATASET:
            has_error = argc != 1;
            if (!has_error)
                imprimir_dataset(args[0]);
            break;
        case AGREGAR_REGISTRO:
            has_error = argc != 1;
            if (!has_error)
                agregar_registro(args[0]);
            break;
        case ELIMINAR_REGISTRO:
            has_error = argc != 1;
            if (!has_error)
                eliminar_registro(args[0]);
            break;
        case BUSCAR_PICO:
            has_error = argc != 1;
            if (!has_error)
                buscar_pico(args[0]);
            break;
        case CASOS_ACUMULADOS:
            has_error = argc != 1;
            if (!has_error)
                casos_acumulados(args[0]);
            break;
        case TIEMPO_DUPLICACION:
            has_error = argc != 1;
            if (!has_error)
                tiempo_duplicacion(args[0]);
            break;
        case GRAFICAR:
            has_error = argc != 1;
            if (!has_error)
                graficar(args[0]);
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
    const char *argv[MAX_ARGS];
    int argc = 0;

    while(token != NULL && argc < MAX_ARGS) {
        argv[argc] = token;
        argc++;
        token = strtok(NULL, " ");
    }

    if(argv[0] != NULL && argc < MAX_ARGS)
        continuar = shell_command(argv[0], tabla,(argv + 1), (argc - 1));
    else
        error();
    return continuar;
}
