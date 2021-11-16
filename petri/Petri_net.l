%option noyywrap nodefault yylineno
%{
#include "Petri_net.h"
#include "Petri_net.tab.h"
%}

%%
"Place" {return PLACE;}
"Transicion" {return TRANS;}
"Arco" {return ARCO;}
Print {return PRINT;}
Compleja1 {return COM1;}
Compleja2 {return COM2;}
Union {return UNION;}
Trigger {return TRIGGER;}
[A-Za-z]+ { strcpy(yylval.s, yytext); return NAME; }
[0-9]+ { yylval.d = atoi(yytext); return NUMBER; }
\n {return EOL;}
"," |
"(" |
")" {return yytext[0];}
. {printf("palabra no reconocida");}
%%
