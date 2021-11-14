#include <stdbool.h>
#include "scanner.h"

typedef struct node {
	token token;
	struct node *next;
	struct node *previous;
} list_node_t;

typedef struct {
	list_node_t *first;
	list_node_t *last;
	list_node_t *act;
} list;


list *init_list();

void free_list(list *list);

void list_insert_first(list *list, token t);

void list_delete_first(list *list);

void list_delete_active(list *list);

void list_delete_last(list *list);

bool list_is_empty(list *list);

void list_insert_last(list *list, token t); 

void list_insert_active(list *list, token t);

bool list_is_active(list *list);

void list_activate_first(list *list);

void list_activate_last(list *list);

token list_get_active(list *list);

token list_get_after_active(list *list);

token list_get_last(list *list);

bool list_active_previous(list *list);

bool list_active_next(list *list);

void list_delete_more(list *list, unsigned n);
