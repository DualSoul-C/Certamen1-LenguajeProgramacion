#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <string.h>
#include "Petri_net.h"

Nodo*inicio=NULL;
Lista*ini=NULL;
Lista*final=NULL;
int ver = 1;

void insertarNodo(char name[50], int token){
    Nodo* aux;
    Nodo* nuevo=(Nodo*)malloc(sizeof(Nodo));
    strcpy(nuevo->name, name);
    nuevo->siguiente=NULL;
    nuevo->adyacencia=NULL;
    nuevo->visitado=nuevo->terminado=0;
    nuevo->token=token;
    nuevo->anterior=0;
    if(inicio==NULL){
        inicio=nuevo;
    }else{
        aux=inicio;
        while(aux->siguiente!=NULL){
            aux=aux->siguiente;
        }
        aux->siguiente=nuevo;
      }
 
 }
 
void insertarArista(char name1[50],char name2[50],int peso){   
    Arista* nuevo=(Arista*)malloc(sizeof(Arista));
    nuevo->siguiente=NULL;
    Nodo* aux;
    Nodo* aux2;
    if(inicio==NULL){
         printf("Error: El grafo está vacio\n");
         return;
    }
    if(peso==0){
    	nuevo->peso=1;
    }
    else{
    	nuevo->peso=peso;
    }
    aux=inicio;
    aux2=inicio;
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
    while(aux!=NULL){
        if(strcmp(aux->name,name1)==0){
            if((aux->token>-1 && aux2->token==-1) || (aux->token==-1 && aux2->token>-1)){
            	agregarArista(aux,aux2,nuevo);
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
    if(aux->adyacencia==NULL){   
	    aux->adyacencia=nuevo;
        nuevo->vrt=aux2;
    }else{   
	    a=aux->adyacencia;
        while(a->siguiente!=NULL)
            a=a->siguiente;
        nuevo->vrt=aux2;
        a->siguiente=nuevo;
    }
}

void visualizarGrafo(){
    Nodo*aux=inicio;
    Arista* ar;
    printf("Nodos\n");
    while(aux!=NULL){   
	    printf("%s/%d:    ",aux->name,aux->token);
        if(aux->adyacencia!=NULL){
            ar=aux->adyacencia;
            while(ar!=NULL){ 
			    printf(" %s/%d",ar->vrt->name,ar->peso);
                ar=ar->siguiente;
            }
        }
        printf("\n");
        aux=aux->siguiente;
    }
    printf("\n");
}

void recorrido(char name1[50], char name2[50]){
     Nodo*aux=inicio,*aux2=inicio;
     if(inicio!=NULL){
         while(aux!=NULL){
  	    if(strcmp(aux->name,name1)==0)
  		break;
	    aux=aux->siguiente;
         }
         while(aux2!=NULL){
  	    if(strcmp(aux2->name,name2)==0)
  		break;
	    aux2=aux2->siguiente;
         }
         if(aux==NULL && aux2==NULL){
     	 	printf("Error: Place no encontrado\n");
	 }
	 else if((aux->token==-1) || (aux2->token==-1)){
	 	printf("Error: Union valida para place/place\n");
	 }
	 else{
		aux->visitado=1;
		insertarCola(aux);
		recorridoAnchura(name2);
		if(ver==0){
			printf("Estan unidos Topologicamente");
			ver=1;
		}else{
			printf("No estan unidos Topologicamente");
		}
		reiniciar();
		printf("\n");
	 }
     }
}

void recorridoAnchura(char name[50]){
	Nodo*aux=desencolar();
	if(aux==NULL)
	return;
	if(aux->adyacencia!=NULL){
		Arista*a=aux->adyacencia;
		while(a!=NULL){
			if(a->vrt->visitado==0){
			    if(strcmp(a->vrt->name,name)==0){
			    	ver = 0;
			    }
			    insertarCola(a->vrt);
			    a->vrt->visitado=1;	
			}
			a=a->siguiente;
		}
	}
	recorridoAnchura(name);
}

void insertarCola(Nodo*aux){
	Lista*nuevo=(Lista*)malloc(sizeof(Lista));
	nuevo->dato=aux;
	nuevo->siguiente=NULL;
	if(ini==NULL){
		ini=nuevo;
		final=nuevo;
	}else{
		final->siguiente=nuevo;
		final=nuevo;
	}
}

Nodo*desencolar(){
	Lista*aux;
	if(ini==NULL){
		return NULL;
	}else{
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

void reiniciar(){
	if(inicio!=NULL){
		Nodo*aux=inicio;
		while(aux!=NULL){
			aux->visitado=aux->terminado=0;
		    aux=aux->siguiente;
		}
	}
}

void petri1(int k){
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

void petri2(int k){
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
