/* decl-var.c */
/* Traduction descendante récursive des déclarations de variables en C */
/* Compatible avec decl-var.lex */
#include "decl-var.h"

#define MAXSYMBOLS 256

void initialisation_Table(SymbolTable *table, char* name, SymbolTable* parent) {

    table->array = NULL;
    strcpy(table->name, name);
    table->parent = parent;
}

void Print_table(SymbolTable table) {
    TableEntry * current;

    current = table.array;

    printf("%s :\n", table.name);
    while (current != NULL) {
        printf("\t%s %s\n", current->type, current->identifier);
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

int addVar(SymbolTable * table, const char name[], char *type) {
    TableEntry * new;
    int res = 0;

    if (checkTable(table, name)) {
        fprintf(stderr, "Warning : redefinition de la variable %s\n", name);
        res = 2;
    }

    if (NULL == (new = (TableEntry *)malloc(sizeof(TableEntry)))) {
        perror("malloc");
        exit(3);
    }

    new->next = table->array;
    table->array = new;

    strcpy(table->array->identifier, name);
    strcpy(table->array->type, type);

    return res;
}