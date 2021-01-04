%{
	#include<stdio.h>
%}

%%
(0|1)*101(0|1)* {printf("Contains 101!! Accepted!!");}
.* {printf("Not Accepted!!");}
%%

int yywrap(void){return 1;}
int main()
{
	yylex();
	return 1;
}