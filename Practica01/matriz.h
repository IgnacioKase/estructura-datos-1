typedef struct {
  float *direccion;
  int capacidad_x;
  int capacidad_y;
} Matriz;

Matriz * crear_matriz(int capacidad_x, int capacidad_y){
  Matriz *matriz = malloc(sizeof(Matriz));
  matriz->direccion = malloc(sizeof(float)*x*y);
  matriz->capacidad_x = x;
  matriz->capacidad_y = y;
  return y;
}

void eliminar_matriz(Matriz * matriz){
  free(matriz->direccion);
  free(matriz);
}

void escribir_matriz(Matriz * matriz, int x, int y, float val){
  (matriz->direccion)[x][y] = val;
}

float leer_matriz(Matriz * matriz, int x, int y){
  return (matriz->direccion)[x][y];
}
