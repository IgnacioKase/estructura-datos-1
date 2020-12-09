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

void cargar_dataset(const char *archivo, TablaHash tabla) {
    FILE *fp = fopen(archivo, "r, ccs=UTF-8");

    if(fp == NULL) {
        printf("ERROR: no se pudo acceder a la ruta indicada: %s. \nRevise el path y asegurese que existan las carpetas contenedoras y el archivo correspondiente.\n", archivo);
        return;
    }

    char fecha_ignorar[300], departamento[300], localidad[300], *departamento_copia, *localidad_copia;
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
        
        departamento_copia = malloc(sizeof(char) * strlen(departamento) + 1);
        localidad_copia = malloc(sizeof(char) * strlen(localidad) + 1);

        strcpy(departamento_copia, departamento);
        strcpy(localidad_copia, localidad);

        nuevo = registro_crear(fecha_nuevo, departamento_copia, localidad_copia, confirmados, descartados, en_estudio, notificaciones);   

        lista = (List) tablahash_buscar(tabla, (void*) nuevo->clave);

        if(lista != NULL) {
            lista = list_agregar_ordenado(lista, (void *) nuevo, registro_menor);
        } else {
            lista = list_crear();
            lista = list_agregar_final(lista, (void *) nuevo);
            tablahash_insertar(tabla, (void*) nuevo->clave, (void *) lista);
        }
    }

    printf("Archivo '%s' cargado con éxito\n", archivo);
    fclose(fp);
}

void imprimir_dataset(const char *archivo, TablaHash tabla) {
    FILE *fp = fopen(archivo, "w+, ccs=UTF-8");

    if(fp == NULL) {
        printf("ERROR: no se pudo acceder a la ruta indicada: %s.\nRevise el path y asegurese que existan las carpetas contenedoras.\n", archivo);
        return;
    }

    struct elt *e;

    fprintf(fp, REGISTRO_CABECERA);

    for(int i = 0; i < tabla->size; i++) {
        for(e = tabla->table[i]; e != 0; e = e->next) {
            list_recorrer_extra((List)e->value, registro_imprimir_archivo, (void*) fp, LIST_RECORRIDO_HACIA_ADELANTE);
        }
    }

    printf("Archivo '%s' creado con éxito\n", archivo);
    fclose(fp);
}

//0-fecha 1-departamento 2-localidad 3-confirmados 4-descartados 5-enEstudio
void agregar_registro(const char *argv[6], TablaHash tabla) {
    Fecha fecha = fecha_analizar(argv[0]);
    char *clave = registro_construir_clave(argv[1], argv[2]);
    List lista = (List) tablahash_buscar(tabla, clave);
    Registro busqueda = registro_crear(fecha, "", "", 0, 0, 0, 0);

    if(!list_vacia(lista)) {
        List nodo = list_buscar(lista, busqueda, registro_igual_por_fecha);
        if(!list_vacia(nodo)) {
            Registro registro = (Registro) nodo->dato;
            printf("Se encontró un registro para esta fecha: %s\n, el mismo será remplazado. Registro correspondiente: ", argv[0]);
            registro_imprimir(registro);
            fecha_destruir(fecha);
            registro->confirmados = atoi(argv[3]);
            registro->descartados = atoi(argv[4]);
            registro->en_estudio = atoi(argv[5]);
            registro->notificaciones = registro->confirmados + registro->descartados + registro->en_estudio;
            printf("Registro reemplazado con éxito.\nRegistro actual: ");
            registro_imprimir(registro);
        } else {
            Registro nuevo = registro_crear(fecha, argv[1], argv[2], atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), 0);
            printf("No se encontraron registros para esta localidad: %s y fecha: %s\n", clave, fecha_char);    
        }
    } else {
        printf("No se encontraron registros para esta localidad: %s\n", clave);
    }

    free(clave);
}

void eliminar_registro(TablaHash tabla, const char *fecha_char, const char *departamento, const char *localidad) {
    char *clave = registro_construir_clave(departamento, localidad);
    Fecha fecha = fecha_analizar(fecha_char);
    List lista = (List) tablahash_buscar(tabla, clave);

    Registro busqueda = registro_crear(fecha, "", "", 0, 0, 0, 0);

    if(!list_vacia(lista)) {
        List nodo = list_buscar(lista, busqueda, registro_igual_por_fecha);
        if(!list_vacia(nodo)) {
            if(nodo->sig != NULL)
                nodo->sig->ant = nodo->ant;
            if(nodo->ant != NULL)
                nodo->ant->sig = nodo->sig;
            registro_destruir((Registro)nodo->dato);
            free(nodo);
        } else {
            printf("No se encontraron registros para esta localidad: %s y fecha: %s\n", clave, fecha_char);    
        }
    } else {
        printf("No se encontraron registros para esta localidad: %s\n", clave);
    }

    registro_destruir(busqueda);
    free(clave);
}

void buscar_pico(const char *archivo) {
    printf("%s", archivo);
}

void casos_acumulados(TablaHash tabla, const char *fecha_char, const char *departamento, const char *localidad) {
    char *clave = registro_construir_clave(departamento, localidad);
    Fecha fecha = fecha_analizar(fecha_char);
    Registro busqueda = registro_crear(fecha, "", "", 0, 0, 0, 0);
    List lista = (List) tablahash_buscar(tabla, clave);

    if(!list_vacia(lista)) {
        List nodo = list_buscar(lista, busqueda, registro_igual_por_fecha);
        if(!list_vacia(nodo)) {
            Registro registro = (Registro) nodo->dato;
            printf("Casos acumulados hasta la fecha: %d\nRegistro correspondiente: ", registro->confirmados);
            registro_imprimir(registro);
        } else {
            printf("No se encontraron registros para esta localidad: %s y fecha: %s\n", clave, fecha_char);    
        }
        
    } else {
        printf("No se encontraron registros para esta localidad: %s\n", clave);
    }

    registro_destruir(busqueda);
    free(clave);
}

void tiempo_duplicacion(const char *archivo) {
    printf("%s", archivo);
}

void graficar(const char *archivo) {
    printf("%s", archivo);
}

// Procesamiento de los comandos que no reciben intervalo
int shell_command(const char *comando, TablaHash tabla, const char *args[], int argc) {
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
                imprimir_dataset(args[0], tabla);
            break;
        case AGREGAR_REGISTRO:
            has_error = argc != 6;
            if (!has_error)
                agregar_registro(args, tabla);
            break;
        case ELIMINAR_REGISTRO:
            has_error = argc != 3;
            if (!has_error)
                eliminar_registro(tabla, args[0], args[1], args[2]);
            break;
        case BUSCAR_PICO:
            has_error = argc != 1;
            if (!has_error)
                buscar_pico(args[0]);
            break;
        case CASOS_ACUMULADOS:
            has_error = argc != 3;
            if (!has_error)
                casos_acumulados(tabla, args[0], args[1], args[2]);
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

int analizar_argumentos(char *s, char *argv[MAX_ARGS]) {
    //   const char *start;
    int argc = 0;
    int estado = ' ';
    argv[0] = s;
    while (*s && argc < MAX_ARGS) {
        switch (estado) {
            case '\f':
            case '\t':
            case '\r':
            case '\v':
            case '\n':
            case ' ':
                if (*s == '\"') {
                    estado = '\"';
                    *s = ' ';
                } else if (*s != ' ') {
                    estado = 'T';
                }
                break;
            case 'T': // non-quoted text
                if (*s == ' ') {
                    estado = ' ';
                    argc++;
                    *s = '\0';
                    argv[argc] = s + 1;
                } else if (*s == '\"') {
                    estado = '\"';
                }
                break;
            case '\"': // Inside a quote
                if (*s == '\"') {
                    estado = 'T';
                    *s = ' ';
                }
                break;
            }
        s++;
    }
    argc++;
    for (int i = 0; i < argc; i++){
        trim(argv[i], " \n\t\f\r\v");
    }
  return argc;
}


/* Identifica el comando guardado en buf
   (recibido por interprete o test_shell),
   ejecuta la operacion (o el error) correspondiente
   y retorna 0 si el comando indica salir del programa
   o 1 en otro caso, y se usa en loop en los programas anteriores */
int loop_shell(char *buf, TablaHash tabla) {

    int continuar = 1;

    // char *token = strtok(buf, "\" ");
    char *argv[MAX_ARGS];
    // int argc = 0;

    // while(token != NULL && argc < MAX_ARGS) {
    //     argv[argc] = token;
    //     argc++;
    //     printf("%s", token);
    //     token = strtok(NULL, "\" ");
    // }

    int argc = analizar_argumentos(buf, argv);

    // printf("argc: %d\n", argc);
    // for (int i = 0; i < argc; i++){
    //     printf("%s\n", argv[i]);
    // }
    // printf("\n");

    if(argv[0] != NULL && argc < MAX_ARGS)
        continuar = shell_command(argv[0], tabla,(const char **)(argv + 1), (argc - 1));
    else
        error();
    return continuar;
}
