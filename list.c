#include <stdio.h>
#include <stdlib.h>
#include "./list.h"

list_t *init_list()
{
	list_t *new = my_malloc(sizeof(list_t));
	new->head = NULL;
	new->tail = NULL;
	return new;

}

void node_delete(list_node_t *node)
{
	switch(node->token.type)
	{
			free(node->token.value); //
	}
}



bool list_is_empty(list_t *list)
{
	return list->head ? true : false;
}

void free_list(list_t *list)
{	
	list_node_t *remove = NULL;
	list_node_t *tmp = list->head;
	while (tmp)
	{
		remove = tmp;
		tmp = tmp->next;
		node_delete(remove);
	}
	//free(list);
}


list_node_t *list_create_node(token t)
{
	list_node_t *new = my_malloc(sizeof(list_node_t));
	new->next = NULL;
	new->previous = NULL;
	new->token = t;
	return new;
}


void list_delete_first(list_t *list)
{ 
	if (!list->head) return;

	if (!list->head->next)
	{
		list->head = NULL;
		list->tail = NULL;
	}
	else
	{
		list_node_t *tmp = list->head->next;
		tmp->previous = NULL;
		list->head = tmp;
	}

}

void list_delete_active(list_t *list)
{
	if (list->active == list->head && list->active == list->tail)
	{
		list->head = NULL;
		list->head = NULL;
		list->tail = NULL;
	}
	else if (list->active == list->head)
	{
		list->active = list->head->next;
		list->active->previous = NULL;
		list->head = list->active;
	}
	else if (list->active == list->tail)
	{
		list->active = list->tail->previous;
		list->active->next = NULL;
		list->tail = list->active;
	}
	else
	{
		list_node_t *tmp = list->active;
		tmp->previous = list->active;
                tmp->next->previous = list->active;
		tmp->previous->next = tmp->next;
	}
}

void list_delete_last(list_t *list)
{
	if (!list->head) return;
	
	if (!list->tail->previous)
	{
		list->head = NULL;
		list->tail = NULL;
	}
	else
	{
		list_node_t *tmp = list->tail->previous;
		tmp->next = NULL;
		list->tail = tmp;
	}
}


void list_insert_first(list_t *list, token t)
{
	list_node_t *node = list_create_node(t);
	if (list->head == NULL)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		list->head->previous = node;
		node->next = list->head;
		list->head = node;
	}
}


void list_insert_last(list_t *list, token t)
{
	list_node_t *node = list_create_node(t);
	if (list->head == NULL)
        {
                list->head = node;
                list->tail = node;
        }
	else
	{
		list->tail->next = node;
		node->previous = list->tail;
		list->tail = node;
	}
}

void list_insert_active(list_t *list, token t)
{
	list_node_t *node = list_create_node(t);
	node->token = t;
	node->previous = list->active;

	if (list->active == list->tail)
	{
		list->tail = node;
	}
	else
	{
		node->next = list->active->next;
		node->next->previous = node;
	}
	list->active->next = node;
}

bool list_is_active(list_t *list)
{
	return list->active ? true : false;
}

void list_activate_first(list_t *list)
{
	list->active = list->head;
}

void list_activate_last(list_t *list)
{
	list->active = list->tail;
}

token list_get_active(list_t *list)
{
	return list->active->token;
}

token list_get_after_active(list_t *list)
{
	return list->active->next->token;
}

token list_get_last(list_t *list)
{
	return list->tail->token;
}

bool list_active_previous(list_t *list)
{
        if ((list->active = list->active->previous) != NULL)
                return true;
        return false;

}

bool list_active_next(list_t *list)
{
        if ((list->active = list->active->next) != NULL)
                return true;
        return false;
}

void list_delete_more(list_t *list, unsigned n)
{
        list_node_t *tmp = list->active->next;
        list_node_t *remove;
        while (tmp && n > 0)
        {
                remove = tmp;
                tmp = tmp->next;
  //            free(remove);
                remove = NULL;
                n--;
        }
        if (tmp)
        {
                tmp->previous = list->active;
                list->active->next = tmp;
        }
        else
        {
                list->tail = list->active;
                list->active->next = NULL;
        }
}