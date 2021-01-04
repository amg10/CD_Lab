%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int yylex();
void yyerror(char * s);

%}

%token AND ASSIGN COLON DIV ELSE END EQ EXITLOOP FLOAT FLOAT_CONST FORMAT FROM GE MAIN GT ID IF INT INT_CONST LEFT_PAREN LEFT_SQ_BKT LE LT MINUS MOD MULT NE NOT NUL OR PLUS PRINT PRODUCT READ RIGHT_PAREN RIGHT_SQ_BKT SEMICOLON STEP TO WHILE STRING
%start prog

%left PLUS MINUS
%left MULT DIV MOD
%left NOT
%left AND OR
%left RIGHT_SQ_BKT LEFT_SQ_BKT
%left RIGHT_PAREN LEFT_PAREN

%%
prog : MAIN  stmtListO END {printf("string valid\n");};
stmtListO : stmtList
	  | /*epsilon*/
	  ;
stmtList : stmtList SEMICOLON stmt
		| stmt
		;
stmt : assignmentStmt
     | readStmt
     | printStmt
     | ifStmt
     | whileStmt
     | loopStmt
     | exitLoop
     ;
assignmentStmt : Id ASSIGN exp
	       ;
Id : id
    ;
readStmt : READ FORMAT exp
	 ;
printStmt : PRINT STRING
	  | PRINT FORMAT exp
	  ;
ifStmt : IF bExp COLON stmtList elsePart END
       ;
elsePart : ELSE stmtList
	 | /*epsilon*/
 	 ;
whileStmt : WHILE bExp COLON stmtList END
	  ;
loopStmt : FROM id ASSIGN exp TO exp stepPart COLON stmtListO END
	 ;
stepPart : STEP exp
	| /*epsilon*/
	 ;
exitLoop : EXITLOOP
	 ;
id : ID indxListO
   ;
indxListO : indxList
	  | /*epsilon*/
	  ;
indxList : indxList LEFT_SQ_BKT exp RIGHT_SQ_BKT
	 | LEFT_SQ_BKT exp RIGHT_SQ_BKT
bExp : bExp OR bExp
     | bExp AND bExp
     | NOT bExp
     | LEFT_PAREN bExp RIGHT_PAREN
     | exp relOP exp
     ;
relOP : EQ
      | LE
      | LT
      | GE
      | GT
      | NE
      ;
exp : exp PLUS exp
    | exp MINUS exp
    | exp MULT exp
    | exp DIV exp
    | exp MOD exp
    | MINUS exp
    | PLUS exp
    | LEFT_PAREN exp RIGHT_PAREN
    | id
    | INT_CONST
    | FLOAT_CONST
    ;

%%

extern int yylex();
extern int yyparse();
extern int yylineno;

void yyerror(char *s){
	printf("Error: %s at line %d\n",s,yylineno);
	exit(-1);
}
int main()
{
	extern FILE *yyin, *yyout;
	yyin=fopen("input.txt","r");
	yyparse();
	return 0;
}
