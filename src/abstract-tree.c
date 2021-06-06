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
    printf("%s - %d", StringFromKind[node->kind], node->lineno);
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
        case Equals:
        case Compare:
        case Struct:
        case Func:
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

void addFunc(Node *node, SymbolTable *table) {
    Node *current_param;
    TableFunc *new;
    TableType *new_type;
    TableChamp *new_champ;
    char name[MAXNAME];
    char type[MAXNAME];

    strcpy(name, node->firstChild->firstChild->u.identifier);
    strcpy(type, node->firstChild->u.identifier);

    if (checkFunc(NULL, table, name)) {
        fprintf(stderr, "Error : the function %s already exist\n", name);
        exit(2);
    }

    if (NULL == (new = (TableFunc *)malloc(sizeof(TableFunc)))) {
        perror("malloc");
        exit(3);
    }

    new->next = table->func;
    table->func = new;

    strcpy(table->func->name, name);
    strcpy(table->func->type, type);

    if (strcmp(type, "int") == 0) {
        new->size = 4;
    } else if (strcmp(type, "char") == 0) {
        new->size = 1;
    } else if (strcmp(type, "void") == 0) {
        new->size = 0;
    } else {
        if (checkType(&new_type, table, type) == 1) {
            new->size = new_type->size;
        } else {
            fprintf(stderr, "Error : unknown type %s\n", type);
            exit(2);
            //le type de la fonction n'existe pas
        }
    }

    // current_param = node->firstChild->firstChild->nextSibling->firstChild;

    // while (current_param != NULL) {
    //     if (NULL == (new_champ = (TableChamp *)malloc(sizeof(TableChamp)))) {
    //         perror("malloc");
    //         exit(3);
    //     }
    //     strcpy(new_champ->name, current_param->firstChild->u.identifier);
    //     strcpy(new_champ->type, current_param->u.identifier);

    //     current_param = current_param->nextSibling;
    // }
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
            } else if (strcmp(node->firstChild->u.identifier, "void") == 0) {
                strcpy(type, "void");
            } else {
                strcpy(type, "struct ");
                strcat(type, node->firstChild->u.identifier);
            }

            addFunc(node, table);
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
    // alignement mémoire pour la fin de la struct
    if (table->types->size % max != 0) {
        table->types->size += max - (table->types->size % max);
    }
}

int researchValueReturn(SymbolTable *table, char *name, char type[MAXNAME]) {
    TableFunc *current;

    if (table == NULL) {
        return 0;
    }

    current = table->func;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            strcpy(type, current->type);
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int researchMain(SymbolTable *table) {
    TableFunc *current;

    if (table == NULL) {
        return 0;
    }

    current = table->func;

    while (current != NULL) {
        if (strcmp(current->name, "main") == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int researchVar(SymbolTable *symbol_tab, char *name, char var[MAXNAME]) {
    TableEntry *current;
    if (symbol_tab == NULL) {
        return 0;
    }

    if (researchVar(symbol_tab->parent, name, var)) {
        return 1;
    }

    current = symbol_tab->array;

    while (current != NULL) {
        if (strcmp(current->identifier, name) == 0) {
            strcpy(var, current->type);
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int TestType(Node *node, SymbolTable *symbol_tab, char var[MAXNAME], char type[MAXNAME]) {
    TableType *current;
    TableChamp *tmp;

    current = symbol_tab->parent->types;

    while (current != NULL) {
        if (strcmp(current->name, var) == 0) {
            tmp = current->champs;
            while (tmp != NULL) {
                if (strcmp(tmp->name, node->u.identifier) == 0) {
                    strcpy(type, tmp->type);
                    return 1;
                }
                tmp = tmp->next;
            }
            fprintf(stderr, "Semantic Error : the field of struct doesn't exist\n");
            exit(2);
        }
        current = current->next;
    }
    return 0;
}

int reasearchType(Node *fils, Node *frere, SymbolTable *symbol_tab, char var[MAXNAME]) {
    char type[MAXNAME];

    if (researchVar(symbol_tab, fils->u.identifier, type) == 0) {
        fprintf(stderr, "Semantic Error : the variable doesn't exist \n");
        exit(2);
    }
    printf("le type est %s\n", type);

    if (TestType(frere, symbol_tab, type, var) == 0) {
        fprintf(stderr, "Semantic Error : the variable doesn't exist 5\n");
        exit(2);
    }
    return 0;
}

int TestVar(Node *node, SymbolTable symbol_tab, char var[MAXNAME]) {
    char tmp[MAXNAME] = "";

    if (NULL == node)
        return 0;

    switch (node->kind) {
        case Identifier:

            if (node->firstChild != NULL) {
                reasearchType(node, node->firstChild, &symbol_tab, tmp);
            }

            else {
                if (researchVar(&symbol_tab, node->u.identifier, tmp) == 0) {
                    fprintf(stderr, "Semantic Error : the variable isn't exist 2\n");
                    exit(2);
                }
            }

            if (strcmp(var, "int") == 0) {
                if (strcmp(tmp, "char") != 0 && strcmp(tmp, "int") != 0) {
                    fprintf(stderr, "Semantic Error : the variable can't be affect\n");
                    exit(2);
                }
            }

            else if (strcmp(var, "char") == 0) {
                if (strcmp(tmp, "int") == 0)
                    fprintf(stderr, "Warning : you affect char for a int1\n");
                if (strcmp(tmp, "char") != 0 && strcmp(tmp, "int") != 0) {
                    fprintf(stderr, "Semantic Error : the variable can't be affect\n");
                    exit(2);
                }
            } else {
                printf("tmp %s var %s\n", tmp, var);
                if (strcmp(tmp, var) != 0) {
                    fprintf(stderr, "Semantic Error : the variable can't be affect\n");
                    exit(2);
                }
            }
            break;

        case Equals:
        case Compare:
        case AddSub:
        case DivStar:
            TestVar(node->firstChild, symbol_tab, var);
            TestVar(node->firstChild->nextSibling, symbol_tab, var);
            break;

        case IntLiteral:
            if (strcmp(var, "char") == 0)
                fprintf(stderr, "Warning : you affect char for a int1\n");

        case CharLiteral:
            if (strcmp(var, "char") != 0 && strcmp(var, "int") != 0) {
                fprintf(stderr, "Semantic Error : the variable can't be affect\n");
                exit(2);
            }
            break;

        default:
            break;
    }
    return 0;
}

void SemanticErrorAux(Node *node, SymbolTable symbol_tab) {
    char var[MAXNAME];

    if (NULL == node) {
        return;
    }

    switch (node->kind) {
        case Corps:
            SemanticErrorAux(node->firstChild->nextSibling, symbol_tab);  //rentre dans SuiteInstr
            break;

        case SuiteInstr:
            for (Node *child = node->firstChild; child != NULL; child = child->nextSibling) {
                SemanticErrorAux(child, symbol_tab);
            }
            break;

        case Asignment:
            printf("ident %s\n", node->firstChild->u.identifier);
            if (node->firstChild->firstChild != NULL) {
                reasearchType(node->firstChild, node->firstChild->firstChild, &symbol_tab, var);
            }

            else if (node->firstChild->kind == IntLiteral)
                strcpy(var, "int");

            else if (node->firstChild->kind == CharLiteral)
                strcpy(var, "char");
            else {
                if (researchVar(&symbol_tab, node->firstChild->u.identifier, var) == 0) {
                    fprintf(stderr, "Semantic Error : the variable isn't exist 1\n");
                    exit(EXIT_FAILURE);
                }
            }

            printf("la valeur assigné est %s\n", var);
            TestVar(node->firstChild->nextSibling, symbol_tab, var);
            break;

        case Equals:
        case Compare:
        case If:
        case While:
        case Or:
        case And:
        case AddSub:
        case DivStar:
            SemanticErrorAux(node->firstChild, symbol_tab);
            SemanticErrorAux(node->firstChild->nextSibling, symbol_tab);
            break;

        case Identifier:
            printf("ident %s  seul\n", node->u.identifier);
            if (node->firstChild != NULL) {
                reasearchType(node, node->firstChild, &symbol_tab, var);
            }

            else {
                if (researchVar(&symbol_tab, node->u.identifier, var) == 0) {
                    fprintf(stderr, "Semantic Error : the variable isn't exist 1\n");
                    exit(2);
                }
            }

            if (strcmp(var, "char") != 0 && strcmp(var, "int") != 0) {
                fprintf(stderr, "Semantic Error : the variable can't be affect\n");
                exit(2);
            }

            break;

        case Return:
            if (researchValueReturn(symbol_tab.parent, symbol_tab.name, var) == 0) {
                fprintf(stderr, "Semantic Error : the function isn't exist\n");
                exit(2);
            }

            if (strcmp(symbol_tab.name, "main") == 0 && strcmp(var, "int") != 0) {
                fprintf(stderr, "Semantic Error : the function main must return integer\n");
                exit(2);
            }

            TestVar(node->firstChild, symbol_tab, var);
            break;

        case Readc:  //lit un caractere
            if (node->firstChild->firstChild != NULL) {
                reasearchType(node->firstChild, node->firstChild->firstChild, &symbol_tab, var);
            }

            else {
                if (researchVar(&symbol_tab, node->firstChild->u.identifier, var) == 0) {
                    fprintf(stderr, "Semantic Error : the variable isn't exist 1\n");
                    exit(2);
                }
            }

            if (strcmp(var, "char") != 0 && strcmp(var, "int") != 0) {
                fprintf(stderr, "Semantic Error : the variable can't be affect\n");
                exit(2);
            }
            break;

        case Print:
        case Else:
            SemanticErrorAux(node->firstChild, symbol_tab);
            break;

        case Reade:  //lit un entier
            if (node->firstChild->firstChild != NULL) {
                reasearchType(node->firstChild, node->firstChild->firstChild, &symbol_tab, var);
            }

            else {
                if (researchVar(&symbol_tab, node->firstChild->u.identifier, var) == 0) {
                    fprintf(stderr, "Semantic Error : the variable isn't exist 1\n");
                    exit(2);
                }
            }

            if (strcmp(var, "char") == 0)
                fprintf(stderr, "Warning : you affect char for a int\n");

            if (strcmp(var, "char") != 0 && strcmp(var, "int") != 0) {
                fprintf(stderr, "Semantic Error : the variable can't be affect\n");
                exit(2);
            }
            break;

        case Func:
            for (Node *child = node->firstChild; child != NULL; child = child->nextSibling) {
                SemanticErrorAux(child, symbol_tab);
            }
            break;

        case IntLiteral:
        case CharLiteral:
        case Type:
        case Struct:
        default:
            break;
    }
}

int searchReturn(Node *node) {
    int tmp1, tmp2, tmp3;
    if (node == NULL) {
        return 0;
    }

    switch (node->kind) {
        case SuiteInstr:
            return searchReturn(node->firstChild);
        case If:
            tmp1 = searchReturn(node->firstChild->nextSibling);
            tmp2 = searchReturn(node->firstChild->nextSibling->nextSibling);
            tmp3 = searchReturn(node->nextSibling);
            return (tmp1 && tmp2) || tmp3;
            break;
        case Return:
            return 1;
            break;
        default:
            return searchReturn(node->nextSibling);
            break;
    }
}

int SemanticErrorAux2(Node *node, SymbolTable *symbol_tab) {
    int tmp1, tmp2;
    TableType *type;
    TableEntry *entry;
    TableChamp *champ;
    TableFunc *func;

    if (NULL == node) {
        return 0;
    }

    switch (node->kind) {
        case Corps:
            SemanticErrorAux2(node->firstChild->nextSibling, symbol_tab);  //rentre dans SuiteInstr
            break;

        case SuiteInstr:
            for (Node *child = node->firstChild; child != NULL; child = child->nextSibling) {
                SemanticErrorAux2(child, symbol_tab);
            }
            break;

        case Asignment:
            printf("assi ident %s\n", node->firstChild->u.identifier);
            tmp1 = SemanticErrorAux2(node->firstChild, symbol_tab);
            tmp2 = SemanticErrorAux2(node->firstChild->nextSibling, symbol_tab);
            printf("%d %d\n", tmp1, tmp2);
            if (tmp1 != tmp2) {
                if (tmp1 == 1 && tmp2 == 4) {
                    fprintf(stderr, "Warning : assignement from an int to a char, line %d\n", node->lineno);
                } else if (!(tmp1 == 4 && tmp2 == 1)) {
                    fprintf(stderr, "Error : incompatible types, line %d\n", node->lineno);
                    exit(0);
                }
            }

            // if (node->firstChild->firstChild != NULL) {
            //     reasearchType(node->firstChild, node->firstChild->firstChild, &symbol_tab, var);
            // }

            // else if (node->firstChild->kind == IntLiteral)
            //     strcpy(var, "int");

            // else if (node->firstChild->kind == CharLiteral)
            //     strcpy(var, "char");
            // else {
            //     if (researchVar(&symbol_tab, node->firstChild->u.identifier, var) == 0) {
            //         fprintf(stderr, "Semantic Error : the variable isn't exist 1\n");
            //         exit(EXIT_FAILURE);
            //     }
            // }

            // printf("la valeur assigné est %s\n", var);
            // TestVar(node->firstChild->nextSibling, *symbol_tab, var);
            break;

        case Equals:
        case Compare:
        case Or:
        case And:
        case AddSub:
        case DivStar:
            tmp1 = SemanticErrorAux2(node->firstChild, symbol_tab);
            tmp2 = SemanticErrorAux2(node->firstChild->nextSibling, symbol_tab);

            if (tmp1 == 1) {
                tmp1 = 4;
            }
            if (tmp2 == 1) {
                tmp2 = 4;
            }
            if (tmp1 > 4 || tmp2 > 4) {
                fprintf(stderr, "Error : incompatible types for %s operator, line %d\n", node->u.identifier, node->lineno);
                exit(2);
            }
            return (tmp1 > tmp2) ? tmp1 : tmp2;
            break;

        case If:
        case While:
            SemanticErrorAux2(node->firstChild, symbol_tab);
            SemanticErrorAux2(node->firstChild->nextSibling, symbol_tab);
            break;
        case Identifier:
            printf("ident %s  seul\n", node->u.identifier);
            printf("%s\n", node->u.identifier);
            if (checkTable(&entry, symbol_tab, node->u.identifier)) {
                printf("%s\n", entry->type);
                if (strcmp(entry->type, "int") == 0) {
                    return 4;
                }
                if (strcmp(entry->type, "char") == 0) {
                    return 1;
                }
                if (checkType(&type, symbol_tab, entry->type)) {
                    if (node->firstChild != NULL) {
                        if (checkChamp(&champ, type, node->firstChild->u.identifier)) {
                            return champ->size;
                        } else {
                            fprintf(stderr, "Error : type %s doesn't have field %s, line %d\n", type->name, node->firstChild->u.identifier, node->lineno);
                            exit(2);
                        }
                    }
                    return type->size;
                }
            } else {
                fprintf(stderr, "Error : unknown variable %s, line %d\n", node->u.identifier, node->lineno);
                exit(2);
            }
            // if (node->firstChild != NULL) {
            //     reasearchType(node, node->firstChild, symbol_tab, var);
            // }

            // else {
            //     if (researchVar(symbol_tab, node->u.identifier, var) == 0) {
            //         fprintf(stderr, "Semantic Error : the variable isn't exist 1\n");
            //         exit(2);
            //     }
            // }

            // if (strcmp(var, "char") != 0 && strcmp(var, "int") != 0) {
            //     fprintf(stderr, "Semantic Error : the variable can't be affect\n");
            //     exit(2);
            // }

            break;

        case Return:
            printf("lala\n");
            checkFunc(&func, symbol_tab, symbol_tab->name);
            tmp1 = SemanticErrorAux2(node->firstChild, symbol_tab);
            printf("%d\n", func->size);

            if (tmp1 != func->size) {
                if (tmp1 == 1 && func->size == 4) {
                    fprintf(stderr, "Warning : assignement from an int to a char, line %d\n", node->lineno);
                } else if (!(tmp1 == 4 && func->size == 1)) {
                    fprintf(stderr, "Error : invalid return type, expected %s, line %d\n", func->type, node->lineno);
                    exit(2);
                }
            }
            // if (researchValueReturn(symbol_tab->parent, symbol_tab->name, var) == 0) {
            //     fprintf(stderr, "Semantic Error : the function isn't exist\n");
            //     exit(2);
            // }

            // if (strcmp(symbol_tab->name, "main") == 0 && strcmp(var, "int") != 0) {
            //     fprintf(stderr, "Semantic Error : the function main must return integer\n");
            //     exit(2);
            // }

            // TestVar(node->firstChild, *symbol_tab, var);
            break;

        case Readc:  //lit un caractere
            tmp1 = SemanticErrorAux2(node->firstChild, symbol_tab);

            if (tmp1 == 4) {
                fprintf(stderr, "Warning : assignement from an int to a char, line %d\n", node->lineno);
            } else if (tmp1 != 1) {
                fprintf(stderr, "Error : invalid return type, expected char, line %d\n", node->lineno);
                exit(2);
            }
            // if (node->firstChild->firstChild != NULL) {
            //     reasearchType(node->firstChild, node->firstChild->firstChild, symbol_tab, var);
            // }

            // else {
            //     if (researchVar(symbol_tab, node->firstChild->u.identifier, var) == 0) {
            //         fprintf(stderr, "Semantic Error : the variable isn't exist 1\n");
            //         exit(2);
            //     }
            // }

            // if (strcmp(var, "char") != 0 && strcmp(var, "int") != 0) {
            //     fprintf(stderr, "Semantic Error : the variable can't be affect\n");
            //     exit(2);
            // }
            break;

        case Print:
        case Else:
            SemanticErrorAux2(node->firstChild, symbol_tab);
            break;

        case Reade:  //lit un entier
            tmp1 = SemanticErrorAux2(node->firstChild, symbol_tab);

            if (tmp1 > 4) {
                fprintf(stderr, "Error : invalid return type, expected char, line %d\n", node->lineno);
                exit(2);
            }
            // if (node->firstChild->firstChild != NULL) {
            //     reasearchType(node->firstChild, node->firstChild->firstChild, symbol_tab, var);
            // }

            // else {
            //     if (researchVar(symbol_tab, node->firstChild->u.identifier, var) == 0) {
            //         fprintf(stderr, "Semantic Error : the variable isn't exist 1\n");
            //         exit(2);
            //     }
            // }

            // if (strcmp(var, "char") == 0)
            //     fprintf(stderr, "Warning : you affect char for a int\n");

            // if (strcmp(var, "char") != 0 && strcmp(var, "int") != 0) {
            //     fprintf(stderr, "Semantic Error : the variable can't be affect\n");
            //     exit(2);
            // }
            break;

        case Func:
            if (checkFunc(&func, symbol_tab, node->u.identifier)) {
                return func->size;
            } else {
                fprintf(stderr, "Error : unknown function %s, line %d\n", node->u.identifier, node->lineno);
                exit(2);
            }

            // for (Node *child = node->firstChild; child != NULL; child = child->nextSibling) {
            //     SemanticErrorAux2(child, symbol_tab);
            // }
            break;

        case IntLiteral:
            return 4;
        case CharLiteral:
            return 1;
        case Type:
        case Struct:
        default:
            break;
    }
    return 0;
}

// void remplisParam(SymbolTablenode->u.symbol_tab->parent, node->u.symbol_tab){

// }

void readSemanticError(Node *node) {
    if (NULL == node) {
        return;
    }

    switch (node->kind) {
        case Prog:
            if (researchMain(&(node->u.symbol_tab)) == 0) {
                fprintf(stderr, "Error : main function must be defined\n");
                exit(EXIT_FAILURE);
            }
            readSemanticError(node->firstChild->nextSibling);
            break;

        case DeclFonct:
            if ((!searchReturn(node->firstChild->nextSibling->firstChild->nextSibling)) && strcmp(node->firstChild->u.identifier, "void") != 0) {
                fprintf(stderr, "Error : control reach end of non-void function, line %d\n", node->lineno);
                exit(2);
            }
            SemanticErrorAux2(node->firstChild->nextSibling, &(node->u.symbol_tab));  //va directement a corp
            printf("première fonction\n");
            readSemanticError(node->nextSibling);  //plusieurs fonction
            break;

        default:
            break;
    }
}