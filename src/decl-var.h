/* decl-var.h */
#ifndef __DECL_VAR__
#define __DECL_VAR__

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define MAXNAME 32
#define MAXSYMBOLS 256

typedef enum {
    Variable,
    Function,
    Parameter
} Kind_Val;

typedef struct entry{
    char identifier[MAXNAME];
    char type[MAXNAME];
    Kind_Val kind;
    size_t offset;  // Offset in bytes.
    size_t size;
    struct entry *next;
} TableEntry;

typedef struct champ {
    char name[MAXNAME];
    char type[MAXNAME];
    int size;
    struct champ *next;
} TableChamp;

typedef struct type {
    char name[MAXNAME];
    int size;
    struct champ * champs;
    struct type *next;
} TableType;

typedef struct func {
    char name[MAXNAME];
    char type[MAXNAME];
    int size;
    struct func *next;
} TableFunc;

typedef struct SymbolTable {
    TableEntry *array;
    TableType *types;
    TableFunc *func;
    int stsize;
    char name[MAXNAME];
    struct SymbolTable *parent;
} SymbolTable;

void initialisation_Table(SymbolTable *table, char* name, SymbolTable* parent);

void Print_table(SymbolTable table);

void addVar(SymbolTable * table, const char name[], char* type, Kind_Val kind);

void addFunc(SymbolTable *table, const char name[], char *type);


#endif