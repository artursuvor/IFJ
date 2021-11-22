#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>

typedef int* symtable_value_t;

// uzel stromu
                                                                                                            
typedef struct symtable_node {
	char *key;
	symtable_value_t value;
    struct symtable_node * lptr;
	struct symtable_node * rptr;
} symtable_node_t;	

symtable_node_t *symtable_init();

bool symtable_search(symtable_node_t *root_pointer, char *key, symtable_value_t content);

void symtable_insert(symtable_node_t **root_pointer, char *key, symtable_value_t content);
