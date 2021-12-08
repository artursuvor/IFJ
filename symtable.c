#include "symtable.h"

symtable_node_t *symtable_init()
{
	return NULL;
}	

bool symtable_search(symtable_node_t *root_pointer, char *key, symtable_value_t value)
{		
	if(root_pointer == NULL)
		return false;
	if(strcmp(root_pointer->key, key) == 0)
	{
		*value = *root_pointer->value;
		return true;
	}
    
    if(strcmp(key, root_pointer->key) < 0)
		return symtable_search(root_pointer->lptr,key,value);
	else
		return symtable_search(root_pointer->rptr,key,value);
} 

symtable_value_t get_symtable_value(symtable_node_t *root_pointer, char *key, symtable_value_t value){
	if(root_pointer == NULL)
		return -1;
	if(strcmp(root_pointer->key, key) == 0)
	{
		*value = *root_pointer->value;
		return *value;
	}
    
    if(strcmp(key, root_pointer->key) < 0)
		return get_symtable_value(root_pointer->lptr,key,value);
	else
		return get_symtable_value(root_pointer->rptr,key,value);
}

void symtable_insert(symtable_node_t **root_pointer, char *key, symtable_value_t value)
{		
	if (*root_pointer == NULL)
	{
		(*root_pointer) = my_malloc(sizeof(symtable_node_t));		
		(*root_pointer)->key = my_malloc(strlen(key) * sizeof(char) + 1);
		strcpy((*root_pointer)->key,key);
		(*root_pointer)->value=value;
		(*root_pointer)->lptr = NULL;
		(*root_pointer)->rptr = NULL;
	}
	else if(strcmp((*root_pointer)->key, key) == 0)
		(*root_pointer)->value=value;
	else if(strcmp(key, (*root_pointer)->key) < 0)
		symtable_insert(&(*root_pointer)->lptr,key,value);
	else 
		symtable_insert(&(*root_pointer)->rptr,key,value);
}