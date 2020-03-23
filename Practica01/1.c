#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int string_len(char* str);
void string_reverse(char* str);
int string_concat(char* str1, char* str2, int max);
int string_compare(char* str1, char* str2);
int string_subcadena(char* str1, char* str2);
void string_unir(char* arregloStrings[], int capacidad, char* sep, char* res);
 
int main(){
  char *a = malloc(17);
  a[16] = '\0';
  char *T = "cadena de prueba";
  int i;
  for (i = 0; i < 16; i++)
    a[i] = T[i];
  int len = string_len(a);
  printf("Largo de la cadena: %d\n", len);
  string_reverse(a);
  printf("Cadena invertida: %s\n", a);
  for (i = 0; i < 16; i++)
    a[i] = T[i];
  int b = string_concat(a, " 123456", 3);
  printf("Cadena concatenada: %s\t Caracteres copiados: %d\n", a, b);
  
  a = malloc(17);
  a[16] = '\0';
  for (i = 0; i < 16; i++)
    a[i] = T[i];
  
  int result = string_compare(a, "z");
  printf("Cadena menor: %d\n", result);
  result = string_compare(a, a);
  printf("Cadena igual: %d\n", result);
  result = string_compare(a, "abcdefghijklmnopqrst1234567890");
  printf("Cadena mayor: %d\n", result);
  int found = string_subcadena(a, "cadena");
  printf("Cadena encontrada: %d\n", found)
  found = string_subcadena(a, "kjh");
  printf("Cadena no encontrada: %d\n", found)
  char *arreglo[] = {"123", "4", "56", "78"};
  char *res = malloc(sizeof(char) * 1000);
  string_unir(arreglo, 1000, '-', res);
  printf("Cadena unida: %s\n", res);*/
  return 0;
}

int string_len(char* str) {
  int i = 0;
  while (str[i] != '\0') i++;
  return i;
}

void string_reverse(char* str) {
  int len = string_len(str), i;
  char temp;
  int len_mid = len / 2;
  for (i = 0; i < len_mid; i++){
    temp = str[i];
    str[i] = str[len - i - 1];
    str[len - i - 1] = temp;
  }
}

int string_concat(char* str1, char* str2, int max) {
  char *dirBackup = str1;
  int i, len = string_len(str1);
  char backup[len];
  for ( i = 0; i < len; i++)
    backup[i] = str1[i];
  unsigned long long test =  (sizeof(char) * (max + len + 1)); 
  char *newPointer = realloc(str1, test);
  if (! newPointer){
    str1 = realloc(dirBackup, sizeof(char) * (len+1));
    for ( i = 0; i < len; i++)
      str1[i] = backup[i];
    str1[len] = '\0';
    return 0;
  }else{
    if( newPointer != dirBackup){
      for ( i = 0; i < len; i++)
        dirBackup[i] = backup[i];
      dirBackup[len] = '\0';
      return 0;
    }else{
      for ( i = len; i < len + max + 1; i++)
        str1[i] = str2[ i - len];
    }
    str1[len+max] = '\0';
  }
  return max;
}

int string_compare(char* str1, char* str2) {
  if ( str1[0] == '\0' && str2[0] == '\0')
    return 0;
  if( str1[0] != str2[0] )
    return str1[0] > str2[0] ? 1 : -1;
  return string_compare((str1 + 1), (str2 + 1));
}

int string_subcadena(char* str1, char* str2) {
  return -1;
}

void string_unir(char* arregloStrings[], int capacidad, char* sep, char* res) {
  
}


 
	
