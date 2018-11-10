#include<stdio.h>
#include"Funcion.h"
#include<string.h>

int main(){
	char** info = (char**)malloc(1000*sizeof(char*));
	int tamano = leerArchivo("test4.txt",info);
	printf("%i\n", tamano);
	int** matrix2 = rellenarMatriz(info,tamano);
	int cantidadVertices = atoi(info[0]);
	int* num2 = (int*)malloc(cantidadVertices*sizeof(int));
	int** prueba2 = (int**)malloc(6*sizeof(int*));
	caminos* prueba = crearCamino();
	for(int i=1;i<cantidadVertices+1;i++){
		int test[cantidadVertices];
		test[0] = i;
		int num = 0;
		encontrarCamino(i,1,cantidadVertices,test,num2,prueba);
	}
	int solucionValor = mejorCamino(matrix2,prueba,cantidadVertices);
	FILE* nuevo = fopen("solucion","wt");
	escribirArchivo(nuevo,solucionValor,prueba,cantidadVertices);
	return 0;
}