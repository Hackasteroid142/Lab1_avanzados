#include<stdio.h>
#include"Funcion.h"
#include<string.h>

int main(){
	char** infoArchivo = (char**)malloc(1000*sizeof(char*));
	int tamano = leerArchivo("test4.txt",infoArchivo);
	int** matriz = rellenarMatriz(infoArchivo,tamano);
	int cantidadVertices = atoi(infoArchivo[0]);
	caminos* opciones = crearCamino();
	int solucionValor = BruteForce(cantidadVertices,matriz,opciones);
	FILE* nuevo = fopen("solucion","wt");
	escribirArchivo(nuevo,solucionValor,opciones,cantidadVertices);
	printCurrent(opciones,cantidadVertices,matriz);
	printf("Programa finalizado, el archivo ha sido creado.\n");
	return 0;
}