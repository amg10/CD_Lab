%{
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include "y.tab.h"
	
	#define YYSTYPE node*
%}

digit [0-9]
number ({digit}+)

%%
{number} {
		node *newnode=(node *)malloc(sizeof(node));
		newnode->isOp=0;
		newnode->left=NULL;
		newnode->right=NULL;
		newnode->value=atoi(yytext);
		yylval=newnode;
		return NUMBER;
		}
["\t"" "] {}
["\n"] return 0;
. {return yytext[0];}

%%
int yywrap(void){return 1;}