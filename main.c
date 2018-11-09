#include<stdio.h>
#include"Funcion.h"
#include<string.h>

int main(){
	char** info = (char**)malloc(1000*sizeof(char*));
	int tamano = leerArchivo("input10.txt",info);
	printf("%i\n", tamano);
	int** matrix2 = rellenarMatriz(info,tamano);
	for(int i = 0;i<4;i++){
		//printf("%i\n", matrix[i][0]);
		for (int j = 0; j < 4; j++)
		{
			printf("%i ", matrix2[i][j]);
		}
		printf("\n");
	}
	int cantidadVertices = atoi(info[0]);
	//int* num = (int*)malloc(cantidadVertices*sizeof(int));
	int* num2 = (int*)malloc(cantidadVertices*sizeof(int));
	int** prueba2 = (int**)malloc(6*sizeof(int*));
	caminos* prueba = crearCamino();
	for(int i=1;i<cantidadVertices+1;i++){
		int test[cantidadVertices];
		test[0] = i;
		int num = 0;
		encontrarCamino(i,1,cantidadVertices,test,num2,prueba);
	}
	//ImprimirCaminos(prueba);
	int solucion[4];
	int solucionValor = mejorCamino(matrix2,prueba,cantidadVertices);
	printf("%i %i %i %i\n",prueba->mejor[0],prueba->mejor[1],prueba->mejor[2],prueba->mejor[3]);
	FILE* nuevo = fopen("solucion","wt");
	escribirArchivo(nuevo,solucionValor,prueba,cantidadVertices);
	return 0;
}