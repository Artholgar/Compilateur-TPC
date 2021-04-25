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
    Node *node = malloc(sizeof(Node));
    if (!node) {
        printf("Run out of memory\n");
        exit(1);
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
        case DeclFonct:
        case Prog:
            printf(": ");
            if (NULL != node->u.symbol_tab.parent) {
                printf("%s ", node->u.symbol_tab.parent->name);
            }
            printf("%s", node->u.symbol_tab.name);
            Print_table(node->u.symbol_tab);
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

// void make_glob_table_aux(Node *node, SymbolTable *table) {
//     char type[MAXNAME];

//     if (NULL == node) {
//         return;
//     }

//     switch (node->kind) {
//         case Prog:
//             initialisation_Table(table);
//             strcpy(table->name, "Global");
//             make_glob_table_aux(node->firstChild, table);
//             make_glob_table_aux(node->firstChild->nextSibling, table);
//             break;
//         case TypesVars:
//             make_glob_table_aux(node->firstChild, table);
//             break;
//         case Type:
//             strcpy(type, node->u.identifier);
//             for (Node *child = node->firstChild; child != NULL && (child->kind == Identifier);
//                  child = child->nextSibling) {
//                 addVar(*table, child->u.identifier, type);
//             }
//             make_glob_table_aux(node->nextSibling, table);
//             break;
//         case DeclFonct:
//             make_glob_table_aux(node->firstChild, table);
//             //make_glob_table_aux(node->nextSibling, table);
//         case Struct:
//             strcpy(type, node->u.identifier);
//             if (node->firstChild->kind == DeclChamps) {
//                 make_glob_table_aux(node->nextSibling, table);
//                 break;
//             }

//             for (Node *child = node->firstChild; child != NULL && (child->kind == Identifier);
//                  child = child->nextSibling) {
//                 addVar(*table, child->u.identifier, type);
//             }
//             make_glob_table_aux(node->nextSibling, table);

//         default:
//             break;
//     }
// }

// void make_glob_table(Node *node) {
//     make_glob_table_aux(node, &node->u.symbol_tab);
// }

// void make_local_table_aux(Node *node, SymbolTable *table) {
//     char type[MAXNAME];

//     if (NULL == node) {
//         return;
//     }

//     switch (node->kind) {
//         case DeclFonct:
//             initialisation_Table(table);
//             strcpy(table->name, node->firstChild->firstChild->u.identifier);
//             make_local_table_aux(node->firstChild->firstChild->nextSibling, table);
//             make_local_table_aux(node->firstChild->nextSibling, table);
//             break;
//         case Parametres:
//             make_local_table_aux(node->firstChild, table);
//             break;
//         case Corps:
//             make_local_table_aux(node->firstChild, table);
//             break;
//         case Type:
//             strcpy(type, node->u.identifier);
//             for (Node *child = node->firstChild; child != NULL && child->kind == Identifier;
//                  child = child->nextSibling) {
//                 addVar(*table, child->u.identifier, type);
//             }
//             make_local_table_aux(node->nextSibling, table);
//             break;
//         case DeclVars:
//             make_local_table_aux(node->firstChild, table);
//         case Struct:
//             strcpy(type, node->u.identifier);

//             for (Node *child = node->firstChild; child != NULL && (child->kind == Identifier);
//                  child = child->nextSibling) {
//                 addVar(*table, child->u.identifier, type);
//             }
//             make_local_table_aux(node->nextSibling, table);
//         default:
//             break;
//     }
// }

// void make_local_table(Node *node) {
//     SymbolTable** tab_glob;

//     for (Node *child = node->firstChild->nextSibling; child != NULL && child->kind == DeclFonct; child = child->nextSibling) {
//         // Set the parent table
//         tab_glob = &child->u.symbol_tab.parent;
//         *tab_glob = &node->u.symbol_tab;
//         // Make the table
//         make_local_table_aux(child, &child->u.symbol_tab);
//     }
// }

void make_table_aux(Node *node, SymbolTable *table) {
    char type[MAXNAME];

    if (NULL == node) {
        return;
    }

    switch (node->kind) {
        case Prog:
            initialisation_Table(table);
            strcpy(table->name, "Global");
            make_table_aux(node->firstChild, table);
            make_table_aux(node->firstChild->nextSibling, table);
            break;
        
        case TypesVars:
            make_table_aux(node->firstChild, table);
            break;
        case Type:
            strcpy(type, node->u.identifier);
            for (Node *child = node->firstChild; child != NULL && (child->kind == Identifier);
                 child = child->nextSibling) {
                addVar(table, child->u.identifier, type);
            }
            make_table_aux(node->nextSibling, table);
            break;
        case DeclFonct:
            make_table_aux(node->firstChild, table);
            initialisation_Table(&node->u.symbol_tab);
            /*node->u.symbol_tab.parent = *table;*/
            strcpy(node->u.symbol_tab.name, node->firstChild->firstChild->u.identifier);
            make_table_aux(node->firstChild->firstChild->nextSibling, &node->u.symbol_tab);
            make_table_aux(node->firstChild->nextSibling->firstChild, &node->u.symbol_tab);
           
            make_table_aux(node->nextSibling, table);
            break;
        
        case DeclVars:
            make_table_aux(node->firstChild, table);
            break;

        case Parametres:
            make_table_aux(node->firstChild, table) ;
            break;

        case Struct:
            strcpy(type, node->u.identifier);
            if (node->firstChild->kind == DeclChamps) {
                make_table_aux(node->nextSibling, table);
                break;
            }

            for (Node *child = node->firstChild; child != NULL && (child->kind == Identifier);
                 child = child->nextSibling) {
                addVar(table, child->u.identifier, type);
            }
            make_table_aux(node->nextSibling, table);
            break;

        default:
            break;
    }
}

void make_Symbole_table(Node *node) {
    make_table_aux(node, &node->u.symbol_tab);
}
