%{
	#define ERROR -1
	#define ID 1
	#define ADD 2
	#define MUL 3
	#define OPNB 4
	#define CLB 5
	#define NL 6
	int lines=1;
%}
whitespace [ \t]
letter [A-Za-z]
digit [0-9]
l_or_d ({letter}|{digit})
identifier ({letter}{l_or_d}*)

%%
{identifier} {return(ID);}
"+" {return(ADD);}
"*" {return(MUL);}
"(" {return(OPNB);}
")" {return(CLB);}
{whitespace} {}
\n {lines++;return(NL);}
. {return ERROR;}
%%

int yywrap(void){return 1;}
int main()
{
	FILE * fptr;
	fptr=fopen("Tokenized_text.txt","w");
	int token;
	yyin=fopen("input_to_check.txt","r");
	while((token=yylex())!=0)
	{
		printf("Token number(%d) %s\n",token,yytext);
		switch(token)
		{
			case 1: fputs("id ",fptr);
					break;
			case 2:	fputs("+ ",fptr);
					break;
			case 3:	fputs("* ",fptr);
					break;
			case 4:	fputs("( ",fptr);
					break;
			case 5:	fputs(") ",fptr);
					break;
			default: fputs("error ",fptr);
		}
	}
	printf("Lines consumed: %d\n",lines);
	fclose(fptr);
	return 1;
}