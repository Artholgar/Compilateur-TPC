#include "trad.h"

int trad_to_nasm(char* name, Node* node) {
    FILE* file;
    file = create_nasm_file(name);
    trad_struct(file, node->u.symbol_tab.types);

    trad_bss(file, node->u.symbol_tab);

    trad_text(file, node);
    close_nasm_file(file);
    return 0;
}

FILE* create_nasm_file(char* name) {
    int i;
    FILE* file;
    if (name == NULL) {
        name = "_anonymous.asm";
    } else {
        for (i = strlen(name); name[i] != '.'; i--) {
            ;
        }

        name[i + 1] = 'a';
        name[i + 2] = 's';
        name[i + 3] = 'm';
        name[i + 4] = '\0';
    }

    if (NULL == (file = fopen(name, "w"))) {
        perror("fopen");
        exit(3);
    }

    return file;
}

void close_nasm_file(FILE* file) {
    fclose(file);
}

int trad_struct(FILE* file, TableType* types) {
    char name[MAXNAME];
    while (types != NULL) {
        strcpy(name, types->name);
        // remove 'struct ' from type name
        memmove(name, name + 7, strlen(name));
        fprintf(file, "struc %s\n", name);

        for (TableChamp* champ = types->champs; champ != NULL; champ = champ->next) {
            fprintf(file, "\t.%s resb %d\n", champ->name, champ->size);
        }
        fprintf(file, "endstruc\n");

        types = types->next;
        fprintf(file, "\n");
    }
    return 0;
}

int trad_bss(FILE* file, SymbolTable symb_tab) {
    TableEntry* current;

    fprintf(file, "section .bss\n");

    for (current = symb_tab.array; current != NULL; current = current->next) {
        fprintf(file, "\t%s resb %ld\n", current->identifier, current->size);
    }

    fprintf(file, "\n");
    return 1;
}

int trad_variable(FILE* file, Node* node, SymbolTable* table) {
    TableEntry* entry = NULL;
    TableType* type = NULL;
    TableChamp* champ = NULL;
    size_t size;
    char name[MAXNAME];

    if (checkTable(&entry, table, node->u.identifier)) {
        if (strcmp(entry->type, "int") == 0) {
            fprintf(file, "dword ");
            size = 4;
        } else if (strcmp(entry->type, "char") == 0) {
            fprintf(file, "byte ");
            size = 1;
        } else {
            if (node->firstChild != NULL) {
                checkType(&type, table, entry->type);
                checkChamp(&champ, type, node->firstChild->u.identifier);

                if (strcmp(champ->type, "int") == 0) {
                    fprintf(file, "dword ");
                    size = 4;
                } else if (strcmp(champ->type, "char") == 0) {
                    fprintf(file, "byte ");
                    size = 1;
                }
            } else {
                ;
            }
        }
        fprintf(file, "[");
        if (isGlobal(table, node->u.identifier) == 1) {
            fprintf(file, "%s", entry->identifier);
        } else {
            fprintf(file, "rbp + %ld", entry->offset);
        }
        if (NULL != champ) {
            strcpy(name, type->name);
            // remove 'struct ' from type name
            memmove(name, name + 7, strlen(name));
            fprintf(file, " + %s.%s", name, champ->name);
        }
        fprintf(file, "]");
    }

    return size;
}

int trad_text(FILE* file, Node* node) {
    TableFunc* current_func;
    Node* function;
    Node* corp;
    Node* instr;

    fprintf(file, "section .text\n");

    for (current_func = node->u.symbol_tab.func; current_func != NULL; current_func = current_func->next) {
        fprintf(file, "global %s\n", current_func->name);
    }

    for (function = node->firstChild->nextSibling; function != NULL; function = function->nextSibling) {
        fprintf(file, "\n");
        fprintf(file, "%s :\n", function->firstChild->firstChild->u.identifier);

        fprintf(file, "\tpush rbp\n\tmov rbp, rsp\n");

        fprintf(file, "\tsub rsp, %d\n", function->u.symbol_tab.stsize);

        corp = function->firstChild->nextSibling;

        for (instr = corp->firstChild->nextSibling->firstChild; instr != NULL; instr = instr->nextSibling) {
            if (instr->kind == Asignment) {
                fprintf(file, "\tmov ");
                trad_variable(file, instr->firstChild, &(function->u.symbol_tab));
                fprintf(file, ", ");
                fprintf(file, "\n");
            }
        }

        // fprintf(file, "\tmov rax, 60\n\tmov rdi, 0\n\tsyscall\n");
    }

    return 1;
}