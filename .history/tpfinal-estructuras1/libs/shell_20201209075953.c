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
    FILE *fp;

    printf("%s\n", archivo);

    assert((fp = fopen("db/query.csv", "r, ccs=UTF-8")));

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
        // registro_imprimir(nuevo);
    }

    struct elt *e;

    for(int i = 0; i < tabla->size; i++) {
        for(e = tabla->table[i]; e != 0; e = e->next) {
            list_recorrer((List)e->value, registro_imprimir, LIST_RECORRIDO_HACIA_ADELANTE);
        }
    }


    fclose(fp);
}

void imprimir_dataset(const char *archivo) {
    printf("%s", archivo);
}

void agregar_registro(const char *argv[6]) {
    printf("%s", argv[0]);
}

void eliminar_registro(TablaHash tabla, const char *fecha_char, const char *departamento, const char *localidad) {
    char *clave = registro_construir_clave(departamento, localidad);
    Fecha fecha = fecha_analizar(fecha_char);
    List lista = (List) tablahash_buscar(tabla, clave);
    
    List nodo;
    Registro registro_nodo;
    int encontrado = 0;

    for (nodo = lista; nodo->sig != lista && !encontrado; nodo = nodo->sig) {
        registro_nodo = (Registro) nodo->dato;
        encontrado = fecha_es_igual(fecha, registro_nodo->fecha);
    }

    if(!encontrado) {
        registro_nodo = (Registro) nodo->dato;
        encontrado = fecha_es_igual(fecha, registro_nodo->fecha);
    }

    if(encontrado) {
        nodo->sig = NULL;
        nodo->ant = NULL;
        list_destruir(nodo, registro_destruir_void);
    }

    fecha_destruir(fecha);
    free(clave);
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
                imprimir_dataset(args[0]);
            break;
        case AGREGAR_REGISTRO:
            has_error = argc != 6;
            if (!has_error)
                agregar_registro(args);
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

int analizar_argumentos(char *s, const char *argv[MAX_ARGS]) {
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
                *s = ' ';
            }
            break;
        case '\"': // Inside a quote
            if (*s == '\"') {
                estado = 'T';
            }
            break;
        }
    s++;
  }
  argc++;
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
    const char *argv[MAX_ARGS];
    // int argc = 0;

    // while(token != NULL && argc < MAX_ARGS) {
    //     argv[argc] = token;
    //     argc++;
    //     printf("%s", token);
    //     token = strtok(NULL, "\" ");
    // }

    int argc = analizar_argumentos(buf, argv);

    printf("argc: %d\n", argc);
    for (int i = 0; i < argc; i++){
        printf("%s\n", argv[i]);
    }
    printf("\n");

    if(argv[0] != NULL && argc < MAX_ARGS)
        continuar = shell_command(argv[0], tabla,(argv + 1), (argc - 1));
    else
        error();
    return continuar;
}
