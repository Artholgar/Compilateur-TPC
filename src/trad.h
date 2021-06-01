#ifndef __TRAD__
#define __TRAD__

#include "decl-var.h"
#include "abstract-tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int trad_to_nasm(char* name, Node* node);

FILE* create_nasm_file(char* name);

void close_nasm_file(FILE* file);

int trad_struct(FILE* file, TableType* types);

#endif