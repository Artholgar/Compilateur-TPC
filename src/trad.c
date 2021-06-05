#include "trad.h"

int labelno = 0;

int trad_to_nasm(char* name, Node* node) {
    FILE* file;
    file = create_nasm_file(name);
    trad_struct(file, node->u.symbol_tab.types);

    fprintf(file, "section .data\n");
    fprintf(file, "\tformat_int db '%%d', 10, 0\n");
    fprintf(file, "\tformat_char db '%%c', 10, 0\n");
    fprintf(file, "\tformat_read_int db '%%d', 0\n");
    fprintf(file, "\tformat_read_char db '%%c', 0\n");

    fprintf(file, "\n");

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

int trad_adresse(FILE* file, Node* node, SymbolTable* table) {
    TableEntry* entry = NULL;
    TableType* type = NULL;
    TableChamp* champ = NULL;
    char name[MAXNAME];

    if (checkTable(&entry, table, node->u.identifier)) {
        checkType(&type, table, entry->type);
        checkChamp(&champ, type, node->firstChild->u.identifier);
        if (isGlobal(table, node->u.identifier) == 1) {
            fprintf(file, "%s", entry->identifier);
        } else {
            switch (-entry->offset) {
                case rdi:
                    fprintf(file, "rdi");
                    break;
                case rsi:
                    fprintf(file, "rsi");
                    break;
                case rdx:
                    fprintf(file, "rdx");
                    break;
                case rcx:
                    fprintf(file, "rcx");
                    break;
                case r8:
                    fprintf(file, "r8");
                    break;
                case r9:
                    fprintf(file, "r9");
                    break;
                default:
                    fprintf(file, "rbp - %d - %ld", entry->offset, entry->size);
                    break;
            }
        }
        if (NULL != champ) {
            strcpy(name, type->name);
            // remove 'struct ' from type name
            memmove(name, name + 7, strlen(name));
            fprintf(file, " + %s.%s", name, champ->name);
        }
    }
    return 1;
}

int trad_variable(FILE* file, Node* node, SymbolTable* table) {
    TableEntry* entry = NULL;
    TableType* type = NULL;
    TableChamp* champ = NULL;
    size_t size;

    if (checkTable(&entry, table, node->u.identifier)) {
        if (entry->offset >= 0) {
            if (entry->size == 8) {
                fprintf(file, "qword ");
                size = 8;
            } else if (entry->size == 4) {
                fprintf(file, "dword ");
                size = 4;
            } else if (entry->size == 1) {
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
            trad_adresse(file, node, table);
            fprintf(file, "]");
        } else {
            trad_adresse(file, node, table);
            size = 8;
        }
    }

    return size;
}

int trad_identifier(FILE* file, Node* node, SymbolTable* table) {
    TableType* type = NULL;
    TableEntry* Lval = NULL;
    TableChamp* champ = NULL;
    int size = 0;

    if (checkTable(&Lval, table, node->u.identifier)) {
        // Quand il ne s'agit pas d'une structure entière.
        if (!(checkType(&type, table, Lval->type)) || node->firstChild != NULL) {
            fprintf(file, "\txor rax, rax\n");
            fprintf(file, "\tmov ");

            if (Lval->size == 8) {
                fprintf(file, "rax, ");
                size = 8;
            } else if (Lval->size == 4) {
                fprintf(file, "eax, ");
                size = 4;
            } else if (Lval->size == 1) {
                fprintf(file, "al, ");
                size = 1;
            } else {
                checkChamp(&champ, type, node->firstChild->u.identifier);
                if (strcmp(champ->type, "int") == 0) {
                    fprintf(file, "eax, ");
                    size = 4;
                } else if (strcmp(champ->type, "char") == 0) {
                    fprintf(file, "al, ");
                    size = 1;
                }
            }

            trad_variable(file, node, table);
            fprintf(file, "\n\n");

        } else {
            ;
        }
    }

    return size;
}

int trad_assignment(FILE* file, Node* node, SymbolTable* table) {
    TableEntry* Lval = NULL;
    TableType* type = NULL;
    TableChamp* champ = NULL;
    int size;

    if (checkTable(&Lval, table, node->firstChild->u.identifier)) {
        // Quand il ne s'agit pas d'une structure entière.
        if (!(checkType(&type, table, Lval->type)) || node->firstChild->firstChild != NULL) {
            // On traduit d'abord ce qu'il y a a droite
            // on traduit l'instruction, et on met le resultat dans rax
            trad_instr(file, node->firstChild->nextSibling, table);

            fprintf(file, "\tmov ");
            size = trad_variable(file, node->firstChild, table);

            if (size == 8) {
                fprintf(file, ", rax\n");
            } else if (size == 4) {
                fprintf(file, ", eax\n");
            } else if (size == 1) {
                fprintf(file, ", al\n");
            } else {
                checkChamp(&champ, type, node->firstChild->firstChild->u.identifier);
                if (strcmp(champ->type, "int") == 0) {
                    fprintf(file, ", eax\n");
                } else if (strcmp(champ->type, "char") == 0) {
                    fprintf(file, ", al\n");
                }
            }

        } else {
            ;
        }
    }
    return 1;
}

int trad_func_call(FILE* file, Node* node, SymbolTable* table) {
    Node* current_param = NULL;
    int compteur = 1;
    int cmp_stack = 0;

    for (current_param = node->firstChild; current_param != NULL; current_param = current_param->nextSibling) {
        trad_instr(file, current_param, table);
        switch (compteur) {
            case rdi:
                fprintf(file, "\tmov rdi, rax\n");
                break;
            case rsi:
                fprintf(file, "\tmov rsi, rax\n");
                break;
            case rdx:
                fprintf(file, "\tmov rdx, rax\n");
                break;
            case rcx:
                fprintf(file, "\tmov rcx, rax\n");
                break;
            case r8:
                fprintf(file, "\tmov r8, rax\n");
                break;
            case r9:
                fprintf(file, "\tmov r9, rax\n");
                break;
            default:
                fprintf(file, "\tpush rax\n");
                cmp_stack += 8;
                break;
        }
        compteur += 1;
    }
    fprintf(file, "\tcall %s\n", node->u.identifier);
    while (cmp_stack != 0) {
        fprintf(file, "\tpop rbx\n");
        cmp_stack -= 8;
    }
    return 1;
}

int trad_instr(FILE* file, Node* node, SymbolTable* table) {
    int true_label, false_label, end_label;
    Node* instr;
    int size;

    if (node == NULL) {
        return 1;
    }

    switch (node->kind) {
        case IntLiteral:
            fprintf(file, "\txor rax, rax\n");
            fprintf(file, "\tmov eax, %d\n", node->u.integer);
            return 4;
            break;
        case CharLiteral:
            fprintf(file, "\txor rax, rax\n");
            if (node->u.character == '\n') {
                fprintf(file, "\tmov ax, 10\n");
            } else {
                fprintf(file, "\tmov ax, '%c'\n", node->u.character);
            }
            return 1;
            break;
        case Identifier:
            return trad_identifier(file, node, table);
            break;
        case AddSub:
            trad_instr(file, node->firstChild, table);
            fprintf(file, "\tpush rax\n");
            trad_instr(file, node->firstChild->nextSibling, table);
            fprintf(file, "\tpush rax\n");
            fprintf(file, "\tpop rbx\n");
            fprintf(file, "\tpop rax\n");

            if (strcmp(node->u.identifier, "+") == 0) {
                fprintf(file, "\tadd eax, ebx\n\n");
            } else {
                fprintf(file, "\tsub eax, ebx\n\n");
            }
            break;
        case DivStar:
            trad_instr(file, node->firstChild, table);
            fprintf(file, "\tpush rax\n");
            trad_instr(file, node->firstChild->nextSibling, table);
            fprintf(file, "\tpush rax\n");
            fprintf(file, "\tpop rbx\n");
            fprintf(file, "\tpop rax\n");
            if (strcmp(node->u.identifier, "*") == 0) {
                fprintf(file, "\timul eax, ebx\n\n");
            } else if (strcmp(node->u.identifier, "/") == 0) {
                fprintf(file, "\txor rdx, rdx\n");
                fprintf(file, "\tidiv ebx\n\n");
            } else {
                fprintf(file, "\txor rdx, rdx\n");
                fprintf(file, "\tidiv ebx\n");
                fprintf(file, "\tmov rax, rdx\n\n");
            }
            break;
        case Compare:
        case Equals:
            trad_instr(file, node->firstChild, table);
            fprintf(file, "\tpush rax\n");
            trad_instr(file, node->firstChild->nextSibling, table);
            fprintf(file, "\tpush rax\n");
            fprintf(file, "\tpop rbx\n");
            fprintf(file, "\tpop rax\n");
            fprintf(file, "\tcmp rax, rbx\n");

            true_label = labelno;
            if (strcmp(node->u.identifier, "==") == 0) {
                fprintf(file, "\tje L%d\n", true_label);
            } else if (strcmp(node->u.identifier, "!=") == 0) {
                fprintf(file, "\tjne L%d\n", true_label);
            } else if (strcmp(node->u.identifier, "<") == 0) {
                fprintf(file, "\tjl L%d\n", true_label);
            } else if (strcmp(node->u.identifier, "<=") == 0) {
                fprintf(file, "\tjle L%d\n", true_label);
            } else if (strcmp(node->u.identifier, ">") == 0) {
                fprintf(file, "\tjg L%d\n", true_label);
            } else if (strcmp(node->u.identifier, ">=") == 0) {
                fprintf(file, "\tjge L%d\n", true_label);
            }
            labelno += 1;
            false_label = labelno;
            fprintf(file, "L%d:\n", false_label);
            fprintf(file, "\tmov rax, 0\n");
            labelno += 1;
            end_label = labelno;
            fprintf(file, "\tjmp L%d\n", end_label);
            fprintf(file, "L%d:\n", true_label);
            fprintf(file, "\tmov rax, 1\n");
            fprintf(file, "\tjmp L%d\n", end_label);
            fprintf(file, "L%d:\n", end_label);
            labelno += 1;
            break;
        case And:
            trad_instr(file, node->firstChild, table);
            fprintf(file, "\tcmp rax, 0\n");
            end_label = labelno;
            labelno += 1;
            fprintf(file, "\tje L%d\n", end_label);

            trad_instr(file, node->firstChild->nextSibling, table);
            fprintf(file, "L%d:\n", end_label);
            break;
        case Or:
            trad_instr(file, node->firstChild, table);
            fprintf(file, "\tcmp rax, 0\n");
            end_label = labelno;
            labelno += 1;
            fprintf(file, "\tjne L%d\n", end_label);

            trad_instr(file, node->firstChild->nextSibling, table);
            fprintf(file, "L%d:\n", end_label);
            break;
        case Not:
            trad_instr(file, node->firstChild, table);
            fprintf(file, "\tcmp rax, 0\n");
            false_label = labelno;
            labelno += 1;
            fprintf(file, "\tjne L%d\n", false_label);
            fprintf(file, "\tmov rax, 1\n");
            end_label = labelno;
            labelno += 1;
            fprintf(file, "L%d:\n", false_label);
            fprintf(file, "\tmov rax, 0\n");
            fprintf(file, "L%d:\n", end_label);
            break;
        case If:
            trad_instr(file, node->firstChild, table);
            fprintf(file, "\tcmp rax, 0\n");
            false_label = labelno;
            labelno += 1;
            fprintf(file, "\tje L%d\n", false_label);
            trad_instr(file, node->firstChild->nextSibling, table);
            end_label = labelno;
            labelno += 1;
            fprintf(file, "\tjmp L%d\n", end_label);

            fprintf(file, "L%d:\n", false_label);
            trad_instr(file, node->firstChild->nextSibling->nextSibling, table);
            fprintf(file, "L%d:\n", end_label);
            break;
        case Else:
            trad_instr(file, node->firstChild, table);
            break;
        case While:
            true_label = labelno;
            labelno += 1;
            fprintf(file, "L%d:\n", true_label);
            trad_instr(file, node->firstChild, table);
            fprintf(file, "\tcmp rax, 0\n");
            end_label = labelno;
            labelno += 1;
            fprintf(file, "\tje L%d\n", end_label);
            trad_instr(file, node->firstChild->nextSibling, table);
            fprintf(file, "\tjmp L%d\n", true_label);
            fprintf(file, "L%d:\n", end_label);

            break;
        case Asignment:
            trad_assignment(file, node, table);
            break;
        case Return:
            trad_instr(file, node->firstChild, table);

            fprintf(file, "\tadd rsp, %d\n\n", table->stsize);

            fprintf(file, "\tpop rbp\n\n");

            if (strcmp(table->name, "main") == 0) {
                fprintf(file, "\tmov rdi, rax\n");
                fprintf(file, "\tmov rax, 60\n");
                fprintf(file, "\tsyscall\n");
            } else {
                fprintf(file, "\tret\n");
            }
            break;
        case SuiteInstr:
            for (instr = node->firstChild; instr != NULL; instr = instr->nextSibling) {
                trad_instr(file, instr, table);
            }
            break;
        case Print:
            size = trad_instr(file, node->firstChild, table);
            fprintf(file, "\tmov rdi, rax\n");
            fprintf(file, "\tmov rsi, %d\n", size);
            fprintf(file, "\tcall print\n");
            break;
        case Reade:
            fprintf(file, "\tmov rax, ");
            trad_adresse(file, node->firstChild, table);
            fprintf(file, "\n");
            fprintf(file, "\tmov rdi, rax\n");
            fprintf(file, "\tcall reade\n");
            break;
        case Readc:
            fprintf(file, "\tmov rax, ");
            trad_adresse(file, node->firstChild, table);
            fprintf(file, "\n");
            fprintf(file, "\tmov rdi, rax\n");
            fprintf(file, "\tcall readc\n");
            break;
        case Func:
            trad_func_call(file, node, table);
            break;

        default:
            break;
    }

    return 4;
}

int print(FILE* file) {
    int char_label, end_label;

    char_label = labelno;
    labelno += 1;
    end_label = labelno;
    labelno += 1;

    fprintf(file, "print :\n");
    fprintf(file, "\tpush rbp\n");
    fprintf(file, "\tmov rbp, rsp\n");

    fprintf(file, "\tmov rax, rsi\n");
    fprintf(file, "\tmov rsi, rdi\n");

    fprintf(file, "\tcmp rax, 4\n");
    fprintf(file, "\tjne L%d\n", char_label);

    fprintf(file, "\tmov rdi, format_int\n");
    fprintf(file, "\tjmp L%d\n", end_label);

    fprintf(file, "L%d:\n", char_label);
    fprintf(file, "\tmov rdi, format_char\n");

    fprintf(file, "L%d:\n", end_label);
    fprintf(file, "\tmov rax, 0\n");
    fprintf(file, "\tmov r14, rsp\n");
    fprintf(file, "\tand rsp, -16\n");
    fprintf(file, "\tcall printf\n");
    fprintf(file, "\tmov rsp, r14\n");

    fprintf(file, "\tpop rbp\n");
    fprintf(file, "\tret\n");
    return 1;
}

int reade(FILE* file) {
    fprintf(file, "reade :\n");
    fprintf(file, "\tpush rbp\n");
    fprintf(file, "\tmov rbp, rsp\n");

    fprintf(file, "\tmov rsi, rdi\n");

    fprintf(file, "\tmov rdi, format_read_int\n");

    fprintf(file, "\tmov rax, 0\n");
    fprintf(file, "\tmov r14, rsp\n");
    fprintf(file, "\tand rsp, -16\n");
    fprintf(file, "\tcall scanf\n");
    fprintf(file, "\tmov rsp, r14\n");

    fprintf(file, "\tpop rbp\n");
    fprintf(file, "\tret\n");
    return 1;
}

int readc(FILE* file) {
    fprintf(file, "readc :\n");
    fprintf(file, "\tpush rbp\n");
    fprintf(file, "\tmov rbp, rsp\n");

    fprintf(file, "\tmov rsi, rdi\n");

    fprintf(file, "\tmov rdi, format_read_char\n");

    fprintf(file, "\tmov rax, 0\n");
    fprintf(file, "\tmov r14, rsp\n");
    fprintf(file, "\tand rsp, -16\n");
    fprintf(file, "\tcall scanf\n");
    fprintf(file, "\tmov rsp, r14\n");

    fprintf(file, "\tpop rbp\n");
    fprintf(file, "\tret\n");
    return 1;
}

int trad_text(FILE* file, Node* node) {
    TableFunc* current_func;
    Node* function;
    Node* corp;

    fprintf(file, "section .text\n");

    for (current_func = node->u.symbol_tab.func; current_func != NULL; current_func = current_func->next) {
        fprintf(file, "global %s\n", current_func->name);
    }

    fprintf(file, "global print\n");
    fprintf(file, "global reade\n");
    fprintf(file, "global readc\n");
    fprintf(file, "extern printf\n");
    fprintf(file, "extern scanf\n");

    fprintf(file, "\n");

    print(file);

    fprintf(file, "\n");

    reade(file);

    fprintf(file, "\n");

    readc(file);

    for (function = node->firstChild->nextSibling; function != NULL; function = function->nextSibling) {
        fprintf(file, "\n");
        fprintf(file, "%s :\n", function->firstChild->firstChild->u.identifier);

        fprintf(file, "\tpush rbp\n\tmov rbp, rsp\n");

        fprintf(file, "\tsub rsp, %d\n\n", function->u.symbol_tab.stsize);

        corp = function->firstChild->nextSibling;

        trad_instr(file, corp->firstChild->nextSibling, &(function->u.symbol_tab));

        // for (instr = corp->firstChild->nextSibling->firstChild; instr != NULL; instr = instr->nextSibling) {
        //     trad_instr(file, instr, &(function->u.symbol_tab));
        // }
    }

    return 1;
}