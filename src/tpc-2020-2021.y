%{
/* tpc-2020-2021.y */
/* Syntaxe du TPC pour le projet d'analyse syntaxique de 2020-2021*/
/* Projet d'analyse synthaxique Arthur PAIRAUD*/
#include <stdio.h>
#include "../src/abstract-tree.h"
#include "../src/decl-var.h"
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#define YYERROR_VERBOSE 1
extern FILE *yyin;
int yyparse();
int yylex();
int yyerror(const char *s);
Node* abs_tree;
extern char line[200];
extern int yylineno;
extern int column;
extern char* yytext;
%}

%union {
    struct Node * tree;
    char* carac;
}

%token <tree> IF ELSE
%token <tree> IDENT
%token <tree> PRINT
%token <tree> WHILE
%token <tree> RETURN
%token <tree> OR AND
%token <tree> EQ ORDER
%token <tree> ADDSUB DIVSTAR
%token <tree> NUM CHARACTER
%token <tree> TYPE
%token <tree> VOID 
%token <tree> READE READC
%token <tree> STRUCT
%precedence ')'
%precedence ELSE
%type <tree> Prog TypesVars Type DeclChamps Declarateurs DeclFoncts DeclFonct
%type <tree> EnTeteFonct Parametres ListTypVar Corps DeclVars SuiteInstr Instr 
%type <tree> Exp TB FB M  E  T F LValue Arguments ListExp

%%
Prog:  TypesVars DeclFoncts                         {   $$ = makeNode(Prog);
                                                        addChild($$, $1);
                                                        addChild($$, $2);
                                                        make_Symbole_table($$);
                                                        abs_tree = $$;
                                                    }
    ;
TypesVars:
       TypesVars Type Declarateurs ';'              {   
                                                        $$ = $1; 
                                                        addChild($$, $2);
                                                        addChild($2, $3);
                                                    }
    |  TypesVars STRUCT IDENT '{' DeclChamps '}'    {   
                                                        $$ = $1;
                                                        addChild($$, $2);
                                                        strcpy($2->u.identifier, $3->u.identifier);
                                                        addChild($2, $5);
                                                    }
    |   %empty                                      { $$ = makeNode(TypesVars); }
    ;
Type:
       TYPE                                         {   
                                                        $$ = $1;
                                                    }
    |  STRUCT IDENT                                 {   
                                                        $$ = $1; 
                                                        strcpy($1->u.identifier, $2->u.identifier);
                                                    }
    ;
DeclChamps:
       DeclChamps TYPE Declarateurs ';'             {   
                                                        $$ = $1; 
                                                        addChild($$, $2);
                                                        addChild($2, $3);  
                                                    }
    |  TYPE Declarateurs ';'                        {   
                                                        $$ = makeNode(DeclChamps); 
                                                        addChild($$, $1); 
                                                        addChild($1, $2);
                                                    }
    ;
Declarateurs:
       Declarateurs ',' IDENT                       {   
                                                        $$ = $1; 
                                                        addSibling($$, $3);  
                                                    }
    |  IDENT                                        {   
                                                        $$ = $1;  
                                                    }
    ;
DeclFoncts:
       DeclFoncts DeclFonct                         {   
                                                        $$ = $1;  
                                                        addSibling($$, $2); 
                                                    }
    |  DeclFonct                                    {   
                                                        $$ = $1;  
                                                    }
    ;
DeclFonct:
       EnTeteFonct Corps                            {   
                                                        $$ = makeNode(DeclFonct); 
                                                        addChild($$, $1);  
                                                        addChild($$, $2); 
                                                    }
    ;
EnTeteFonct:
       Type IDENT '(' Parametres ')'                {   
                                                        $$ = $1;  
                                                        addChild($$, $2); 
                                                        addChild($$, $4); 
                                                    }
    |  VOID IDENT '(' Parametres ')'                {   
                                                        $$ = $1;  
                                                        addChild($$, $2); 
                                                        addChild($$, $4); 
                                                    }
    ;
Parametres:
       VOID                                         {   
                                                        $$ = makeNode(Parametres);
                                                        addChild($$, $1);  
                                                    }
    |  ListTypVar                                   {   
                                                        $$ = makeNode(Parametres);
                                                        addChild($$, $1);  
                                                    }
    ;
ListTypVar:
       ListTypVar ',' Type IDENT                    {   
                                                        $$ = $1;  
                                                        addSibling($$, $3);  
                                                        addChild($3, $4);  
                                                    }
    |  Type IDENT                                   {   
                                                        $$ = $1;  
                                                        addChild($1, $2);    
                                                    }
    ;
Corps: '{' DeclVars SuiteInstr '}'                  {   
                                                        $$ = makeNode(Corps); 
                                                        addChild($$, $2);  
                                                        addChild($$, $3);    
                                                    }
    ;
DeclVars:
       DeclVars Type Declarateurs ';'               {   
                                                        $$ = $1;
                                                        addChild($$, $2);  
                                                        addChild($2, $3);    
                                                    }
    |   %empty                                      {   
                                                        $$ = makeNode(DeclVars);    
                                                    }
    ;           
SuiteInstr:
       SuiteInstr Instr                             {   
                                                        $$ = $1;
                                                        addChild($$, $2);   
                                                    }
    |  %empty                                       {   
                                                        $$ = makeNode(SuiteInstr);    
                                                    }
    ;   
Instr:
       LValue '=' Exp ';'                           {   
                                                        $$ = makeNode(Asignment); 
                                                        addChild($$, $1);
                                                        addChild($$, $3);   
                                                    }
    |  READE '(' IDENT ')' ';'                      {   
                                                        $$ = $1;
                                                        addChild($1, $3);   
                                                    }
    |  READC '(' IDENT ')' ';'                      {   
                                                        $$ = $1;
                                                        addChild($1, $3);   
                                                    }
    |  PRINT '(' Exp ')' ';'                        {   
                                                        $$ = $1;
                                                        addChild($1, $3);   
                                                    }
    |  IF '(' Exp ')' Instr                         {   
                                                        $$ = $1;
                                                        addChild($1, $3);  
                                                        addChild($1, $5); 
                                                    }
    |  IF '(' Exp ')' Instr ELSE Instr              {   
                                                        $$ = $1;
                                                        addChild($1, $3);  
                                                        addChild($1, $5);
                                                        addChild($1, $6);
                                                        addChild($6, $7); 
                                                    }
    |  WHILE '(' Exp ')' Instr                      {   
                                                        $$ = $1;
                                                        addChild($1, $3);  
                                                        addChild($1, $5); 
                                                    }
    |  Exp ';'                                      {   
                                                        $$ = $1; 
                                                    }
    |  RETURN Exp ';'                               {   
                                                        $$ = $1;
                                                        addChild($$, $2);
                                                    }
    |  RETURN ';'                                   {   
                                                        $$ = $1;
                                                    }
    |  '{' SuiteInstr '}'                           {   
                                                        $$ = $2;
                                                    }
    |  ';'                                          {   
                                                        $$ = makeNode(Instr);
                                                    }
    ;
Exp :  Exp OR TB                                    {   
                                                        $$ = $2;
                                                        addChild($$, $1);
                                                        addChild($$, $3);
                                                    }
    |  TB                                           {   
                                                        $$ = $1;
                                                    }
    ;
TB  :  TB AND FB                                    {   
                                                        $$ = $2;
                                                        addChild($$, $1);
                                                        addChild($$, $3);
                                                    }
    |  FB                                           {   
                                                        $$ = $1;
                                                    }
    ;
FB  :  FB EQ M                                      {   
                                                        $$ = $2;
                                                        addChild($$, $1);
                                                        addChild($$, $3);
                                                    }
    |  M                                            {   
                                                        $$ = $1;
                                                    }
    ;
M   :  M ORDER E                                    {   
                                                        $$ = $2;
                                                        addChild($$, $1);
                                                        addChild($$, $3);
                                                    }
    |  E                                            {   
                                                        $$ = $1;
                                                    }
    ;
E   :  E ADDSUB T                                   {   
                                                        $$ = $2;
                                                        addChild($$, $1);
                                                        addChild($$, $3);
                                                    }
    |  T                                            {   
                                                        $$ = $1;
                                                    }
    ;    
T   :  T DIVSTAR F                                  {   
                                                        $$ = $2;
                                                        addChild($$, $1);
                                                        addChild($$, $3);
                                                    }
    |  F                                            {   
                                                        $$ = $1;
                                                    }
    ;
F   :  ADDSUB F                                     {   
                                                        $$ = $1;
                                                        addChild($$, $2);
                                                    }
    |  '!' F                                        {   
                                                        $$ = makeNode(Not);
                                                        addChild($$, $2);
                                                    }
    |  '(' Exp ')'                                  {   
                                                        $$ = $2;
                                                    }
    |  NUM                                          {   
                                                        $$ = $1;
                                                    }
    |  CHARACTER                                    {   
                                                        $$ = $1;
                                                    }
    |  LValue                                       {   
                                                        $$ = $1;
                                                    }
    |  IDENT '(' Arguments  ')'                     {   
                                                        $$ = $1;
                                                        addChild($1, $3);
                                                    }
    ;
LValue:
       IDENT                                        {   
                                                        $$ = $1;
                                                    }
    |  IDENT '.' IDENT                              {   
                                                        $$ = makeNode(LValue);
                                                        addChild($$, $1);
                                                        addChild($$, $3);
                                                    }
    ;
Arguments:
       ListExp                                      {   
                                                        $$ = $1;
                                                    }
    |  %empty                                       {   
                                                        $$ = makeNode(Arguments);
                                                    }
    ;
ListExp:
       ListExp ',' Exp                              {   
                                                        $$ = makeNode(ListExp);
                                                        addChild($$, $1);
                                                        addChild($$, $3);
                                                    }
    |  Exp                                          {   
                                                        $$ = $1;
                                                    }
    ;
%%

int yyerror(const char *s) {
    fprintf(stderr, "%s near line %d column %d\n", s, yylineno, column);
    fprintf(stderr, "%s\n", line);
    for(int i = 0; i < column - 1; i++)
        fprintf(stderr," ");
    fprintf(stderr,"^\n");
    return 0;
}

int main(int argc, char *argv[]) {
    int help_flag = 0;
    int tree_flag = 0;
    int symb_flag = 0;
    int opt;
    int option_index = 0;
    int nb_opt = 0;
    struct option longopts[] = {
        { "help", no_argument, &help_flag, 1 },
        { "tree", no_argument, &tree_flag, 1 },
        { "symtabs", no_argument, &symb_flag, 1 },
        {0, 0, 0, 0 }
    };

    while ((opt = getopt_long(argc, argv, "-t-s-h", longopts, &option_index)) != -1) {
        nb_opt++;
        switch (opt) {
            case 't':
                tree_flag = 1;
                //printf("%s\n", optarg);
                break;
            case 's':
                symb_flag = 1;
                break;
            case '?':
                fprintf(stderr, "Erreur : Option invalide\n");
            case 'h':
                help_flag = 1;
                break;
            default: 
                break;
        }
    }

    if (nb_opt <= argc) {
        yyin = fopen(argv[nb_opt], "r");
    }

    if (yyparse()) {
        return 1;
    }

    if (help_flag) {
        printf("./bin/tpcc [OPTIONS] < FILE.tpc\n");
        printf("[OPTIONS] : \n");
        printf("-t : affiche l'arbre abstrait sur la sortie standart.\n");
        printf("-s : affiche toutes les tables des symboles sur la sortie standard.\n");
        printf("-h : affiche une description de l’interface utilisateur et termine l’exécution.\n");
        printf("FILE.tpc : le fichier .tpc sur lequel vous voulez tester.\n");
        printf("./test.sh : Est un script bash permettant de lancer tout les tests du dossiers test.\n");
        return 0;
    }

    if (tree_flag) {
        printf("Tree\n");
        /* Affiche tree */
        printTree(abs_tree);
    }

    if (symb_flag) {
        printf("Symbol\n");
        /* Affiche symbol table */
        printTables(abs_tree);
    }

    deleteTree(abs_tree);
    return 0;
}