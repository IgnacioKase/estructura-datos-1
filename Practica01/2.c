#include <stdio.h>
#include <stdlib.h>

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
  int found = string_subcadena(a, "pr");
  printf("Cadena encontrada: %d\n", found);
  found = string_subcadena(a, "kjh");
  printf("Cadena no encontrada: %d\n", found);
  char *arreglo[] = {"123", "4", "56", "78"};
  char *res = malloc(10000);
  string_unir(arreglo, 4, "-", res);
  printf("Cadena unida: %s\n", res);
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
  int i = 0, j;
  int len_str2 = string_len(str2);
  while ( str1[i] != '\0') {
    j = 0;
    while ( str1[i+j] == str2[j] && str2[j] != '\0') j++;
    if ( len_str2 == j )
      return i;
    i++;
  }
  return -1;
}

void string_unir(char* arregloStrings[], int capacidad, char* sep, char* res) {
  int totalLength = 0, i;
  int lenSep = string_len(sep);
  for ( i = 0; i < capacidad; i++ )
    totalLength = totalLength + string_len(arregloStrings[i]);
  if( lenSep != 0 )
    totalLength = totalLength + capacidad * lenSep; // deberiamos restar uno pero lo usaremos para el caracter \0
  else
    totalLength++;
  char *temp = realloc(res, totalLength);
  if(temp != res)
    return;
  for(i = 0; i < totalLength; i++)
    temp[i] = 0;
  temp[0] = '\0';
  //printf("%d\t%p\t%s\t%s\t%d\n", totalLength, temp, temp, sep, lenSep);
  for ( i = 0; i < capacidad; i++ ) {
    string_concat(temp, arregloStrings[i], string_len(arregloStrings[i]));
    //printf("%d\t%p\t%s\n", totalLength, temp, temp);
    if ( lenSep != 0 && i != capacidad - 1)
      string_concat(temp, sep, lenSep);
  }
  temp[totalLength] = '\0';
}


 
	
