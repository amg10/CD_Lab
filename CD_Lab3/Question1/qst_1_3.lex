%{
	#include<stdio.h>
%}

%%
(0|1(0(1)*0)*1)* {printf("Divisible by 3");}
.* {printf("Not divisible by 3");}
%%

int yywrap(void){return 1;}
int main()
{
	yylex();
	return 1;
}