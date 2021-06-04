#ifndef __TRAD__
#define __TRAD__

#include "decl-var.h"
#include "abstract-tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    not_register,
    rdi,
    rsi,
    rdx,
    rcx,
    r8,
    r9
} registre;

int trad_to_nasm(char* name, Node* node);

FILE* create_nasm_file(char* name);

void close_nasm_file(FILE* file);

int trad_struct(FILE* file, TableType* types);

int trad_bss(FILE* file, SymbolTable symb_tab);

int trad_instr(FILE* file, Node* node, SymbolTable* table);

int trad_text(FILE* file, Node* node);

#endif