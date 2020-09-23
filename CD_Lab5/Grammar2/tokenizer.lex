%{
	// ic, id,fc, str
	#define ERROR -1
	int lines=1;
%}
whitespace [ \t]
letter [A-Za-z]
digit [0-9]
l_or_d ({letter}|{digit})
str (letter{letter}*)
id ({letter}{l_or_d}*)
ic ([+-]?{digit}+)
fc ({digit}+(\.{digit}+)?(E[+-]?{digit}+)?)

%%
"+" {return(1);}
"-" {return(2);}
"*" {return(3);}
"/" {return(4);}
"=" {return(5);}
"<" {return(6);}
">" {return(7);}
"(" {return(8);}
")" {return(9);}
"{" {return(10);}
"}" {return(11);}
":=" {return(11);}
";" {return(12);}
"," {return(13);}
and {return(14);}
else {return(15);}
end {return(16);}
if	{return(17);}
int {return(18);}
do {return(19);}
float {return(20);}
not {return(21);}
or {return(22);}
print {return(23);}
prog {return(24);}
scan {return(25);}
then {return(26);}
while {return(27);}
{str} {return(28);}
{id} {return(29);}
{ic} {return(30);}
{fc} {return(31);}
{whitespace} {}
\n {lines++;return(32);}
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
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
			case 16:
			case 17:
			case 18:
			case 19:
			case 20:
			case 21:
			case 22:
			case 23:
			case 24:
			case 25:
			case 26:
			case 27:fputs(yytext,fptr);
					fputs(" ",fptr);
					break;
			case 28: fputs("str ",fptr);
					break;
			case 29:	fputs("id ",fptr);
					break;
			case 30:	fputs("ic ",fptr);
					break;
			case 31:	fputs("fc ",fptr);
					break;
			default : 	fputs("error ",fptr);
		}
	}
	printf("Lines consumed: %d\n",lines);
	fclose(fptr);
	return 1;
}