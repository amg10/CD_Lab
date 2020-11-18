%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void yyerror(char * s);

#define YYSTYPE char
char temp= 'A'-1;

#include "y.tab.h"
#include "lex.yy.c"


%}

%token NUMBER ID
%start exp

%left '+' '-'
%left '*' '/' '%'
%left '(' ')'

%%
exp : E {printf("%c = %c\n",++temp,(char)$1);return 0;}
E : E '+' T {printf("%c = %c + %c\n",++temp,(char)$1,(char)$3);$$=temp;}
  | E '-' T {printf("%c = %c - %c\n",++temp,(char)$1,(char)$3);$$=temp;}
  | T {$$=(char)$1;}
T : T '*' F {printf("%c = %c * %c\n",++temp,(char)$1,(char)$3);$$=temp;}
  | F '/' F {printf("%c = %c / %c\n",++temp,(char)$1,(char)$3);$$=temp;}
  | T '%' F {printf("%c = %c % %c\n",++temp,(char)$1,(char)$3);$$=temp;}
  | F {$$=(char)$1;}
F : '(' E ')' {$$ =(char) $2;}
  | NUMBER {$$=(char)$1;}
  | ID {$$=(char)$1;}
  ;
  
%%

void yyerror(char *s){
	printf("Invalid Expression!!\n");
	exit(-1);
}
int main()
{
	return(yyparse());
}