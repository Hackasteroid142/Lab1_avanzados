#include<stdio.h>
#include<stdlib.h>
#include<string.h>


/*
	Estructura de la lista enlazada donde se tiene dos array, uno para el camino encontrado y otro para el mejor
	camino que de todos los encontrados.
*/
struct Caminos
{	
	struct Caminos* inicio;
	struct Caminos* final;
	struct Caminos* siguiente;
	int camino[100];
	int mejor[100];
};
typedef struct Caminos caminos;

/*
	Crea la estructura camino.
*/
caminos* crearCamino(){
	caminos* aux = (caminos*)malloc(sizeof(caminos));
	aux->inicio = NULL;
	aux->final = NULL;
	aux->siguiente = NULL;
}

/*
	Entrada: lista de caminos posibles y nuevo camino encontrado.
	Proceso: Ingresa al final de la lista enlazada el nuevo camino encontrado.
	Salida: Lista con nuevo camino encontrado.
*/
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
	Entrada: matriz de adyacencia, camino y cantidad de vertices.
	Proceso: Calcula el costo del camino ingresado.
	Salida: Costo del camino.
*/
int calcularCosto(int** matriz,int camino[],int cantidadVertices){
	int costo = 0;
	for(int i=0;i<cantidadVertices-1;i++){
		costo = costo + matriz[camino[i]-1][camino[i+1]-1];
	}
	return costo;
}

/*
	Entrada: lista de los caminos posibles, cantidad de vertices y matriz de adyacencia.
	Proceso: Muestra la informacion de los caminos.
*/
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

/*
	Entrada: Tamaño de la matriz.
	Proceso: Crea una matriz de 0.
	Salida: Matriz.
*/
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

/*
	Entrada: Matriz de adyacencia, caminos posibles encontrados y la cantidad de vertices utilizada.
	Proceso: Calcula el costo de cada camino segun la matriz y deja el camino de menor costo. 
	Salida: Costo del menor camino.
*/
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

/*
	Entrada: vertice inicial, contador, total de vertices, lista vacia, lista vacia que indica los vertices visitados, 
	lista de adyacencia donde se guarda la informacion de los caminos.
	Proceso: A partir de un nodo inicial va recorriendo los nodos adyacentes, los cuales pasan a ser vertices iniciales y se repite
	el proceso hasta recorrer todos los vertices y guardar el camino.
	Salida: Los posibles caminos de un grafo.
*/
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

/*
	Entrada: cantidad de vertices, matriz de adyacencia y lista enlazada vacia.
	Proceso: Genera todos los posibles caminos de un grafo y busca el de menor costo.
	Salida: Costo del camino mas corto.
*/
int BruteForce(int cantidadVertices,int** matriz,caminos* opciones){
	int* visitados = (int*)malloc(cantidadVertices*sizeof(int));
	for(int i=1;i<cantidadVertices+1;i++){
		int nuevoCamino[cantidadVertices];
		nuevoCamino[0] = i;
		int num = 0;
		encontrarCamino(i,1,cantidadVertices,nuevoCamino,visitados,opciones);
	}
	int solucionValor = mejorCamino(matriz,opciones,cantidadVertices);
	return solucionValor;
}


/*
	Entrada: lista de string con informacion y tamaño de la lista.
	Proceso: Crea la matriz de adyacencia con la informacion del archivo.
	Salida: matriz de adyacencia del grafo.
*/
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

/*
	Entrada: archivo vacio, costo del mejor camino, lista de caminos y cantidad de vertices del grafo.
	Proceso: Escribe el archivo de salida.
	Salida: Archivo con informacion del mejor camino. 
*/
void escribirArchivo(FILE* archivo,int mejor,caminos* posibles,int cantidadVertices){
	fprintf(archivo, "%i\n",mejor);
	fprintf(archivo, "%i-",0);
	for(int i=0;i<cantidadVertices;i++){
		fprintf(archivo, "%i-",posibles->mejor[i]);
	}
	fprintf(archivo, "%i",0);
}


/*
	Entrada: nombre del archivo y lista de string vacias.
	Proceso: Recorre el archivo linea por linea y guarda la informacion de cada una en la lista de string.
	Salida: El largo de la lista de string.
*/
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