%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "syntax_tree.h"
extern FILE *yyin;
// external functions from lex
extern int yylex();
 //extern "C" int yyparse (void);

// external variables from lexical_analyzer module
extern int lines;
extern char *yytext;
extern int pos_end;
extern int pos_start;

// Global syntax tree
syntax_tree *gt;

// Error reporting
void yyerror(const char *s);
%}

/* TODO: Complete this definition. */
%union {
    syntax_tree_node* node;
}

/* TODO: Your tokens here. */
%type <node> program type-specifier relop addop mulop declaration-list declaration var-declaration fun-declaration local-declarations compound-stmt statement-list statement expression-stmt iteration-stmt selection-stmt return-stmt expression simple-expression var additive-expression term factor integer float call params param-list param args arg-list 
%token <node> LT  LTE  GT  GTE  EQ  NEQ  ASSIN  SEMICOLON  COMMA  LPARENTHESE  RPARENTHESE  LBRACKET  RBRACKET  LBRACE  RBRACE  ELSE  IF  INT  FLOAT  RETURN  VOID  WHILE  IDENTIFIER  INTEGER  FLOATPOINT  ARRAY  LETTER  EOL  COMMENT  BLANK  ERROR ADD SUB MUL DIV 
/*%left <node> ADD SUB
%left <node> MUL DIV*/
%start program

%%
/* TODO: Your rules here. */

program  :  
declaration-list {
    $$ = new_syntax_tree_node("program");
    syntax_tree_add_child($$, $1);
    gt->root=$$;
	//printf("program -> declaration-list\n");
}

declaration-list  :
declaration-list  declaration {
	$$ = new_syntax_tree_node("declaration-list");
	syntax_tree_add_child($$, $1);
	syntax_tree_add_child($$, $2);
	//printf("declaration-list -> declaration-list  declaration\n");
}
| declaration {
	$$ = new_syntax_tree_node("declaration-list");
	syntax_tree_add_child($$, $1);
	//printf("declaration-list -> declaration\n");
}

declaration  :
var-declaration {
	$$ = new_syntax_tree_node("declaration");
	syntax_tree_add_child($$, $1);
	//printf("declaration -> var-declaration\n");
}
| fun-declaration {
	$$ = new_syntax_tree_node("declaration");
	syntax_tree_add_child($$, $1);
	//printf("declaration -> fun-declaration\n");
}

var-declaration :
type-specifier  IDENTIFIER  SEMICOLON {
	$$ = new_syntax_tree_node("var-declaration");
	syntax_tree_add_child($$, $1);
	syntax_tree_add_child($$, $2);
	syntax_tree_add_child($$, $3);
	//printf("var-declaration -> type-specifier  IDENTIFIER  SEMICOLON\n");
}
| type-specifier  IDENTIFIER  LBRACKET  INTEGER  RBRACKET  SEMICOLON {
	$$ = new_syntax_tree_node("var-declaration");
	syntax_tree_add_child($$, $1);
	syntax_tree_add_child($$, $2);
	syntax_tree_add_child($$, $3);
	syntax_tree_add_child($$, $4);
	syntax_tree_add_child($$, $5);
	syntax_tree_add_child($$, $6);
	//printf("var-declaration -> type-specifier  IDENTIFIER  LBRACKET  INTEGER  RBRACKET  SEMICOLON\n");
}

type-specifier  :
INT {
	$$ = new_syntax_tree_node("type-specifier");
	syntax_tree_add_child($$, $1);
	//printf("type-specifier -> INT\n");
}
| FLOAT {
	$$ = new_syntax_tree_node("type-specifier");
	syntax_tree_add_child($$, $1);
	//printf("type-specifier -> FLOAT\n");
}
| VOID {
	$$ = new_syntax_tree_node("type-specifier");
	syntax_tree_add_child($$, $1);
	//printf("type-specifier -> VOID\n");
}

fun-declaration  :
type-specifier  IDENTIFIER  LPARENTHESE  params  RPARENTHESE  compound-stmt {
	$$ = new_syntax_tree_node("fun-declaration");
	syntax_tree_add_child($$, $1);
	syntax_tree_add_child($$, $2);
	syntax_tree_add_child($$, $3);
	syntax_tree_add_child($$, $4);
	syntax_tree_add_child($$, $5);
	syntax_tree_add_child($$, $6);
	//printf("fun-declaration -> type-specifier  IDENTIFIER  LPARENTHESE  params  RPARENTHESE  compound-stmt\n");
}

params  :
param-list {
	$$ = new_syntax_tree_node("params");
	syntax_tree_add_child($$, $1);
	//printf("params -> param-list\n");
}
| VOID {
	$$ = new_syntax_tree_node("params");
	syntax_tree_add_child($$, $1);
	//printf("params -> VOID\n");
}

param-list  :
param-list COMMA param {
	$$ = new_syntax_tree_node("param-list");
	syntax_tree_add_child($$, $1);
	syntax_tree_add_child($$, $2);
	syntax_tree_add_child($$, $3);
	//printf("param-list -> param-list COMMA param\n");
}
| param {
	$$ = new_syntax_tree_node("param-list");
	syntax_tree_add_child($$, $1);
	//printf("param-list -> param\n");
}

param  :
type-specifier  IDENTIFIER {
	$$ = new_syntax_tree_node("param");
	syntax_tree_add_child($$, $1);
	syntax_tree_add_child($$, $2);
	//printf("param -> type-specifier  IDENTIFIER\n");
}
| type-specifier  IDENTIFIER  ARRAY {
	$$ = new_syntax_tree_node("param");
	syntax_tree_add_child($$, $1);
	syntax_tree_add_child($$, $2);
	syntax_tree_add_child($$, $3);
	//printf("param -> type-specifier  IDENTIFIER  ARRAY\n");
}

compound-stmt  :
LBRACE  local-declarations  statement-list RBRACE {
	$$ = new_syntax_tree_node("compound-stmt");
	syntax_tree_add_child($$, $1);
	syntax_tree_add_child($$, $2);
	syntax_tree_add_child($$, $3);
	syntax_tree_add_child($$, $4);
	//printf("compound-stmt -> LBRACE  local-declarations  statement-list RBRACE\n");
}

local-declarations  :
local-declarations var-declaration {
	$$ = new_syntax_tree_node("local-declarations");
	syntax_tree_add_child($$, $1);
	syntax_tree_add_child($$, $2);
	//printf("local-declarations -> local-declarations var-declaration\n");
}
| {
	$$ = new_syntax_tree_node("local-declarations");
	syntax_tree_node * empty_child = new_syntax_tree_node("epsilon");
	syntax_tree_add_child($$, empty_child);
	//printf("local-declarations -> \n");
}

statement-list  :
statement-list  statement {
	$$ = new_syntax_tree_node("statement-list");
	syntax_tree_add_child($$, $1);
	syntax_tree_add_child($$, $2);
	//printf("statement-list -> statement-list  statement\n");
}
| {
	$$ = new_syntax_tree_node("statement-list");
	syntax_tree_node * empty_child = new_syntax_tree_node("epsilon");
	syntax_tree_add_child($$, empty_child);
	//printf("statement-list -> \n");
}

statement  :
expression-stmt {
	$$ = new_syntax_tree_node("statement");
	syntax_tree_add_child($$, $1);
	//printf("statement -> expression-stmt\n");
}
| compound-stmt {
	$$ = new_syntax_tree_node("statement");
	syntax_tree_add_child($$, $1);
	//printf("statement -> compound-stmt\n");
}
| selection-stmt {
	$$ = new_syntax_tree_node("statement");
	syntax_tree_add_child($$, $1);
	//printf("statement -> selection-stmt\n");
}
| iteration-stmt {
	$$ = new_syntax_tree_node("statement");
	syntax_tree_add_child($$, $1);
	//printf("statement -> iteration-stmt\n");
}
| return-stmt {
	$$ = new_syntax_tree_node("statement");
	syntax_tree_add_child($$, $1);
	//printf("statement -> return-stmt\n");
}

expression-stmt  :
expression  SEMICOLON {
	$$ = new_syntax_tree_node("expression-stmt");
	syntax_tree_add_child($$, $1);
	syntax_tree_add_child($$, $2);
	//printf("expression-stmt -> expression  SEMICOLON\n");
}
| SEMICOLON {
	$$ = new_syntax_tree_node("expression-stmt");
	syntax_tree_add_child($$, $1);
	//printf("expression-stmt -> SEMICOLON\n");
}

selection-stmt  :
IF  LPARENTHESE  expression  RPARENTHESE  statement {
	$$ = new_syntax_tree_node("selection-stmt");
	syntax_tree_add_child($$, $1);
	syntax_tree_add_child($$, $2);
	syntax_tree_add_child($$, $3);
	syntax_tree_add_child($$, $4);
	syntax_tree_add_child($$, $5);
	//printf("selection-stmt -> IF  LPARENTHESE  expression  RPARENTHESE  statement\n");
}
| IF  LPARENTHESE  expression  RPARENTHESE  statement  ELSE  statement {
	$$ = new_syntax_tree_node("selection-stmt");
	syntax_tree_add_child($$, $1);
	syntax_tree_add_child($$, $2);
	syntax_tree_add_child($$, $3);
	syntax_tree_add_child($$, $4);
	syntax_tree_add_child($$, $5);
	syntax_tree_add_child($$, $6);
	syntax_tree_add_child($$, $7);
	//printf("selection-stmt -> IF  LPARENTHESE  expression  RPARENTHESE  statement  ELSE  statement\n");
}

iteration-stmt  :
WHILE  LPARENTHESE  expression  RPARENTHESE  statement {
	$$ = new_syntax_tree_node("iteration-stmt");
	syntax_tree_add_child($$, $1);
	syntax_tree_add_child($$, $2);
	syntax_tree_add_child($$, $3);
	syntax_tree_add_child($$, $4);
	syntax_tree_add_child($$, $5);
	//printf("iteration-stmt -> WHILE  LPARENTHESE  expression  RPARENTHESE  statement\n");
}

return-stmt  :
RETURN  SEMICOLON {
	$$ = new_syntax_tree_node("return-stmt");
	syntax_tree_add_child($$, $1);
	syntax_tree_add_child($$, $2);
	//printf("return-stmt -> RETURN  SEMICOLON\n");
}
| RETURN  expression  SEMICOLON {
	$$ = new_syntax_tree_node("return-stmt");
	syntax_tree_add_child($$, $1);
	syntax_tree_add_child($$, $2);
	syntax_tree_add_child($$, $3);
	//printf("return-stmt -> RETURN  expression  SEMICOLON\n");
}

expression  :
var  ASSIN  expression {
	$$ = new_syntax_tree_node("expression");
	syntax_tree_add_child($$, $1);
	syntax_tree_add_child($$, $2);
	syntax_tree_add_child($$, $3);
	//printf("expression -> var  ASSIN  expression\n");
}
| simple-expression {
	$$ = new_syntax_tree_node("expression");
	syntax_tree_add_child($$, $1);
	//printf("expression -> simple-expression\n");
}

var  :
IDENTIFIER {
	$$ = new_syntax_tree_node("var");
	syntax_tree_add_child($$, $1);
	//printf("var -> IDENTIFIER\n");
}
| IDENTIFIER  LBRACKET  expression   RBRACKET {
	$$ = new_syntax_tree_node("var");
	syntax_tree_add_child($$, $1);
	syntax_tree_add_child($$, $2);
	syntax_tree_add_child($$, $3);
	syntax_tree_add_child($$, $4);
	//printf("var -> IDENTIFIER  LBRACKET  expression   RBRACKET\n");
}

simple-expression  :
additive-expression  relop  additive-expression {
	$$ = new_syntax_tree_node("simple-expression");
	syntax_tree_add_child($$, $1);
	syntax_tree_add_child($$, $2);
	syntax_tree_add_child($$, $3);
	//printf("simple-expression -> additive-expression  relop  additive-expression\n");
}
| additive-expression {
	$$ = new_syntax_tree_node("simple-expression");
	syntax_tree_add_child($$, $1);
	//printf("simple-expression -> additive-expression\n");
}

relop :
LTE {
	$$ = new_syntax_tree_node("relop");
	syntax_tree_add_child($$, $1);
	//printf("relop -> LTE\n");
}
| LT {
	$$ = new_syntax_tree_node("relop");
	syntax_tree_add_child($$, $1);
	//printf("relop -> LT\n");
}
| GT {
	$$ = new_syntax_tree_node("relop");
	syntax_tree_add_child($$, $1);
	//printf("relop -> GT\n");
}
| GTE {
	$$ = new_syntax_tree_node("relop");
	syntax_tree_add_child($$, $1);
	//printf("relop -> GTE\n");
}
| EQ {
	$$ = new_syntax_tree_node("relop");
	syntax_tree_add_child($$, $1);
	//printf("relop -> EQ\n");
}
| NEQ {
	$$ = new_syntax_tree_node("relop");
	syntax_tree_add_child($$, $1);
	//printf("relop -> NEQ\n");
}

additive-expression  :
additive-expression  addop  term {
	$$ = new_syntax_tree_node("additive-expression");
	syntax_tree_add_child($$, $1);
	syntax_tree_add_child($$, $2);
	syntax_tree_add_child($$, $3);
	//printf("additive-expression -> additive-expression  addop  term\n");
}
| term {
	$$ = new_syntax_tree_node("additive-expression");
	syntax_tree_add_child($$, $1);
	//printf("additive-expression -> term\n");
}

addop  :
ADD {
	$$ = new_syntax_tree_node("addop");
	syntax_tree_add_child($$, $1);
	//printf("addop -> ADD\n");
}
| SUB {
	$$ = new_syntax_tree_node("addop");
	syntax_tree_add_child($$, $1);
	//printf("addop -> SUB\n");
}

term  :
term  mulop  factor {
	$$ = new_syntax_tree_node("term");
	syntax_tree_add_child($$, $1);
	syntax_tree_add_child($$, $2);
	syntax_tree_add_child($$, $3);
	//printf("term -> term  mulop  factor\n");
}
| factor {
	$$ = new_syntax_tree_node("term");
	syntax_tree_add_child($$, $1);
	//printf("term -> factor\n");
}

mulop  :
MUL {
	$$ = new_syntax_tree_node("mulop");
	syntax_tree_add_child($$, $1);
	//printf("mulop -> MUL\n");
}
| DIV {
	$$ = new_syntax_tree_node("mulop");
	syntax_tree_add_child($$, $1);
	//printf("mulop -> DIV\n");
}

factor  :
LPARENTHESE  expression  RPARENTHESE {
	$$ = new_syntax_tree_node("factor");
	syntax_tree_add_child($$, $1);
	syntax_tree_add_child($$, $2);
	syntax_tree_add_child($$, $3);
	//printf("factor -> LPARENTHESE  expression  RPARENTHESE\n");
}
| var {
	$$ = new_syntax_tree_node("factor");
	syntax_tree_add_child($$, $1);
	//printf("factor -> var\n");
}
| call {
	$$ = new_syntax_tree_node("factor");
	syntax_tree_add_child($$, $1);
	//printf("factor -> call\n");
}
| integer {
	$$ = new_syntax_tree_node("factor");
	syntax_tree_add_child($$, $1);
	//printf("factor -> integer\n");
}
| float {
	$$ = new_syntax_tree_node("factor");
	syntax_tree_add_child($$, $1);
	//printf("factor -> float\n");
}

integer  :
INTEGER {
	$$ = new_syntax_tree_node("integer");
	syntax_tree_add_child($$, $1);
	//printf("integer -> INTEGER\n");
}

float  :
FLOATPOINT {
	$$ = new_syntax_tree_node("float");
	syntax_tree_add_child($$, $1);
	//printf("float -> FLOATPOINT\n");
}

call  :
IDENTIFIER  LPARENTHESE  args   RPARENTHESE {
	$$ = new_syntax_tree_node("call");
	syntax_tree_add_child($$, $1);
	syntax_tree_add_child($$, $2);
	syntax_tree_add_child($$, $3);
	syntax_tree_add_child($$, $4);
	//printf("call -> IDENTIFIER  LPARENTHESE  args   RPARENTHESE\n");
}

args  :
arg-list {
	$$ = new_syntax_tree_node("args");
	syntax_tree_add_child($$, $1);
	//printf("args -> arg-list\n");
}
| {
	$$ = new_syntax_tree_node("args");
	syntax_tree_node * empty_child = new_syntax_tree_node("epsilon");
	syntax_tree_add_child($$, empty_child);
	//printf("args -> \n");
}

arg-list  :
arg-list  COMMA  expression {
	$$ = new_syntax_tree_node("arg-list");
	syntax_tree_add_child($$, $1);
	syntax_tree_add_child($$, $2);
	syntax_tree_add_child($$, $3);
	//printf("arg-list -> arg-list  COMMA  expression\n");
}
| expression {
	$$ = new_syntax_tree_node("arg-list");
	syntax_tree_add_child($$, $1);
	//printf("arg-list -> expression\n");
}



%%

/// The error reporting function.
void yyerror(const char *s)
{
    // TO STUDENTS: This is just an example.
    // You can customize it as you like.
    fprintf(stderr, "error at line %d column %d: %s\n", lines, pos_start, s);
}

/// Parse input from file `input_path`, and prints the parsing results
/// to stdout.  If input_path is NULL, read from stdin.
///
/// This function initializes essential states before running yyparse().
syntax_tree *parse(const char *input_path)
{
    if (input_path != NULL) {
        if (!(yyin = fopen(input_path, "r"))) {
            fprintf(stderr, "[ERR] Open input file %s failed.\n", input_path);
            exit(1);
        }
    } else {
        yyin = stdin;
    }

    lines = pos_start = pos_end = 1;
    gt = new_syntax_tree();
    //yyrestart(yyin);
    yyparse();
    return gt;
}


