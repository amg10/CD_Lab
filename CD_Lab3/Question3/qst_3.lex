%{
	#define ERROR -1
	#define INT 1
	#define FLOAT 2
	#define IF 3
	#define FOR 4
	#define WHILE 5
	#define READ 6
	#define PRINT 7
	#define ID 8
	#define NUMBER 9
	#define RELOP 10
	#define ARTM_OP 11
	#define ASSIGN_OP 12
	#define SEP 13
	#define INCR_OP 14
	#define DECR_OP 15
	#define OP_ASSIGN 16
	#define MAIN 17
	int lines=1;
%}
whitespace [ \t]
letter [A-Za-z]
digit [0-9]
number ({digit}+(\.{digit}+)?(E[+-]?{digit}+)?)
l_or_d ({letter}|{digit})
identifier ({letter}{l_or_d}*)
relop (<|>|<=|>=|<>|==)
autochg (\+=|\-=|\*=|\/=)
operator [+\-*/]
seperator [(){};,]

%%
int|INT {printf("INT");return INT;}
float|FLOAT {printf("FLOAT");return FLOAT;}
if {printf("IF");return IF;}
for {printf("FOR");return FOR;}
while {printf("WHILE");return WHILE;}
read {printf("READ");return READ;}
print {printf("PRINT");return PRINT;}
"main()" {printf("MAIN");return MAIN;}
{identifier} {printf("ID");return ID;}
{number} {printf("NUMBER");return NUMBER;}
{relop} {printf("RELOP");return RELOP;}
{operator} {printf("ARTM_OP");return ARTM_OP;}
"=" {printf("ASSIGN_OP");return ASSIGN_OP;}
{seperator} {printf("SEPERATOR");return SEP;} 
"++" {printf("INCR_OP");return INCR_OP;}
"--" {printf("DECR_OP");return DECR_OP;}
{autochg} {printf("OP_ASSIGN");return OP_ASSIGN;}
{whitespace} {}
\n {printf("Line %d done...............\n",lines);lines++;}
. {printf("ERROR");return ERROR;}

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