#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <string.h>
#include "Petri_net.h"

Nodo*inicio=NULL; //PN vacia
Lista*ini=NULL; //incia de la cola
Lista*final=NULL; //final de la cola
int ver = 1; // variable para comprobar union topoligica

void insertarNodo(char name[50], int token){//constructor del Place y Transicion de la PN
    Nodo* aux;
    Nodo* nuevo=(Nodo*)malloc(sizeof(Nodo));
    strcpy(nuevo->name, name);
    nuevo->siguiente=NULL;
    nuevo->adyacencia=NULL;
    nuevo->visitado=nuevo->terminado=0;
    nuevo->token=token;
    nuevo->anterior=0;
    if(inicio==NULL){ // si esta  vacio el PN
        inicio=nuevo;
    }else{// si al menos tiene un Place o Transicion
        aux=inicio;
        while(aux->siguiente!=NULL){
            aux=aux->siguiente;
        }
        aux->siguiente=nuevo;
      }
 
 }
 
void insertarArista(char name1[50],char name2[50],int peso){//constructor de Arcos de la PN
    Arista* nuevo=(Arista*)malloc(sizeof(Arista));
    nuevo->siguiente=NULL;
    Nodo* aux;
    Nodo* aux2;
    if(inicio==NULL){// si esta  vacio el PN
         printf("Error: El PN está vacio\n");
         return;
    }
    if(peso==0){//peso de una arista no puede ser 0
    	nuevo->peso=1;
    }
    else{
    	nuevo->peso=peso;
    }
    aux=inicio;
    aux2=inicio;
    //comprobacion de los nombres de los Places y Transicion(segundo parametro)
    while(aux2!=NULL){
        if(strcmp(aux2->name,name2)==0){
            break;
        }
        aux2=aux2->siguiente;
    }
    if(aux2==NULL){
    	printf("Error:Vertice no encontrado\n");
    	return;
	}
    //comprobacion de los nombres de los Places y Transicion(primer parametro)
    while(aux!=NULL){
        if(strcmp(aux->name,name1)==0){
            if((aux->token>-1 && aux2->token==-1) || (aux->token==-1 && aux2->token>-1)){//Comprobar que se de place/transicion o transicion/place
            	agregarArista(aux,aux2,nuevo); //asignar atributos a al place, transicion y arco
            	return;
            }
	    else{
	    	printf("solo se puede hacer un arco a un place/transicion o transicion/place\n");
            	return;    
	    }

        }
        aux = aux->siguiente;
    }
    if(aux==NULL)
    	printf("Error:Vertice no encontrado\n");
}

void agregarArista(Nodo* aux,Nodo* aux2,Arista* nuevo){
    Arista* a;
    if(aux->adyacencia==NULL){//si el place o transicion no tiene una adyacencia
	aux->adyacencia=nuevo;
        nuevo->vrt=aux2;
    }else{//si el place o transicion tiene una o más adyacencia
	a=aux->adyacencia;
        while(a->siguiente!=NULL)
            a=a->siguiente;
        nuevo->vrt=aux2;
        a->siguiente=nuevo;
    }
}

void visualizarGrafo(){//visualizacion del grafo
    Nodo*aux=inicio;
    Arista* ar;
    printf("Nodos\n");
    while(aux!=NULL){//recorrer todos los place y transicion
	    printf("%s/%d:    ",aux->name,aux->token);
        if(aux->adyacencia!=NULL){//si no existe adyacencia
            ar=aux->adyacencia;
            while(ar!=NULL){ //recorre los place y transicion adyacentes
			    printf(" %s/%d",ar->vrt->name,ar->peso);
                ar=ar->siguiente;
            }
        }
        printf("\n");
        aux=aux->siguiente;
    }
    printf("\n");
}

void recorrido(char name1[50], char name2[50]){//comprobacion de union topologica de places
     Nodo*aux=inicio,*aux2=inicio;
     if(inicio!=NULL){//si no esta vacia la PN
         while(aux!=NULL){//comprobacion de los nombres de los Places 
  	    if(strcmp(aux->name,name1)==0)
  		break;
	    aux=aux->siguiente;
         }
         while(aux2!=NULL){//comprobacion de los nombres de los Places
  	    if(strcmp(aux2->name,name2)==0)
  		break;
	    aux2=aux2->siguiente;
         }
         if(aux==NULL && aux2==NULL){//
     	 	printf("Error: Place no encontrado\n");
	 }
	 else if((aux->token==-1) || (aux2->token==-1)){//comprobacion de que no son transicion
	 	printf("Error: Union valida para place/place\n");
	 }
	 else{
		aux->visitado=1;
		insertarCola(aux);//agrega a cola
		recorridoAnchura(name2);//recorre el PN
		if(ver==0){
			printf("Estan unidos Topologicamente");
			ver=1;
		}else{
			printf("No estan unidos Topologicamente");
		}
		reiniciar();//reinicia el atributo visitado de los place y transicion
		printf("\n");
	 }
     }
}

void recorridoAnchura(char name[50]){
	Nodo*aux=desencolar();//el primer elemento de la cola
	if(aux==NULL)//no hay elementos en la cola
	return;
	if(aux->adyacencia!=NULL){//el place o transicion tienen adyacencia
		Arista*a=aux->adyacencia;
		while(a!=NULL){//recorre la adyacencia
			if(a->vrt->visitado==0){//comprueba si el place o transicion fue visitado
			    if(strcmp(a->vrt->name,name)==0){//comprueba que esta unido topologicamente
			    	ver = 0;
			    }
			    insertarCola(a->vrt);//inserta en la cola
			    a->vrt->visitado=1;	
			}
			a=a->siguiente;
		}
	}
	recorridoAnchura(name);//si viendo los elementos de la cola
}

void insertarCola(Nodo*aux){//inserta transiciones o place en la cola
	Lista*nuevo=(Lista*)malloc(sizeof(Lista));
	nuevo->dato=aux;
	nuevo->siguiente=NULL;
	if(ini==NULL){//si la cola esta vacia
		ini=nuevo;
		final=nuevo;
	}else{//si hay algo en la cola
		final->siguiente=nuevo;
		final=nuevo;
	}
}

Nodo*desencolar(){//entrega un place o transicion ademas de quitar un elemento de la cola
	Lista*aux;
	if(ini==NULL){//si esta vacia
		return NULL;
	}else{//si hay algo en la cola, entrega el primer elemento
		aux=ini;
		ini=ini->siguiente;
		aux->siguiente=NULL;
		if(ini==NULL)
		final=NULL;
	}
	Nodo*resultado=aux->dato;
	free(aux);
	return resultado;
}

void reiniciar(){//reinicia el valor visitado de los place y transiciones
	if(inicio!=NULL){//si no esta vacia
		Nodo*aux=inicio;
		while(aux!=NULL){//recorre los places y transiciones
			aux->visitado=aux->terminado=0;
		    aux=aux->siguiente;
		}
	}
}

void petri1(int k){//creaciones de la representacion del problema lectores/escritores
	insertarNodo("p", k);
	insertarNodo("t",-1);
	insertarNodo("tt",-1);
	insertarNodo("pp", 0);
	insertarNodo("ppp", k);
	insertarNodo("pppp", 0);
	insertarNodo("ttt",-1);
	insertarNodo("tttt",-1);
	insertarArista("p","t",1);
	insertarArista("p","tt",1);
	insertarArista("t","pp",1);
	insertarArista("pp","ttt",1);
	insertarArista("ttt","p",1);
	insertarArista("ttt","ppp",1);
	insertarArista("ppp","t",1);
	insertarArista("tt","pppp",1);
	insertarArista("pppp","tttt",1);
	insertarArista("tttt","p",1);
	insertarArista("tttt","ppp",k);
	insertarArista("ppp","tt",k);
	visualizarGrafo();
}

void petri2(int k){//creaciones de la representacion del problema exclusion mutua
	char place[50]= "p";
	char trans[50]= "t";
	insertarNodo("A",1);
	insertarNodo("B",0);
	insertarNodo("C",-1);
	insertarArista("B","C",1);
	insertarArista("C","A",1);
	for(int i=0; k>i; i++){
		insertarNodo(trans,-1);
		insertarNodo(place,0);
		insertarArista("A",trans,1);
		insertarArista(trans,place,1);
		strcat(trans,"t");
		insertarNodo(trans,-1);
		insertarArista(place,trans,1);
		insertarArista(trans,"B",1);
		strcat(trans,"t");
		strcat(place,"p");
	}
	visualizarGrafo();
}
void yyerror(char *s, ...){
  va_list ap; va_start(ap, s);
  fprintf(stderr, "%d: error: ", yylineno);
  vfprintf(stderr, s, ap);
  fprintf(stderr, "\n");
}

int main(){
  printf(">  ");
  return yyparse();
}
