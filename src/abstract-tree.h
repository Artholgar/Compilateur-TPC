/* abstract-tree.h */
#ifndef __ABSTR_TREE__
#define __ABSTR_TREE__

#include "decl-var.h"

#define FOREACH_NODE(NODE) \
        NODE(IntLiteral) \
        NODE(CharLiteral) \
        NODE(Identifier) \
        NODE(If) \
        NODE(Else) \
        NODE(While) \
        NODE(Print) \
        NODE(Or) \
        NODE(And) \
        NODE(Equals) \
        NODE(Compare) \
        NODE(Struct) \
        NODE(Not) \
        NODE(AddSub) \
        NODE(DivStar) \
        NODE(Asignment) \
        NODE(Return) \
        NODE(Reade) \
        NODE(Readc) \
        NODE(Prog) \
        NODE(TypesVars) \
        NODE(Type) \
        NODE(DeclChamps) \
        NODE(Declarateurs) \
        NODE(DeclFoncts) \
        NODE(DeclFonct) \
        NODE(EnTeteFonct) \
        NODE(Parametres) \
        NODE(ListTypVar) \
        NODE(Corps) \
        NODE(DeclVars) \
        NODE(SuiteInstr) \
        NODE(Instr) \
        NODE(Exp) \
        NODE(TB) \
        NODE(FB) \
        NODE(M) \
        NODE(E) \
        NODE(T) \
        NODE(F) \
        NODE(LValue) \
        NODE(Arguments) \
        NODE(ListExp)

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

typedef enum {
    FOREACH_NODE(GENERATE_ENUM)
    /* and allother node labels */
    /* The list must coincide with the strings in abstract-tree.c */
    /* To avoid listing them twice, see https://stackoverflow.com/a/10966395 */
} Kind;

typedef struct Node {
    Kind kind;
    union {
        int integer;
        char character;
        char identifier[64];
        SymbolTable symbol_tab;
    } u;
    struct Node *firstChild, *nextSibling;
    int lineno;
} Node;

Node *makeNode(Kind kind);
void addSibling(Node *node, Node *sibling);
void addChild(Node *parent, Node *child);
void deleteTree(Node *node);
void printTree(Node *node);
void printTables(Node *node);
void make_Symbole_table(Node *node);
void addType(Node *node, SymbolTable * table, const char name[]);
void readSemanticError(Node *node);

#define FIRSTCHILD(node) node->firstChild
#define SECONDCHILD(node) node->firstChild->nextSibling
#define THIRDCHILD(node) node->firstChild->nextSibling->nextSibling
#endif