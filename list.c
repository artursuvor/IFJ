#include <stdio.h>
#include <stdlib.h>
#include "./list.h"

list *init_list()
{
	list *new = my_malloc(sizeof(list));
	new->first = NULL;
	new->last = NULL;
	return new;

}

void node_delete(list_node_t *node)
{
	switch(node->token.type)
	{
			free(node->token.value); //
	}
}



bool list_is_empty(list *list)
{
	return list->first ? true : false;
}

void free_list(list *list)
{	
	list_node_t *remove = NULL;
	list_node_t *tmp = list->first;
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


void list_delete_first(list *list)
{ 
	if (!list->first) return;

	if (!list->first->next)
	{
		list->first = NULL;
		list->last = NULL;
	}
	else
	{
		list_node_t *tmp = list->first->next;
		tmp->previous = NULL;
		list->first = tmp;
	}

}

void list_delete_active(list *list)
{
	if (list->act == list->first && list->act == list->last)
	{
		list->first = NULL;
		list->first = NULL;
		list->last = NULL;
	}
	else if (list->act == list->first)
	{
		list->act = list->first->next;
		list->act->previous = NULL;
		list->first = list->act;
	}
	else if (list->act == list->last)
	{
		list->act = list->last->previous;
		list->act->next = NULL;
		list->last = list->act;
	}
	else
	{
		list_node_t *tmp = list->act;
		tmp->previous = list->act;
                tmp->next->previous = list->act;
		tmp->previous->next = tmp->next;
	}
}

void list_delete_last(list *list)
{
	if (!list->first) return;
	
	if (!list->last->previous)
	{
		list->first = NULL;
		list->last = NULL;
	}
	else
	{
		list_node_t *tmp = list->last->previous;
		tmp->next = NULL;
		list->last = tmp;
	}
}


void list_insert_first(list *list, token t)
{
	list_node_t *node = list_create_node(t);
	if (list->first == NULL)
	{
		list->first = node;
		list->last = node;
	}
	else
	{
		list->first->previous = node;
		node->next = list->first;
		list->first = node;
	}
}


void list_insert_last(list *list, token t)
{
	list_node_t *node = list_create_node(t);
	if (list->first == NULL)
        {
                list->first = node;
                list->last = node;
        }
	else
	{
		list->last->next = node;
		node->previous = list->last;
		list->last = node;
	}
}

void list_insert_active(list *list, token t)
{
	list_node_t *node = list_create_node(t);
	node->token = t;
	node->previous = list->act;

	if (list->act == list->last)
	{
		list->last = node;
	}
	else
	{
		node->next = list->act->next;
		node->next->previous = node;
	}
	list->act->next = node;
}

bool list_is_active(list *list)
{
	return list->act ? true : false;
}

void list_activate_first(list *list)
{
	list->act = list->first;
}

void list_activate_last(list *list)
{
	list->act = list->last;
}

token list_get_active(list *list)
{
	return list->act->token;
}

token list_get_after_active(list *list)
{
	return list->act->next->token;
}

token list_get_last(list *list)
{
	return list->last->token;
}

bool list_active_previous(list *list)
{
        if ((list->act = list->act->previous) != NULL)
                return true;
        return false;

}

bool list_active_next(list *list)
{
        if ((list->act = list->act->next) != NULL)
                return true;
        return false;
}

void list_delete_more(list *list, unsigned n)
{
        list_node_t *tmp = list->act->next;
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
                tmp->previous = list->act;
                list->act->next = tmp;
        }
        else
        {
                list->last = list->act;
                list->act->next = NULL;
        }
}