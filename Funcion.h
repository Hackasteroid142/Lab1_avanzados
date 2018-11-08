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
	//int costo;
};
typedef struct Caminos caminos;


caminos* crearCamino(){
	caminos* aux = (caminos*)malloc(sizeof(caminos));
	//aux->camino = NULL;
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

void ImprimirCaminos(caminos* lista){
	caminos* aux = lista->inicio;
	int i = 0;
	while(aux!=NULL){
		printf("%i %i %i %i %i\n",i+1,aux->camino[0],aux->camino[1],aux->camino[2],aux->camino[3]);
		aux = aux->siguiente;
		i++;
	}
	printf("\n");
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

int calcularCosto(int** matriz,int camino[],int cantidadVertices){
	int costo = 0;
	printf("CAMINO = %i %i %i %i\n",camino[0],camino[1],camino[2],camino[3]);
	for(int i=0;i<cantidadVertices-1;i++){
		printf("%i %i %i\n",camino[i]-1,camino[i+1]-1,matriz[camino[i]-1][camino[i+1]-1]);
		costo = costo + matriz[camino[i]-1][camino[i+1]-1];
	}
	return costo;
}


int mejorCamino(int** matriz,caminos* posibles){
	caminos* aux = posibles->inicio;
	//ImprimirCaminos(posibles);
	int mejor = 20000;
	//int buenCamino[4];
	while(aux != NULL){
		int costo = calcularCosto(matriz,aux->camino,4);
		printf("COSTO = %i\n",costo);
		if(costo<mejor){
			mejor = costo;
			printf("COSTO 2= %i\n",costo);
			memcpy(posibles->mejor,aux->camino,sizeof(posibles->mejor));
		}
		aux=aux->siguiente;
	}
	//printf("%i %i %i %i\n",buenCamino[0],buenCamino[1],buenCamino[2],buenCamino[3] );
	return mejor;
}

void encontrarCamino(int vertice,int contador,int total,int lista[],int* visitados,caminos* posibles){
	printf("/------------------------------------------------------/\n");
	printf("VERTICE = %i\n",vertice );
	printf("CONTADOR = %i\n",contador);
	if(contador == total){
		lista[contador-1] = vertice;
		caminos* aux = crearCamino();
		memcpy(aux->camino,lista,sizeof(aux->camino));
		ingresarCamino(posibles,aux);
		//printf("%i %i %i %i %i %i\n",lista[0],lista[1],lista[2],lista[3],lista[4],lista[5]);
		printf("TERMINE\n");
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
		printf("ENTRE CON = %i\n",i );
		char* strFila = strtok(info[i]," ");
		char* strColum = strtok(NULL," ");
		char* strValor = strtok(NULL," ");
		int fila = atoi(strFila)-1 ;
		int columna = atoi(strColum)-1;
		printf("%s %s\n",strFila,strColum);
		matriz[fila][columna] = atoi(strValor);
		matriz[columna][fila] = atoi(strValor);
	}
	return matriz;
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