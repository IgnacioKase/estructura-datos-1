#include <stdio.h>
#include <stdlib.h>

int string_len(char* str) {
  if(!str)
    return 0;
  int i = 0;
  while (str[i] != '\0') i++;
  return i;
}

void f(char *str){
  printf("String: %s, Address: %p, Length: %d\n", str, str, string_len(str));
  str = realloc(str, 4);
  str[0] = 'a';
  str[1] = 'b';
  str[2] = 'c';
  str[3] = 0;
  printf("String: %s, Address: %p, Length: %d\n", str, str, string_len(str));
  return;
}

int main(){
  char *str = 0;
  //printf("String: %p, Length: %d\n", str, string_len(str));
  f(str);
  printf("String: %s, Address: %p, Length: %d\n", str, str, string_len(str));
}
