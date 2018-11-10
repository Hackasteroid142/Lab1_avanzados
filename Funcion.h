#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Caminos
{	
	struct Caminos* inicio;
	struct Caminos* final;
	struct Caminos* siguiente;
	int camino[100];
	int mejor[100];
};
typedef struct Caminos caminos;


caminos* crearCamino(){
	caminos* aux = (caminos*)malloc(sizeof(caminos));
	aux->inicio = NULL;
	aux->final = NULL;
	aux->siguiente = NULL;
}

void ingresarCamino(caminos* lista,caminos* posibleCamino){
	if(lista->inicio == NULL){
		lista->inicio = posibleCamino;
		lista->final = posibleCamino;
	}
	else{
		lista->final->siguiente = posibleCamino;
		lista->final = posibleCamino;
	}
}

/*
void imprimirCamino(int camino[],int cantidadVertices){
	for(int i=0;i<cantidadVertices;i++){
		printf("%i ",camino[i] );
	}
	printf("\n");
}*/

int calcularCosto(int** matriz,int camino[],int cantidadVertices){
	int costo = 0;
	for(int i=0;i<cantidadVertices-1;i++){
		costo = costo + matriz[camino[i]-1][camino[i+1]-1];
	}
	return costo;
}


void printCurrent(caminos* lista,int cantidadVertices,int** matriz){
	#ifdef DEBUG
	caminos* aux = lista->inicio;
	while(aux!=NULL){
		for(int i=0;i<cantidadVertices;i++){
			printf("%i ",aux->camino[i] );
		}
		printf(" COSTO = %i\n",calcularCosto(matriz,aux->camino,cantidadVertices) );
		aux = aux->siguiente;
	}
	#endif
}


int** formarMatriz(int tamano){
	int** matriz = (int**)malloc(tamano*sizeof(int*));
	for(int i=0;i<tamano;i++){
		matriz[i] = (int*)malloc(tamano*sizeof(int));
		for(int j=0;j<tamano;j++ ){
			matriz[i][j] = 0;
		}
		
	}
	return matriz;
}



int mejorCamino(int** matriz,caminos* posibles,int cantidadVertices){
	caminos* aux = posibles->inicio;
	int mejor = 20000;
	while(aux != NULL){
		int costo = calcularCosto(matriz,aux->camino,cantidadVertices) + 2;
		if(costo<mejor){
			mejor = costo;
			memcpy(posibles->mejor,aux->camino,sizeof(posibles->mejor));
		}
		aux=aux->siguiente;
	}
	return mejor;
}

void encontrarCamino(int vertice,int contador,int total,int lista[],int* visitados,caminos* posibles){
	if(contador == total){
		caminos* aux = crearCamino();
		memcpy(aux->camino,lista,sizeof(aux->camino));
		ingresarCamino(posibles,aux);
	}
	else{
		visitados[vertice-1] = 1;
		for(int i=0;i<total;i++){
			if(visitados[i] != 1){
				lista[contador] = i+1;
				encontrarCamino(i+1,contador+1,total,lista,visitados,posibles);;
			}

		}
		visitados[vertice-1] = 0;
	}
}

int** rellenarMatriz(char** info,int tamano){
	int** matriz = formarMatriz(atoi(info[0]));
	for(int i=1;i<tamano;i++){
		char* strFila = strtok(info[i]," ");
		char* strColum = strtok(NULL," ");
		char* strValor = strtok(NULL," ");
		int fila = atoi(strFila)-1 ;
		int columna = atoi(strColum)-1;
		matriz[fila][columna] = atoi(strValor);
		matriz[columna][fila] = atoi(strValor);
	}
	return matriz;
}

void escribirArchivo(FILE* archivo,int mejor,caminos* posibles,int cantidadVertices){
	fprintf(archivo, "%i\n",mejor);
	fprintf(archivo, "%i-",0);
	for(int i=0;i<cantidadVertices;i++){
		fprintf(archivo, "%i-",posibles->mejor[i]);
	}
	fprintf(archivo, "%i",0);
}



int leerArchivo(char* nombre,char** info){
	FILE* arch;
	arch = fopen(nombre,"r");
	if(arch == NULL){
		printf("No se a podido leer correctamente el archivo.\n ");
		exit(1);
	}
	int i = 0;
	while(feof(arch) == 0){
		char* aux=(char*)malloc(100*sizeof(char));
		fgets(aux,100,arch);
		strtok(aux,"\n");
		info[i] = aux;
		i++;
	}
	fclose(arch);
	return i;
}