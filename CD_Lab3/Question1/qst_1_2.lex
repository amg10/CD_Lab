%{
	#include<stdio.h>
%}

%%
(00|11|(01|10)(00|11)*(01|10))* {printf("Even zeros and ones!! Accepted!!");}
.* {printf("Not Accepted!!");}
%%

int yywrap(void){return 1;}
int main()
{
	yylex();
	return 1;
}