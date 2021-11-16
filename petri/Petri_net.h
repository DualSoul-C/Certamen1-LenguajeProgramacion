extern int yylineno;

void yyerror(char *s, ...);

typedef struct Nodo Nodo;
typedef struct Arista Arista;
typedef struct Lista Lista;

struct Nodo{
	char name[50]; 
	Nodo* siguiente;
	Arista* adyacencia; 
	int visitado,terminado;
	int token;
	char anterior;
};

struct Arista{
	Nodo*vrt; 
	Arista*siguiente;
	int peso;
};

struct Lista{
	Nodo* dato;
	Lista* siguiente;
};

void insertarNodo(char name[50], int token);
void agregarArista(Nodo*aux,Nodo*aux2,Arista*nuevo);
void insertarArista(char name1[50],char name2[50],int peso);
void visualizarGrafo();
void recorrido(char name1[50], char name2[50]);
void recorridoAnchura(char name[50]);
void insertarCola(Nodo* aux);
Nodo*desencolar();
void reiniciar();
void petri1(int k);
void petri2(int k);
