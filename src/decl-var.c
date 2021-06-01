/* decl-var.c */
/* Traduction descendante récursive des déclarations de variables en C */
/* Compatible avec decl-var.lex */
#include "decl-var.h"

void initialisation_Table(SymbolTable *table, char *name, SymbolTable *parent) {
    table->array = NULL;
    table->types = NULL;
    strcpy(table->name, name);
    table->parent = parent;
    table->stsize = 0;
}

void Print_table(SymbolTable table) {
    TableEntry *current;
    TableType *current_type;
    TableFunc *current_func;

    current = table.array;

    current_type = table.types;

    current_func = table.func;

    if (current_type != NULL) {
        printf("Types :\n");
    }

    while (current_type != NULL) {
        printf("\t%d - %s\n", current_type->size, current_type->name);
        
        for (TableChamp *current_champ = current_type->champs; current_champ != NULL; current_champ = current_champ->next) {
            printf("\t\t%s - %s\n", current_champ->type, current_champ->name);
        }
        current_type = current_type->next;
    }

    if (current_func != NULL) {
        printf("Fonctions :\n");
    }

    while (current_func != NULL) {
        printf("\t%d - %s\n", current_func->size, current_func->name);
        
        current_func = current_func->next;
    }

    printf("%s - size = %d :\n", table.name, table.stsize);
    while (current != NULL) {
        printf("\t%ld - ", current->offset);
        switch (current->kind) {
            case Variable:
                printf("Variable - ");
                break;
            case Function:
                printf("Function - ");
                break;
            case Parameter:
                printf("Parameter - ");
                break;

            default:
                break;
        }
        printf("%s %s\n", current->type, current->identifier);
        current = current->next;
    }
}

int checkTable(SymbolTable *table, const char name[]) {
    TableEntry *current;

    if (NULL == table) {
        return 0;
    }
    if (checkTable(table->parent, name)) {
        return 1;
    }
    current = table->array;

    while (current != NULL) {
        if (strcmp(current->identifier, name) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int checkType(TableType* type, SymbolTable *table, const char name[]) {
    TableType *current;

    if (NULL == table) {
        return 0;
    }
    if (checkType(type, table->parent, name)) {
        return 1;
    }
    current = table->types;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            (*type) = *current;
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void addVar(SymbolTable *table, const char name[], char *type, Kind_Val kind) {
    TableEntry *new;
    TableType new_type;

    if (checkTable(table, name)) {
        fprintf(stderr, "Error : redefinition de la variable %s\n", name);
        exit(EXIT_FAILURE);
    }

    if (NULL == (new = (TableEntry *)malloc(sizeof(TableEntry)))) {
        perror("malloc");
        exit(3);
    }

    new->next = table->array;
    table->array = new;

    strcpy(table->array->identifier, name);
    strcpy(table->array->type, type);
    table->array->kind = kind;
    new->offset = table->stsize;

    if (strcmp(type, "int") == 0) {
        table->stsize += 4;
        new->size = 4;
    }
    else if (strcmp(type, "char") == 0) {
        table->stsize += 1;
        new->size = 1;
    }
    else {
        if (checkType(&new_type, table, type) == 1) {
            table->stsize += new_type.size;
            new->size = new_type.size;
        }
        else {
            // erreur sémantique, a toi de jouer Thomas !!
            ;
        }
    }
}

void addFunc(SymbolTable *table, const char name[], char *type) {
    TableFunc *new;
    TableType new_type;

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
    }
    else if (strcmp(type, "char") == 0) {
        new->size = 1;
    }
    else {
        if (checkType(&new_type, table, type) == 1) {
            new->size = new_type.size;
        }
        else {
            // erreur sémantique, a toi de jouer Thomas !!
            ;
        }
    }
}
