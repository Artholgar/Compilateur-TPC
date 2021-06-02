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
    }
    else {
        for (i = strlen(name); name[i] != '.'; i--) {
            ;
        }

        name[i+1] = 'a';
        name[i+2] = 's';
        name[i+3] = 'm';
        name[i+4] = '\0';
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
    char  name[MAXNAME];
    while (types != NULL) {

        strcpy(name, types->name);
        // remove 'struct ' from type name
        memmove(name, name+7, strlen(name));
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

int trad_text(FILE* file, Node* node) {
    TableFunc* current_func;
    Node* function;

    fprintf(file, "section .text\n");

    for (current_func = node->u.symbol_tab.func; current_func != NULL; current_func = current_func->next) {
        fprintf(file, "global %s\n", current_func->name);
    }

    for (function = node->firstChild->nextSibling; function != NULL; function = function->nextSibling) {
        fprintf(file, "\n");
        fprintf(file, "%s :\n", function->firstChild->firstChild->u.identifier);

        fprintf(file, "\tpush rbp\n\tmov rbp, rsp\n");

        fprintf(file, "\tsub rsp, %d\n", function->u.symbol_tab.stsize);


        fprintf(file, "\tmov rax, 60\n\tmov rdi, 0\n\tsyscall\n");
    }
    
    return 1;
}