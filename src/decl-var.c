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

void addVar(SymbolTable * table, const char name[], char *type) {
    TableEntry * new;

    if (NULL == (new = (TableEntry *)malloc(sizeof(TableEntry)))) {
        perror("malloc");
        exit(3);
    }

    new->next = table->array;
    table->array = new;
    // int count;
    // for (count = 0; count < table->stsize; count++) {
    //     if (!strcmp(table->array[count].identifier, name)) {
    //         printf("semantic error, redefinition of variable %s\n",
    //                name);
    //         return;
    //     }
    // }
    // if (++(table->stsize) > MAXSYMBOLS) {
    //     printf("too many variables\n");
    //     exit(3);
    // }

    strcpy(table->array->identifier, name);
    strcpy(table->array->type, type);
}