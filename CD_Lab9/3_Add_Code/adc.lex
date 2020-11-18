%{
	#include<stdio.h>
	#include<stdlib.h>
	
%}

digit [0-9]
number ({digit}+)
letter [a-z]

%%
{number} {yylval=(char)yytext[0];return NUMBER;}
{letter} {yylval=(char)yytext[0];return ID;}
[" "|"\t"] 		{}
[\n]			{return 0;}
.               {return yytext[0];}

%%
int yywrap(void){return 1;}