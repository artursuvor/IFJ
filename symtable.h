#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>



typedef int* symtable_value_t;
                                                                                             
typedef struct symtable_node {
	char *key;
	symtable_value_t value;
    struct symtable_node * lptr;
	struct symtable_node * rptr;
} symtable_node_t;	

symtable_node_t *symtable_init();

bool symtable_search(symtable_node_t *root_pointer, char *key, symtable_value_t value);

void symtable_insert(symtable_node_t **root_pointer, char *key, symtable_value_t value);

symtable_value_t get_symtable_value(symtable_node_t *root_pointer, char *key, symtable_value_t value);