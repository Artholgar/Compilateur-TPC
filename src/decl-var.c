/* decl-var.c */
/* Traduction descendante récursive des déclarations de variables en C */
/* Compatible avec decl-var.lex */
#include "decl-var.h"

#define MAXSYMBOLS 256

void initialisation_Table(SymbolTable *table, char* name, SymbolTable* parent) {

    table->array = NULL;
    table->types = NULL;
    strcpy(table->name, name);
    table->parent = parent;
    table->stsize = 0;
}

void Print_table(SymbolTable table) {
    TableEntry * current;
    TableType * current_type;

    current = table.array;

    current_type = table.types;

    if (current_type != NULL) {
        printf("Types :\n");
    }

    while (current_type != NULL) {

        printf("\t%s\n", current_type->name);
        current_type = current_type->next;
    }

    printf("%s :\n", table.name);
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

int checkTable(SymbolTable * table, const char name[]) {
    TableEntry * current;

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

void addVar(SymbolTable * table, const char name[], char *type, Kind_Val kind) {
    TableEntry * new;

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
    new->offset = - table->stsize;

    if (strcmp(type, "int") == 0) {
        table->stsize += 4;
    }
}

void addType(SymbolTable * table, const char name[]) {
    TableType * new;

    if (NULL == (new = (TableType *)malloc(sizeof(TableType)))) {
        perror("malloc");
        exit(3);
    }

    new->next = table->types;
    table->types = new;

    strcpy(table->types->name, name);
    table->types->champs = NULL;

    if (strcmp(name, "int") == 0) {
        table->stsize += 4;
    }
}