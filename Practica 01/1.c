#include <stdio.h>
#include <stdlib.h>

void bubble_sort(float arreglo[],int longitud);
float mediana(float *arreglo, int longitud);
 
int main(){
  float a[] = {1,2};
  int n = 2, i = 0;
  float result = mediana(a,n);
  printf("%.2f\n", result);
  for(i = 0; i < n; i++)
    printf("%.2f\t", a[i]);
  printf("\n");
  return 0;
}

void bubble_sort(float arreglo[], int longitud) { for (int iter = 0 ; iter < longitud - 1 ; iter++) { for (int i = 0 ; i < longitud - iter - 1; i++) { if (arreglo[i] > arreglo[i + 1]) { float aux = arreglo[i]; arreglo[i] = arreglo[i + 1]; arreglo[i + 1] = aux; } } } }
 
float mediana(float *arreglo, int longitud){
  if(longitud == 0) return 0;
  if(longitud == 1) return arreglo[0];
  int mid = longitud / 2, i = 0;
  float *bck = malloc(sizeof(int)*longitud);
  for(i = 0; i < longitud; i++)
    bck[i] = arreglo[i];
  bubble_sort(bck, longitud);
  return longitud % 2 != 0 ? (float)bck[mid] : (float)(bck[mid]+bck[mid-1]) / 2; 
}
