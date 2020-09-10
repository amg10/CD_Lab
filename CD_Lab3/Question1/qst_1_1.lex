%{
	#include<stdio.h>
%}

%%
(1|0(1)*0)* {printf("Even zeros!! Accepted!!");}
.* {printf("Odd zeros!! Not Accepted!!");}
%%

int yywrap(void){return 1;}
int main()
{
	yylex();
	return 1;
}