/************************ STRING UTILITIES ****************************/

#include "string_utilities.h"

/*
    Toma una string(array de char) y elimina
    los caracteres: en @seps o los siguientes si
    seps es NULL:
    \t\n\v\f\r (incluido espacios en blancos)
    del lado izquierdo de la string
*/
void ltrim(char *str, const char *seps) {
  size_t totrim;
  if (seps == NULL) {
    seps = "\t\n\v\f\r ";
  }
  totrim = strspn(str, seps);
  if (totrim > 0) {
    size_t len = strlen(str);
    if (totrim == len) {
      str[0] = '\0';
    } else {
      memmove(str, str + totrim, len + 1 - totrim);
    }
  }
}

/*
    Versión wchar_t de ltrim
*/
void wltrim(wchar_t *str, const wchar_t *seps) {
  size_t totrim;
  if (seps == NULL) {
    seps = L"\t\n\v\f\r ";
  }
  totrim = wcsspn(str, seps);
  if (totrim > 0) {
    size_t len = wcslen(str);
    if (totrim == len) {
      str[0] = L'\0';
    } else {
      wmemmove(str, str + totrim, len + 1 - totrim);
    }
  }
}

/*
    Toma una string(array de char) y elimina
    los caracteres: en @seps o los siguientes si
    seps es NULL:
    \t\n\v\f\r (incluido espacios en blancos)
    del lado derecho de la string
*/
void rtrim(char *str, const char *seps) {
  int i;
  if (seps == NULL) {
    seps = "\t\n\v\f\r ";
  }
  i = strlen(str) - 1;
  while (i >= 0 && strchr(seps, str[i]) != NULL) {
    str[i] = '\0';
    i--;
  }
}

/*
    Versión wchar_t de rtrim
*/
void wrtrim(wchar_t *str, const wchar_t *seps) {
  int i;
  if (seps == NULL) {
    seps = L"\t\n\v\f\r ";
  }
  i = wcslen(str) - 1;
  while (i >= 0 && wcschr(seps, str[i]) != NULL) {
    str[i] = L'\0';
    i--;
  }
}

/*
    Toma una string(array de char) y elimina
    los caracteres: en @seps o los siguientes si
    seps es NULL:
    \t\n\v\f\r (incluido espacios en blancos)
    del lado derecho e izquierdo de la string
*/
void trim(char *str, const char *seps) {
  rtrim(str, seps);
  ltrim(str, seps);
}

/*
    Versión wchar_t de trim
*/
void wtrim(wchar_t *str, const wchar_t *seps) {
  wrtrim(str, seps);
  wltrim(str, seps);
}

/*
    Toma una string(array de char) y elimina
    todos los caracteres hasta la primer coma
    encontrada (de izquierda a derecha) con
    coma incluida, o toda la string en caso de
    no tener una coma
*/
void chop(wchar_t *str) {
  int i = 0;
  int len = wcslen(str);
  while (str[i] != ',' && i < len)
    i++;
  wmemmove(str, str + i + 1, len - i + 1);
}

/*
    Toma una string(array de char) y devuelve
    una substring hasta la primer coma encontrada
    (o toda la string en caso de no tener una)
    y además elimina esta substring (con la coma)
    de la string @str
*/
wchar_t *strChunk(wchar_t *str) {
  int i, n = 0;
  int len = wcslen(str);
  while (str[n] != ',' && n < len)
    n++;
  wchar_t *output = (wchar_t *) malloc(sizeof(wchar_t) * (n + 1));
  for (i = 0; i < n; i++)
    output[i] = str[i];
  output[n] = '\0';
  chop(str);
  return output;
}

/*
    Función auxiliar para encontrar el caracter correspondiente
    para sacar las tildes en la comparación.
    - Toma el caracter a buscar, el arreglo de caracteres donde buscar
    y el tamaño del mismo.
    - Devuelve la posicion del caracter a buscar si esta en el array,
    de lo contrario devuelve -1.
*/
int buscar(int n, float arr[], int tam) {
  for (int i = 0; i < tam; i++) {
    if ((int) n == (int) arr[i])
      return i;
  }
  return -1;
}

/*
    Función auxiliar para sacar las tildes en la comparación.
    - Toma el codigo del caracter en float
    - Devuelve el nuevo codigo sin tilde en float
*/
float reemplazo_ascii(float codigo) {
  if (codigo < 128.0)
    return codigo;

  float esp[14] =
      { 241, 209, 225, 193, 233, 201, 237, 205, 243, 211, 252, 250, 220, 218 };
  //            {ñ, Ñ, á, Á, é, É, í, Í, ó, Ó, ü, ú, Ü, Ú}
  float reem[14] =
      { 110.5, 78.5, 97.5, 65.5, 101.5, 69.5, 111.5, 79.5, 117.5, 117.6, 85.5,
    85.6
  };
  //             {n, N, a, A, e, E, i, I, o, O, u, u, U, U}

  int indice = buscar(codigo, esp, 14);
  if (indice == -1)
    return codigo;
  return reem[indice];
}

/*
    Toma dos strings de tipo wchar_t y
    las compara (@str1 y @str2).
    Devuelve 1 si @str1 es menor a @str2,
    caso contrario devuelve 0.
*/
int string_compare(wchar_t *str1, wchar_t *str2) {
  if (str1[0] == '\0' && str2[0] == '\0')
    return 0;
  float str1_primero = reemplazo_ascii((float) str1[0]);
  float str2_primero = reemplazo_ascii((float) str2[0]);
  if (str1_primero != str2_primero)
    return str1_primero < str2_primero ? 1 : 0;
  return string_compare((str1 + 1), (str2 + 1));
}
