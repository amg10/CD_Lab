%{
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include "y.tab.h"
	extern int yylval;
%}

%option yylineno
digit [0-9]
number ({digit}+)

%%
{number} {yylval=atoi(yytext); return DIGIT;}
[" ""\n""\t"] {}
. {return yytext[0];}

%%
int yywrap(void){return 1;}