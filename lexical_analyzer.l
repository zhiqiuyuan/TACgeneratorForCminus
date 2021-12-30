%option noyywrap
%{
#include <stdio.h>
#include <stdlib.h>

#include "syntax_tree.h"
#include "syntax_analyzer.tab.h"

int files_count;
int lines;
int pos_start;
int pos_end;

void pass_node(char *name, char*yytext){
     yylval.node = new_syntax_tree_node_yytext(name,yytext); 
}
%}

%%

\n { lines++;pos_start=1;pos_end=1;} 
[ \t\r] { pos_start=pos_end;pos_end=pos_start+1;}
\/\*([^\*]*|\*+[^\/]|\n)*\*\/ { 
    pos_start=pos_end;
    //pass_node(yytext);
    char*p=yytext;
    while(p&&*p){
        char c=*p;
        if(c=='\n'){
            lines++;
            pos_end=strlen(p+1)+1;
        }
        ++p;
    }
}

"+" { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("ADD",yytext);return ADD;}
"-" { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("SUB",yytext);return SUB;}
"*" { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("MUL",yytext);return MUL;}
"/" { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("DIV",yytext);return DIV;}
"<" { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("LT",yytext);return LT;}
">" { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("GT",yytext);return GT;}
"=" { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("ASSIN",yytext); return ASSIN;}
";" { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("SEMICOLON",yytext); return SEMICOLON;}
"," { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("COMMA",yytext); return COMMA;}
"(" { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("LPARENTHESE",yytext); return LPARENTHESE;}
")" { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("RPARENTHESE",yytext); return RPARENTHESE;}
"{" { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("LBRACE",yytext); return LBRACE;}
"}" { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("RBRACE",yytext); return RBRACE;}
"<=" { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("LTE",yytext);return LTE;}
">=" { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("GTE",yytext);return GTE;}
"==" { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("EQ",yytext);return EQ;}
"!=" { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("NEQ",yytext);return NEQ;}
"else" { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("ELSE",yytext); return ELSE;}
"if" { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("IF",yytext); return IF;}
"int" { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("INT",yytext); return INT;}
"float" { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("FLOAT",yytext); return FLOAT;}
"return" { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("RETURN",yytext); return RETURN;}
"void" { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("VOID",yytext); return VOID;}
"while" { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("WHILE",yytext); return WHILE;}
"[]" { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("ARRAY",yytext); return ARRAY;}
"[" { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("LBRACKET",yytext); return LBRACKET;}
"]" { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("RBRACKET",yytext); return RBRACKET;}
[a-zA-Z]+ { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("IDENTIFIER",yytext); return IDENTIFIER;}
[a-zA-Z] { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("LETTER",yytext); return LETTER;}
[0-9]|[1-9][0-9]* { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("INTEGER",yytext); return INTEGER;}
(([0-9]|[1-9][0-9]*)\.[0-9]*)|(\.[0-9]+) { pos_start=pos_end;pos_end=pos_start+yyleng;pass_node("FLOATPOINT",yytext); return FLOATPOINT;}


<<EOF>> { pos_start=pos_end;pos_end=pos_start+yyleng;return EOF;} 
. { pos_start=pos_end;pos_end=pos_start+yyleng;}

%%
