/* decl-var.c */
/* Traduction descendante récursive des déclarations de variables en C */
/* Compatible avec decl-var.lex */
#include "decl-var.h"

void initialisation_Table(SymbolTable *table, char *name, SymbolTable *parent) {
    table->array = NULL;
    table->types = NULL;
    strcpy(table->name, name);
    table->parent = parent;
    table->stsize = 0;
}

void Print_table(SymbolTable table) {
    TableEntry *current;
    TableType *current_type;
    TableFunc *current_func;

    current = table.array;

    current_type = table.types;

    current_func = table.func;

    if (current_type != NULL) {
        printf("Types :\n");
    }

    while (current_type != NULL) {
        printf("\t%d - %s\n", current_type->size, current_type->name);

        for (TableChamp *current_champ = current_type->champs; current_champ != NULL; current_champ = current_champ->next) {
            printf("\t\t%s - %s\n", current_champ->type, current_champ->name);
        }
        current_type = current_type->next;
    }

    if (current_func != NULL) {
        printf("Fonctions :\n");
    }

    while (current_func != NULL) {
        printf("\t%d - %s\n", current_func->size, current_func->name);

        current_func = current_func->next;
    }

    printf("%s - size = %d :\n", table.name, table.stsize);
    while (current != NULL) {
        printf("\t%d - ", current->offset);
        switch (current->kind) {
            case Variable:
                printf("Variable - ");
                break;
            case Function:
                printf("Function - ");
                break;
            case Parameter:
                printf("Parameter - ");
                break;

            default:
                break;
        }
        printf("%ld %s %s\n", current->size, current->type, current->identifier);
        current = current->next;
    }
}

int checkTable(TableEntry **entry, SymbolTable *table, const char name[]) {
    TableEntry *current;

    if (NULL == table) {
        return 0;
    }
    if (checkTable(entry, table->parent, name)) {
        return 1;
    }
    current = table->array;

    while (current != NULL) {
        if (strcmp(current->identifier, name) == 0) {
            *entry = current;
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int isGlobal(SymbolTable *table, const char name[]) {
    TableEntry *current;

    if (NULL == table) {
        return 0;
    }
    if (isGlobal(table->parent, name)) {
        return 1;
    }
    current = table->array;

    while (current != NULL) {
        if (strcmp(current->identifier, name) == 0) {
            if (strcmp(table->name, "Global") == 0) {
                return 1;
            } else {
                return 0;
            }
        }
        current = current->next;
    }
    return 0;
}

int checkType(TableType **type, SymbolTable *table, const char name[]) {
    TableType *current;

    if (NULL == table) {
        return 0;
    }
    if (checkType(type, table->parent, name)) {
        return 1;
    }
    current = table->types;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            (*type) = current;
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int checkChamp(TableChamp **champ, TableType *type, const char name[]) {
    TableChamp *current;

    if (NULL == type) {
        return 0;
    }

    current = type->champs;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            (*champ) = current;
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int count_params(SymbolTable *table) {
    TableEntry *current = NULL;
    int count = 0;

    for (current = table->array; current != NULL; current = current->next) {
        if (current->kind == Parameter) {
            count += 1;
        }
    }
    return count;
}

int checkVar(SymbolTable * table, const char name[]) {
    TableEntry * current;
    
    if (NULL == table || table->parent == NULL) {
        return 0;
    }
    
    current = table->parent->array;

    while (current != NULL) {
        if (strcmp(current->identifier, name) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int checkFunc(SymbolTable * table, const char name[]) {
    TableFunc * current;
    
    if (NULL == table) {
        return 0;
    }
    
    current = table->func;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void addVar(SymbolTable *table, const char name[], char *type, Kind_Val kind) {
    TableEntry *new;
    TableType *new_type;
    int count_param;

    if (checkVar(table, name)) {
        fprintf(stderr, "Error : redefinition de la variable %s\n", name);
        exit(2);
    }
    
    if (NULL == (new = (TableEntry *)malloc(sizeof(TableEntry)))) {
        perror("malloc");
        exit(3);
    }

    count_param = count_params(table);

    new->next = table->array;
    table->array = new;

    strcpy(table->array->identifier, name);
    strcpy(table->array->type, type);
    table->array->kind = kind;
    new->on_stack = 1;
    if (kind == Parameter) {
        if (count_param <= 5) {
            new->offset = 0;
            new->on_stack = 0;
            new->reg = count_param + 1;
        }
        else {
            new->offset = ((count_param - 6) * 8);
            new->reg = count_param + 1;
        }
    } else {
        new->offset = -table->stsize;
    }

    if (strcmp(type, "int") == 0) {
        if (kind == Parameter) {
            new->size = 8;
        } else {
            table->stsize += 4;
            new->size = 4;
        }

    } else if (strcmp(type, "char") == 0) {
        if (kind == Parameter) {
            new->size = 8;
        } else {
            table->stsize += 1;
            new->size = 1;
        }

    } else {
        if (checkType(&new_type, table, type) == 1) {
            if (kind == Parameter) {
                ;
            } else {
                table->stsize += new_type->size;
            }

            new->size = new_type->size;
        } else {
            // erreur sémantique, a toi de jouer Thomas !!
            // le type écrit n'existe pas
            ;
        }
    }
}

void addFunc(SymbolTable *table, const char name[], char *type) {  
    TableFunc *new;
    TableType *new_type;

    if (checkFunc(table, name)) {
        fprintf(stderr, "Error : the function %s already exist \n", name);
        exit(2);
    }
    
    if (NULL == (new = (TableFunc *)malloc(sizeof(TableFunc)))) {
        perror("malloc");
        exit(3);
    }

    new->next = table->func;
    table->func = new;

    strcpy(table->func->name, name);
    strcpy(table->func->type, type);

    if (strcmp(type, "int") == 0) {
        new->size = 4;
    } else if (strcmp(type, "char") == 0) {
        new->size = 1;
    } else {
        if (checkType(&new_type, table, type) == 1) {
            new->size = new_type->size;
        } else {
            // erreur sémantique, a toi de jouer Thomas !!
            //la fonction n'existe pas
            ;
        }
    }
}


