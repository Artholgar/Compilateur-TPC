%{
/* Projet d'analyse synthaxique Arthur PAIRAUD*/
#include "tpc-2020-2021.tab.h"
#include "../src/abstract-tree.h"
int column = 1;
int next_column = 1;

char line[200];

%}
%option noinput
%option nounput
%option noyywrap
%option yylineno
%x COMM
%%
^.*$                    { strcpy(line, yytext)
                        ; REJECT; }
(\/\*)                  BEGIN COMM;
<COMM>(\*\/)            BEGIN INITIAL;
<COMM>.                 ;
<COMM>\n                ;
"if"                    { 
                            struct Node * t = makeNode(If);
                            yylval.tree = t; 
                            column = next_column; next_column+=strlen(yytext); return IF; 
                        }
"else"                  { 
                            struct Node * t = makeNode(Else);
                            strcpy(t->u.identifier, yytext);
                            yylval.tree = t; 
                            column = next_column; next_column+=strlen(yytext); return ELSE; 
                        } 
"while"                 { 
                            struct Node * t = makeNode(While);
                            yylval.tree = t; 
                            column = next_column; next_column+=strlen(yytext); return WHILE; 
                        } 
"return"                { 
                            struct Node * t = makeNode(Return);
                            yylval.tree = t; 
                            column = next_column; next_column+=strlen(yytext); return RETURN; 
                        }
"void"                  { 
                            struct Node * t = makeNode(Type);
                            strcpy(t->u.identifier, yytext);
                            yylval.tree = t; 
                            column = next_column; next_column+=strlen(yytext); return VOID; 
                        }
"reade"                 { 
                            struct Node * t = makeNode(Reade);
                            yylval.tree = t; 
                            column = next_column; next_column+=strlen(yytext); return READE; 
                        }
"readc"                 { 
                            struct Node * t = makeNode(Readc);
                            yylval.tree = t; 
                            column = next_column; next_column+=strlen(yytext); return READC; 
                        }
"print"                 { 
                            struct Node * t = makeNode(Print);
                            yylval.tree = t; 
                            column = next_column; next_column+=strlen(yytext); return PRINT; 
                        } 
"||"                    { 
                            struct Node * t = makeNode(Or);
                            yylval.tree = t; 
                            column = next_column; next_column+=strlen(yytext); return OR; 
                        }  
"&&"                    { 
                            struct Node * t = makeNode(And);
                            yylval.tree = t; 
                            column = next_column; next_column+=strlen(yytext); return AND; 
                        }
"=="|"!="               { 
                            struct Node * t = makeNode(Equals);
                            strcpy(t->u.identifier, yytext);
                            yylval.tree = t; 
                            column = next_column; next_column+=strlen(yytext); return EQ; 
                        }
"<"|"<="|">"|">="       { 
                            struct Node * t = makeNode(Compare);
                            strcpy(t->u.identifier, yytext);
                            yylval.tree = t; 
                            column = next_column; next_column+=strlen(yytext); return ORDER; 
                        }
"+"|"-"                 { 
                            struct Node * t = makeNode(AddSub);
                            strcpy(t->u.identifier, yytext);
                            yylval.tree = t; 
                            column = next_column; next_column+=strlen(yytext); return ADDSUB; 
                        }
"*"|"%"|"/"             { 
                            struct Node * t = makeNode(DivStar);
                            strcpy(t->u.identifier, yytext);
                            yylval.tree = t; 
                            column = next_column; next_column+=strlen(yytext); return DIVSTAR; 
                        } 
[0-9]+                  { 
                            struct Node * t = makeNode(IntLiteral);
                            t->u.integer = atoi(yytext); 
                            yylval.tree = t; 
                            column = next_column; next_column+=strlen(yytext); return NUM; 
                        }
'.'                     { 
                            struct Node * t = makeNode(CharLiteral);
                            printf("%s\n", yytext);
                            t->u.character = yytext[1]; 
                            yylval.tree = t; 
                            column = next_column; next_column+=strlen(yytext); return CHARACTER; 
                        }
'\\n'                     { 
                            struct Node * t = makeNode(CharLiteral);
                            printf("%s\n", yytext);
                            t->u.character = '\n'; 
                            yylval.tree = t; 
                            column = next_column; next_column+=strlen(yytext); return CHARACTER; 
                        }
"int"|"char"            { 
                            struct Node * t = makeNode(Type);
                            strcpy(t->u.identifier, yytext);
                            yylval.tree = t; 
                            column = next_column; next_column+=strlen(yytext); return TYPE; 
                        }
"struct"                { 
                            struct Node * t = makeNode(Struct);
                            yylval.tree = t; 
                            column = next_column; next_column+=strlen(yytext); return STRUCT; 
                        }
[_a-zA-Z][_a-zA-Z0-9]*  { 
                            struct Node * t = makeNode(Identifier);
                            strcpy(t->u.identifier, yytext);
                            yylval.tree = t; 
                            column = next_column; next_column+=strlen(yytext); return IDENT; 
                        }
[ \t]                   { column = next_column; next_column+=strlen(yytext); }
\n                      { column = next_column; next_column = 1; }
.                       { 
                            struct Node * t = makeNode(Identifier);
                            strcpy(t->u.identifier, yytext);
                            yylval.tree = t; 
                            column = next_column; next_column+=strlen(yytext); return yytext[0]; 
                        }
%%