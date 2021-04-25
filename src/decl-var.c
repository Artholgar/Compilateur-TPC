/* decl-var.c */
/* Traduction descendante récursive des déclarations de variables en C */
/* Compatible avec decl-var.lex */
#include "decl-var.h"

#define MAXSYMBOLS 256

void initialisation_Table(SymbolTable *table) {

    if (NULL == (table->array = (TableEntry *)malloc(MAXSYMBOLS * sizeof(TableEntry)))) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    table->stsize = 0;
}

void Print_table(SymbolTable table) {
    int i = 0;
    printf("[");
    printf("%s %s", table.array[i].type, table.array[i].identifier);
    for (i = 1; i < table.stsize; i++) {
        printf(", %s %s", table.array[i].type, table.array[i].identifier);
    }
    printf("]");
}

void addVar(SymbolTable * table, const char name[], char *type) {
    int count;
    for (count = 0; count < table->stsize; count++) {
        if (!strcmp(table->array[count].identifier, name)) {
            printf("semantic error, redefinition of variable %s\n",
                   name);
            return;
        }
    }
    if (++(table->stsize) > MAXSYMBOLS) {
        printf("too many variables\n");
        exit(1);
    }

    strcpy(table->array[table->stsize - 1].identifier, name);
    strcpy(table->array[table->stsize - 1].type, type);
}