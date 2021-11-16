%{
#include <stdio.h>
#include <stdlib.h>
#include "Petri_net.h"
%}

%union{
  struct nodo *n;
  struct arco *a;
  int d;
  char s[50];
}

%token PLACE
%token TRANS
%token ARCO
%token COM1
%token COM2
%token UNION
%token PRINT
%token TRIGGER
%token <d> NUMBER
%token <s> NAME
%token EOL

%type <a> arco
%type <n> nodo
%%

input:
 | input nodo EOL {printf(">  ");}
 | input arco EOL {printf(">  ");}
 | input func EOL {printf(">  ");}
 | input EOL {printf(">  ");}
 ; 
nodo:PLACE'('NAME','NUMBER')' {insertarNodo($3,$5);}
 | TRANS'('NAME')' {insertarNodo($3,-1);}
 ;
arco: ARCO'('NAME','NAME','NUMBER')'  {insertarArista($3,$5,$7);}
 ;
func: COM1'('NUMBER')' {petri1($3);}
 | COM2'('NUMBER')' {petri2($3);}
 | TRIGGER'('NAME','NAME')' {trigger($3,$5);}
 | PRINT {visualizarGrafo();}
 | UNION'('NAME','NAME')'{recorrido($3,$5);} 
 ;

%%
