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
    struct elt *casilla;
    
    //2020-11-22T00:00:00-03:00,9 de Julio,POZO BORRADO,8,5,0,13
    while (fscanf(fp, "%d-%d-%dT%39[^,],%39[^,],%39[^,],%d,%d,%d,%d\n", &anio, &mes, &dia, fecha_ignorar, departamento, localidad, &confirmados, &descartados, &en_estudio, &notificaciones) != EOF) {
        fecha_nuevo = fecha_crear(dia, mes, anio);
        
        departamento_copia = malloc(sizeof(char) * strlen(departamento) + 1);
        localidad_copia = malloc(sizeof(char) * strlen(localidad) + 1);

        strcpy(departamento_copia, departamento);
        strcpy(localidad_copia, localidad);

        nuevo = registro_crear(fecha_nuevo, departamento_copia, localidad_copia, confirmados, descartados, en_estudio, notificaciones);   

        casilla = (struct elt *) tablahash_buscar(tabla, (void*) nuevo->clave);

        if(casilla != NULL) {
            lista = (List) casilla->value;
            lista = list_agregar_ordenado(lista, (void *) nuevo, registro_menor);
            casilla->value = lista;
        } else {
            lista = list_crear();
            lista = list_agregar_ordenado(lista, (void *) nuevo, registro_menor);
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
    char *clave = registro_construir_clave(argv[1], argv[2]);
    struct elt *casilla = (struct elt *) tablahash_buscar(tabla, clave);
    List lista;
    Registro busqueda = registro_crear(fecha_analizar(argv[0]), "", "", 0, 0, 0, 0);

    char *departamento = malloc((sizeof(char) * strlen(argv[1])) + 1);
    char *localidad = malloc((sizeof(char) * strlen(argv[2])) + 1);

    strcpy(departamento, argv[1]);
    strcpy(localidad, argv[2]);

    Registro nuevo = registro_crear(fecha_analizar(argv[0]), departamento, localidad, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), 0);
    nuevo->notificaciones = nuevo->confirmados + nuevo->descartados + nuevo->en_estudio;

    if(casilla != NULL) {
        lista = (List) casilla->value;
        List nodo = list_buscar(lista, busqueda, registro_igual_por_fecha);
        if(!list_vacia(nodo)) {
            Registro registro = (Registro) nodo->dato;
            printf("Se encontró un registro para esta fecha: %s, el mismo será remplazado.\nRegistro a reemplazar: ", argv[0]);
            registro_imprimir(registro);
            registro->confirmados = nuevo->confirmados;
            registro->descartados = nuevo->descartados;
            registro->en_estudio = nuevo->en_estudio;
            registro->notificaciones = nuevo->notificaciones;
            registro_destruir(nuevo);
            printf("Registro reemplazado con éxito.\nRegistro actual: ");
            registro_imprimir(registro);
        } else {
            lista = list_agregar_ordenado(lista, (void *)nuevo, registro_menor);
            casilla->value = (void *) lista;
            printf("Registro agregado con éxito.\nRegistro:");
            registro_imprimir(nuevo);    
        }
    } else {
        lista = list_crear();
        lista = list_agregar_ordenado(lista, (void *)nuevo, registro_menor);
        tablahash_insertar(tabla, (void*) nuevo->clave, (void *) lista);
        printf("Localidad registrada.\n");
        printf("Registro agregado con éxito.\nRegistro:");
        registro_imprimir(nuevo);    
    }

    registro_destruir(busqueda);
    free(clave);
}

void eliminar_registro(TablaHash tabla, const char *fecha_char, const char *departamento, const char *localidad) {
    char *clave = registro_construir_clave(departamento, localidad);
    Fecha fecha = fecha_analizar(fecha_char);
    struct elt *casilla = (struct elt *) tablahash_buscar(tabla, clave);

    Registro busqueda = registro_crear(fecha, "", "", 0, 0, 0, 0);

    if(casilla != NULL) {
        List lista = (List) casilla->value;
        List nodo = list_buscar(lista, busqueda, registro_igual_por_fecha);
        if(!list_vacia(nodo)) {
            if(nodo == lista) {
                lista = nodo->sig;
                casilla->value = (void *)lista;
            }
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

void buscar_pico(TablaHash tabla, const char *departamento, const char *localidad) {
    char *clave = registro_construir_clave(departamento, localidad);
    struct elt *casilla = (struct elt *) tablahash_buscar(tabla, clave);

    if(casilla == NULL)
        return;

    List lista = (List) casilla->value;

    if(list_vacia(lista))
        return;

    List nodo;
    Fecha fecha = ((Registro) lista->dato)->fecha;

    int max = 0, temp;

    for (nodo = lista; nodo->sig != lista; nodo = nodo->sig) {
        if(nodo->sig != NULL) {
            if(nodo->sig->dato != NULL) {
                temp = ((Registro) nodo->dato)->confirmados - ((Registro) nodo->sig->dato)->confirmados;
                if (temp > max) {
                    max = temp;
                    fecha = ((Registro) nodo->dato)->fecha;
                }
            }
        }
    }

    printf("El pico para la localidad de: %s, fue en la fecha: %02d-%02d-%02d con un total de %d\n", clave, fecha->anio, fecha->mes, fecha->dia, max);

    free(clave);
}

void casos_acumulados(TablaHash tabla, const char *fecha_char, const char *departamento, const char *localidad) {
    Fecha fecha = fecha_analizar(fecha_char);
    char *clave = registro_construir_clave(departamento, localidad);
    struct elt *casilla = (struct elt *) tablahash_buscar(tabla, clave);
    Registro busqueda = registro_crear(fecha, "", "", 0, 0, 0, 0);

    if(casilla != NULL) {
        List lista = (List) casilla->value;
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

void tiempo_duplicacion(TablaHash tabla, const char *fecha_char, const char *departamento, const char *localidad) {
    char *clave = registro_construir_clave(departamento, localidad);
    struct elt *casilla = (struct elt *) tablahash_buscar(tabla, clave);

    if(casilla == NULL)
        return;

    List lista = (List) casilla->value;

    if(list_vacia(lista))
        return;
    
    Registro busqueda = registro_crear(fecha_analizar(fecha_char), "", "", 0, 0, 0, 0);
    List nodo = list_buscar(lista, busqueda, registro_igual_por_fecha);
    registro_destruir(busqueda);
    busqueda = (Registro) nodo->dato;

    if(busqueda->confirmados == 0) {
        printf("Error, la fecha ingresada tiene 0 confirmados, no es posible buscar el tiempo de duplicación.\n");
        return;
    }

    List iterador;

    Fecha fecha_mejor_candidato = busqueda->fecha;
    Registro temp;
    int objetivo = busqueda->confirmados / 2 , mejor_candidato;

    mejor_candidato = 0;
 
    for (iterador = nodo->ant; iterador->ant != lista->ant; iterador = iterador->ant) {
        temp = (Registro) iterador->dato;
        if(temp == NULL)
            continue;
        if (temp->confirmados == 0)
            continue;
        if(abs(objetivo - temp->confirmados) < abs(objetivo - mejor_candidato)) {
            mejor_candidato = temp->confirmados;
            fecha_mejor_candidato = temp->fecha;
        }
    }

    printf("El tiempo de duplicación para la localidad de: %s y fecha: %02d-%02d-%02d, fue de %d día/s, en la fecha: %02d-%02d-%02d.\nCon un ratio (mejor_resultado / objetivo) de %.4f.\nUna diferencia absoluta con el valor objetivo de %d día/s.\n", 
            clave,
            busqueda->fecha->anio, 
            busqueda->fecha->mes, 
            busqueda->fecha->dia, 
            fecha_dias_diferencia(busqueda->fecha, fecha_mejor_candidato), 
            fecha_mejor_candidato->anio, 
            fecha_mejor_candidato->mes, 
            fecha_mejor_candidato->dia, 
            (double) mejor_candidato / (double) objetivo,
            abs(objetivo - mejor_candidato)
    );

    free(clave);
}

void graficar(TablaHash tabla, const char *fecha_inicio_char, const char *fecha_fin_char, const char *departamento, const char *localidad) {
    char *clave = registro_construir_clave(departamento, localidad);
    struct elt *casilla = (struct elt *) tablahash_buscar(tabla, clave);

    if(casilla == NULL)
        return;

    List lista = (List) casilla->value;

    if(list_vacia(lista))
        return;

    Registro busqueda_inicio = registro_crear(fecha_analizar(fecha_inicio_char), "", "", 0, 0, 0, 0);
    Registro busqueda_fin = registro_crear(fecha_analizar(fecha_fin_char), "", "", 0, 0, 0, 0);

    if(!registro_menor((void*)busqueda_inicio, (void*)busqueda_fin)) {
        printf("Intervalo de búsqueda inválido.\nLa fecha de inicio debe ser menor estricto a la fecha de fin.\n");
        return;
    }

    List iterador;
    List inicio = (List) list_buscar(lista, busqueda_inicio, registro_igual_por_fecha);
    List fin = (List) list_buscar(lista, busqueda_fin, registro_igual_por_fecha);

    if(inicio == NULL) {
        printf("No se encontró registro con la fecha de inicio indicada.\n");
        return;
    }

    if(fin == NULL) {
        printf("No se encontró registro con la fecha de inicio indicada.\n");
        return;
    }

    Fecha fecha_inicio = ((Registro)inicio->dato)->fecha;
    Fecha fecha_fin = ((Registro)fin->dato)->fecha;
    
    char *xrange = malloc(sizeof(char) * 100);
    sprintf(xrange, "set xrange [\"%02d%c%02d%c%02d\":\"%02d%c%02d%c%02d\"]",
            fecha_inicio->anio, 45, fecha_inicio->mes, 45, fecha_inicio->dia,
            fecha_fin->anio, 45, fecha_fin->mes, 45, fecha_fin->dia);

    int num_commands = 13;
    char * comandos_gnuplot[] = {
        "set title \"Gráfica casos confirmados y acumulados\"",
        "set ylabel 'Personas'",
        "set xlabel 'Día'",
        "set xdata time",
        "set timefmt '%m/%d'",
        "set format x '%m/%d",
        "set datafile sep ','",
        "set key top left autotitle columnheader",
        "set grid",
        "set autoscale",
        // "set terminal png size 720,650",
        "set terminal dumb",
        // "set output 'grafica.png'",
        "set output 'grafica.csv'",
        "plot 'confirmados.temp' using 1:2 lt rgb 'red' w l title 'Confirmados', 'acumulados.temp' using 1:2 lt rgb 'green' w l title 'Acumulados'"
    };
    FILE * archivo_confirmados = fopen("confirmados.temp", "w");
    FILE * archivo_acumulados = fopen("acumulados.temp", "w");
    FILE * gnuplot_entrada = popen("gnuplot -persistent", "w");
    Fecha fecha;
    registro_destruir(busqueda_inicio);
    registro_destruir(busqueda_fin);

    int confirmados, acumulados, acumulados_temp = 0;

    for (iterador = inicio; iterador != fin; iterador = iterador->sig) {
        acumulados = ((Registro) iterador->dato)->confirmados;
        fecha = ((Registro) iterador->dato)->fecha;
        confirmados = acumulados - acumulados_temp;
        // fprintf(archivo_confirmados, "%lf\t %lf\t \n", (double)confirmados, (double)confirmados); //Write the data to a temporary file
        fprintf(archivo_confirmados, "%02d%c%02d%c%02d,%d\n", fecha->anio, 45, fecha->mes, 45, fecha->dia, confirmados); //Write the data to a temporary file
        // fprintf(archivo_acumulados, "%lf\t %lf\t \n", (double)acumulados, (double)acumulados); //Write the data to a temporary file
        fprintf(archivo_acumulados, "%02d%c%02d%c%02d,%d\n", fecha->anio, 45, fecha->mes, 45, fecha->dia, acumulados); //Write the data to a temporary file
        // printf("Casos confirmados: %d, Casos acumulados: %d\n", confirmados, acumulados);
        acumulados_temp = acumulados;
    }
    
    fclose(archivo_confirmados);
    fclose(archivo_acumulados);

    for (int i = 0; i < num_commands; i++) {
        fprintf(gnuplot_entrada, "%s \n", comandos_gnuplot[i]);
    }
    
    free(clave);
    free(xrange);
}

// Procesamiento de los comandos que no reciben intervalo
int shell_command(const char *comando, TablaHash tabla, const char *argv[], int argc) {
    int continuar = 1;
    int has_error = 0;
    switch (match_command(comando)) {
        case CARGAR_DATASET:
            has_error = argc != 1;
            if (!has_error)
                cargar_dataset(argv[0], tabla);
            break;
        case IMPRIMIR_DATASET:
            has_error = argc != 1;
            if (!has_error)
                imprimir_dataset(argv[0], tabla);
            break;
        case AGREGAR_REGISTRO:
            has_error = argc != 6;
            if (!has_error)
                agregar_registro(argv, tabla);
            break;
        case ELIMINAR_REGISTRO:
            has_error = argc != 3;
            if (!has_error)
                eliminar_registro(tabla, argv[0], argv[1], argv[2]);
            break;
        case BUSCAR_PICO:
            has_error = argc != 2;
            if (!has_error)
                buscar_pico(tabla, argv[0], argv[1]);
            break;
        case CASOS_ACUMULADOS:
            has_error = argc != 3;
            if (!has_error)
                casos_acumulados(tabla, argv[0], argv[1], argv[2]);
            break;
        case TIEMPO_DUPLICACION:
            has_error = argc != 3;
            if (!has_error)
                tiempo_duplicacion(tabla, argv[0], argv[1], argv[2]);
            break;
        case GRAFICAR:
            has_error = argc != 4;
            if (!has_error)
                graficar(tabla, argv[0], argv[1], argv[2], argv[3]);
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
