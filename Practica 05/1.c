/*

 Al ejecutar tablehash/main.c insertando dos elementos con la misma clave 
 ocurre que se reemplaza el valor insertado con el puntero de la clave nueva
 y ademas al no encontrar el elemento buscando con la clave anterior se intenta
 convertir a (*int) el puntero NULL, por lo cual la ejecución se corta.
*/