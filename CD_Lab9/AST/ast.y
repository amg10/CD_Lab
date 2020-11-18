%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
int isOp;
int value;
struct node *left;
struct node *right;
}node;

#define YYSTYPE node*

void yyerror(char * s);
void print_tree(node *root);

#include "y.tab.h"
#include "lex.yy.c"

int n;
%}

%token NUMBER
%start exp

%left '+' '-'
%left '*' '/' '%'
%left '(' ')'

%%
exp : E {printf("\nResult printed inorder:\n");print_tree($1);return 0;};
E : E '+' T { node *newnode= (node *)malloc(sizeof(node));
			newnode->isOp=1;
			newnode->value=(int)'+';
			newnode->left=$1;
			newnode->right=$3;
			$$=newnode;
			n=n+1;
			}
  | E '-' T { node *newnode= (node *)malloc(sizeof(node));
			newnode->isOp=1;
			newnode->value=(int)'-';
			newnode->left=$1;
			newnode->right=$3;
			$$=newnode;
			n=n+1;
			}
  | T {$$ = $1;}
  ;
T : T '*' F { node *newnode= (node *)malloc(sizeof(node));
			newnode->isOp=1;
			newnode->value=(int)'*';
			newnode->left=$1;
			newnode->right=$3;
			$$=newnode;
			n=n+1;
			}
  | T '/' F { node *newnode= (node *)malloc(sizeof(node));
			newnode->isOp=1;
			newnode->value=(int)'/';
			newnode->left=$1;
			newnode->right=$3;
			$$=newnode;
			n=n+1;
			}
  | T '%' F { node *newnode= (node *)malloc(sizeof(node));
			newnode->isOp=1;
			newnode->value=(int)'%';
			newnode->left=$1;
			newnode->right=$3;
			$$=newnode;
			n=n+1;
			}
  | F {$$ = $1;}
  ;
F : '(' E ')' {$$ = $2;}
  | NUMBER	{$$= $1;n=n+1;}
  ;
  
%%

void yyerror(char *s){
	printf("Invalid Expression!!\n");
	exit(-1);
}

void print_tree(node * root)
{
	if(root==NULL)
		return;
	if(root->left!=NULL)
		print_tree(root->left);
	if(root->isOp==1)
		printf("%c\n",(char)root->value);
	else
		printf("%d\n",root->value);
	if(root->right!=NULL)
		print_tree(root->right);
}
int main()
{
	return(yyparse());
}