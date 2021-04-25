/* decl-var.h */
#ifndef __DECL_VAR__
#define __DECL_VAR__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNAME 32

typedef struct {
    char identifier[MAXNAME];
    char type[MAXNAME];
    size_t offset;  // Offset in bytes.
} TableEntry;

typedef struct SymbolTable {
    TableEntry *array;
    int stsize;
    char name[MAXNAME];
    struct SymbolTable *parent;
} SymbolTable;

void initialisation_Table(SymbolTable *table);

void Print_table(SymbolTable table);

void addVar(SymbolTable * table, const char name[], char* type);
#endif