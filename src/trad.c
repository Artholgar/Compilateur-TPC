#include "trad.h"

int trad_to_nasm(char* name, Node* node) {
    FILE* file;
    file = create_nasm_file(name);
    trad_struct(file, node->u.symbol_tab.types);
    fprintf(file, "\n");
    trad_bss(file, node->u.symbol_tab);
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
    }
    return 0;
}

int trad_bss(FILE* file, SymbolTable symb_tab) {
    TableEntry* current;

    fprintf(file, "section .bss\n");

    for (current = symb_tab.array; current != NULL; current = current->next) {
        fprintf(file, "\t%s resb %d\n", current->identifier, current->size);
    }
    return 1;
}