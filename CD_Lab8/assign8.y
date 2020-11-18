%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int yylex();
void yyerror(char * s);

%}

%token DIGIT
%start exp

%left '+' '-'
%left '*' '/' '%'
%left '(' ')'

%%
exp : E {printf("\nEvaluated Value=%d\n",$$);return 0;}
E : E '+' T {$$ = $1 + $3;}
  | E '-' T {$$ = $1 - $3;} 
  | T {$$ = $1;}
  ;
T : T '*' F {$$ = $1 * $3;}
  | T '/' F {$$ = $1 / $3;}
  | T '%' F {$$ = $1 % $3;}
  | F {$$ = $1;}
  ;
F : '(' E ')' {$$ = $2;}
  | DIGIT
  ;
  
%%
extern int yylex();
extern int yyparse();

void yyerror(char *s){
	printf("Invalid Expression!!\n");
	exit(-1);
}
int main()
{
	return(yyparse());
}