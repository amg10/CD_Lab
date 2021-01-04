%{
	#include<stdio.h>
%}
digit [0-9]
intg ([+-]?{digit}+)
floatp ([+-]?{digit}+(\.{digit}+)(E[+-]?{digit}+)?)

%%
{intg} {printf("Its an integer!!");}
{floatp} {printf("Its floating number!!");}
.* {printf("Invalid input!! Retry again!!");}
%%

int yywrap(void){return 1;}
int main()
{
	yylex();
	return 1;
}