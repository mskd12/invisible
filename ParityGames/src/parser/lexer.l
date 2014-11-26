%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.hh"
char** endp;
%}
alphanum  [\)\(\,\-a-zA-Z0-9 ]
white     [ \t]+
digit     [0-9]
integer   {digit}+
iden      \"{alphanum}*\"
%%

{white} 	{ /* We ignore white characters */ }

parity    return(PARITY);

";"       return SEMI;

","       return COMMA;

{iden} { 
yylval.id = strndup(yytext+1,strlen(yytext)-2);            
return(IDEN); 
}

{integer} {
yylval.num=atoi(yytext);
return(INT);
}

