%{
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
%}

%option yylineno
letter [A-Za-z]
digit [0-9]
l_or_d ({letter}|{digit})
id ({letter}{l_or_d}*)
int_const [+-]?{digit}+
float_const ([+-]?{digit}+(\.{digit}+)(E[+-]?{digit}+)?)

%%

"and" {return AND;}
":=" {return ASSIGN;}
":" {return COLON;}
"," {return COMMA;}
"def" {return DEF;}
"/" {return DIV;}
"." {return DOT;}
"else" {return ELSE;}
"end" {return END;}
"=" {return EQ;}
"exit" {return EXITLOOP;}
"float" {return FLOAT;}
"%d"|"%s"|"%f" {return FORMAT;}
"from" {return FROM;}
"fun" {return FUN;}
">=" {return GE;}
"global" {return GLOBAL;}
">" {return GT;}
"if" {return IF;}
"int" {return INT;}
"(" {return LEFT_PAREN;}
"[" {return LEFT_SQ_BKT;}
"<=" {return LE;}
"<" {return LT;}
"-" {return MINUS;}
"mod" {return MOD;}
"*" {return MULT;}
"<>" {return NE;}
"not" {return NOT;}
"null" {return NUL;}
"or" {return OR;}
"+" {return PLUS;}
"print" {return PRINT;}
"product" {return PRODUCT;}
"read" {return READ;}
"return" {return RETURN;}
"->" {return RETURNS;}
")" {return RIGHT_PAREN;}
"]" {return RIGHT_SQ_BKT;}
";" {return SEMICOLON;}
"skip" {return SKIP;}
"step" {return STEP;}
"to" {return TO;}
"while" {return WHILE;}
{id} {strcpy(yylval.val, yytext);return ID;}
{int_const} {strcpy(yylval.val, yytext);return INT_CONST;}
{float_const} {strcpy(yylval.val, yytext);return FLOAT_CONST;}
\".*\" {return STRING;}
[/][/].*["\n"] {}
[" ""\n""\t"] {}

%%
int yywrap(void){return 1;}