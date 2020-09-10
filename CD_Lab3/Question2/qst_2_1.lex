%{
	#define ERROR -1
	#define IF 1
	#define THEN 2
	#define ELSE 3
	#define ID 4
	#define NUMBER 5
	#define RELOP 6
	int lines=1;
%}
whitespace [ \t]
letter [A-Za-z]
digit [0-9]
number ({digit}+(\.{digit}+)?(E[+-]?{digit}+)?)
l_or_d ({letter}|{digit})
identifier ({letter}{l_or_d}*)

%%
if {printf("IF");return(IF);}
then {printf("THEN");return(THEN);}
else {printf("ELSE");return(ELSE);}
{identifier} {printf("ID");return(ID);}
{number} {printf("NUMBER");return(NUMBER);}
"<" {printf("LT");return(RELOP);}
"<=" {printf("LE");return(RELOP);}
"=" {printf("EQ");return(RELOP);}
"<>" {printf("NE");return(RELOP);}
">" {printf("GT");return(RELOP);}
">=" {printf("GE");return(RELOP);}
{whitespace} {}
\n {lines++;}
. {return ERROR;}
%%

int yywrap(void){return 1;}
int main()
{
	int token;
	yyin=fopen("myfile.txt","r");
	while((token=yylex())!=0)
		printf("(%d) %s\n",token,yytext);
	printf("Lines consumed: %d\n",lines);
	yylex();
	return 1;
}