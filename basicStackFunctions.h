/*
*Téma:              Zakladne funkcie zasobniku
*varianta:          Tym 069, varianta 1
*clenovia:          xsuvor00 - veduci
*                   xnovak2q
*                   xfuisl00                   
*                   xcicmi00
*skola:             Vysoke uceni technicke v Brne - FIT
*datum vytvorenia:  1.12.2021
*/

#include <stdio.h>
#include <stdlib.h>
#include "precedence.h"

#define MAX_STACK 101

typedef struct{
    int top;    
    stack_item *data[MAX_STACK];
} TStack;

TStack* initStack();

int isFull(TStack *s);

int isEmpty(TStack *s);

void push(TStack *s, stack_item *item);

stack_item pop(TStack *s);

stack_item* top_item(TStack *s);

int top_index(TStack *s);

int term_index(TStack *s);

void free_stack(TStack *s)