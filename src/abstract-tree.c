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

    if (NULL == (node = (Node *)malloc(sizeof(Node)))) {
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
            if (node->u.character == '\n') {
                printf(": '\\n'");
            } else {
                printf(": '%c'", node->u.character);
            }
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

void make_table_aux(Node *node, SymbolTable *table, Kind_Val kind) {
    char type[MAXNAME];

    if (NULL == node) {
        return;
    }

    switch (node->kind) {
        case Prog:
            initialisation_Table(table, "Global", NULL);
            make_table_aux(node->firstChild, table, kind);
            make_table_aux(node->firstChild->nextSibling, table, kind);
            break;

        case TypesVars:
            make_table_aux(node->firstChild, table, Variable);
            break;
        case Type:
            strcpy(type, node->u.identifier);
            for (Node *child = node->firstChild; child != NULL && (child->kind == Identifier);
                 child = child->nextSibling) {
                addVar(table, child->u.identifier, type, kind);
            }
            make_table_aux(node->nextSibling, table, kind);
            break;
        case DeclFonct:
            if (strcmp(node->firstChild->u.identifier, "int") == 0) {
                strcpy(type, "int");
            } else if (strcmp(node->firstChild->u.identifier, "char") == 0) {
                strcpy(type, "char");
            } else {
                strcpy(type, "struct ");
                strcat(type, node->firstChild->u.identifier);
            }

            addFunc(table, node->firstChild->firstChild->u.identifier, type);
            // make_table_aux(node->firstChild, table, Function);
            initialisation_Table(&node->u.symbol_tab, node->firstChild->firstChild->u.identifier, table);
            strcpy(node->u.symbol_tab.name, node->firstChild->firstChild->u.identifier);
            make_table_aux(node->firstChild->firstChild->nextSibling, &node->u.symbol_tab, Parameter);
            make_table_aux(node->firstChild->nextSibling->firstChild, &node->u.symbol_tab, Variable);

            make_table_aux(node->nextSibling, table, kind);
            break;

        case DeclVars:
            make_table_aux(node->firstChild, table, Variable);
            break;

        case Parametres:
            make_table_aux(node->firstChild, table, Parameter);
            break;

        case Struct:
            strcpy(type, "struct ");
            strcat(type, node->u.identifier);
            if (node->firstChild->kind == DeclChamps) {
                addType(node, table, type);
                make_table_aux(node->nextSibling, table, kind);
                break;
            }

            for (Node *child = node->firstChild; child != NULL && (child->kind == Identifier);
                 child = child->nextSibling) {
                addVar(table, child->u.identifier, type, kind);
            }
            make_table_aux(node->nextSibling, table, kind);
            break;

        default:
            break;
    }
}

void make_Symbole_table(Node *node) {
    make_table_aux(node, &node->u.symbol_tab, Variable);
}

void addType(Node *node, SymbolTable *table, const char name[]) {
    TableType *new;
    Node *current;
    TableChamp *champ, *tmp;
    size_t max = 0;

    if (NULL == (new = (TableType *)malloc(sizeof(TableType)))) {
        perror("malloc");
        exit(3);
    }

    new->next = table->types;
    table->types = new;

    strcpy(table->types->name, name);
    table->types->champs = NULL;
    table->types->size = 0;

    current = node->firstChild->firstChild;

    while (current != NULL) {
        if (NULL == (champ = (TableChamp *)malloc(sizeof(TableChamp)))) {
            perror("malloc");
            exit(3);
        }
        strcpy(champ->name, current->firstChild->u.identifier);

        strcpy(champ->type, current->u.identifier);

        // type du champ
        if (strcmp(champ->type, "int") == 0) {
            champ->size = 4;
        } else {
            champ->size = 1;
        }

        // incrémentation de la taille de la struct avec l'alignement mémoire
        table->types->size += champ->size + (table->types->size % champ->size);

        tmp = table->types->champs;

        if (tmp != NULL) {
            while (tmp->next != NULL) {
                tmp = tmp->next;
            }
            tmp->next = champ;
        } else {
            table->types->champs = champ;
        }
        if (champ->size > max) {
            max = champ->size;
        }
        current = current->nextSibling;
    }
    printf("%d\n", max);
    printf("%d\n", table->types->size);
    if (table->types->size % max != 0) {
        table->types->size += max - (table->types->size % max);
    }
}
