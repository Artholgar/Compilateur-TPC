/* abstract-tree.c */
#include "abstract-tree.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
extern int yylineno; /* from lexer */

static const char *StringFromKind[] = {
    FOREACH_NODE(GENERATE_STRING)
    /* and all other node labels */
    /* The list must coincide with the enum in abstract-tree.h */
    /* To avoid listing them twice, see https://stackoverflow.com/a/10966395 */
};

Node *makeNode(Kind kind) {
    Node *node;

    if (NULL == (node = (Node*)malloc(sizeof(Node)))) {
        perror("malloc");
        exit(3);
    }
    node->kind = kind;
    node->firstChild = node->nextSibling = NULL;
    node->lineno = yylineno;
    return node;
}

void addSibling(Node *node, Node *sibling) {
    Node *curr = node;
    while (curr->nextSibling != NULL) {
        curr = curr->nextSibling;
    }
    curr->nextSibling = sibling;
}

void addChild(Node *parent, Node *child) {
    if (parent->firstChild == NULL) {
        parent->firstChild = child;
    } else {
        addSibling(parent->firstChild, child);
    }
}

void deleteTree(Node *node) {
    if (node->firstChild) {
        deleteTree(node->firstChild);
    }
    if (node->nextSibling) {
        deleteTree(node->nextSibling);
    }
    free(node);
}

void printTree(Node *node) {
    static bool rightmost[128];        // current node is rightmost sibling
    static int depth = 0;              // depth of current node
    for (int i = 1; i < depth; i++) {  // 2502 = vertical line
        printf(rightmost[i] ? "    " : "\u2502   ");
    }
    if (depth >
        0) {  // 2514 = up and right; 2500 = horiz; 251c = vertical and right
        printf(rightmost[depth] ? "\u2514\u2500\u2500 " : "\u251c\u2500\u2500 ");
    }
    printf("%s", StringFromKind[node->kind]);
    switch (node->kind) {
        case IntLiteral:
            printf(": %d", node->u.integer);
            break;
        case CharLiteral:
            printf(": '%c'", node->u.character);
            break;
        case Type:
        case AddSub:
        case DivStar:
        case Struct:
        case Identifier:
            printf(": %s", node->u.identifier);
            break;
        default:
            break;
    }
    printf("\n");
    depth++;
    for (Node *child = node->firstChild; child != NULL;
         child = child->nextSibling) {
        rightmost[depth] = (child->nextSibling) ? false : true;
        printTree(child);
    }
    depth--;
}

void printTables(Node *node) {
    if (NULL == node) {
        return;
    }

    switch (node->kind) {
        case Prog:
            Print_table(node->u.symbol_tab);
            printTables(node->firstChild->nextSibling);
            break;
        case DeclFonct:
            Print_table(node->u.symbol_tab);
            printTables(node->nextSibling);
            break;
        default:
            break;
    }
}

int make_table_aux(Node *node, SymbolTable *table) {
    char type[MAXNAME];
    int res = 0;

    if (NULL == node) {
        return res;
    }
    
    switch (node->kind) {
        case Prog:
            initialisation_Table(table, "Global", NULL);
            res = make_table_aux(node->firstChild, table);
            res = res || make_table_aux(node->firstChild->nextSibling, table);
            break;
        
        case TypesVars:
            res = make_table_aux(node->firstChild, table);
            break;
        case Type:
            strcpy(type, node->u.identifier);
            for (Node *child = node->firstChild; child != NULL && (child->kind == Identifier);
                 child = child->nextSibling) {
                res = res || addVar(table, child->u.identifier, type);
            }
            res = res || make_table_aux(node->nextSibling, table);
            break;
        case DeclFonct:
            res = res || make_table_aux(node->firstChild, table);
            initialisation_Table(&node->u.symbol_tab, node->firstChild->firstChild->u.identifier, table);
            strcpy(node->u.symbol_tab.name, node->firstChild->firstChild->u.identifier);
            res = res || make_table_aux(node->firstChild->firstChild->nextSibling, &node->u.symbol_tab);
            res = res || make_table_aux(node->firstChild->nextSibling->firstChild, &node->u.symbol_tab);
           
            res = res || make_table_aux(node->nextSibling, table);
            break;
        
        case DeclVars:
            res = res || make_table_aux(node->firstChild, table);
            break;

        case Parametres:
            res = res || make_table_aux(node->firstChild, table) ;
            break;

        case Struct:
            strcpy(type, "struct ");
            strcat(type, node->u.identifier);
            if (node->firstChild->kind == DeclChamps) {
                res = res || make_table_aux(node->nextSibling, table);
                break;
            }

            for (Node *child = node->firstChild; child != NULL && (child->kind == Identifier);
                 child = child->nextSibling) {
                res = res || addVar(table, child->u.identifier, type);
            }
            res = res || make_table_aux(node->nextSibling, table);
            break;

        default:
            break;
    }

    return res;
}

int make_Symbole_table(Node *node) {
    return make_table_aux(node, &node->u.symbol_tab);
}
