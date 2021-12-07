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


#include "basicStackFunctions.h"

TStack* initStack(){
    TStack* stack = (TStack*)malloc(sizeof(TStack));   
    stack->top = -1;
    return stack;
}

/*int isFull(TStack *s){
    return s->top == s->capacity - 1;
}*/

int isEmpty(TStack *s){
    return s->top == -1;
}

void stack_push(TStack *s, stack_item *item){
    if (isFull(s))
        return;
    s->data[++s->top] = item;
}

void insert_start(TStack *s, int term_index){
    push(s, NULL);

    //array shift    
    for (int i = (top_index(s) -1); i >= term_index; i--)
        s->data[i+1] = s->data[i];

    stack_item *start_item = malloc(sizeof(stack_item));
    start_item->token = NULL;
    start_item->type = START;

    s->data[term_index] = start_item;    
}

stack_item pop(TStack *s){
    if (isEmpty(s))
        return;
    return *s->data[s->top--];
}

stack_item* top_item(TStack *s){
    if (isEmpty(s)){
        return;
    }
    return s->data[s->top];
}

int top_index(TStack *s){
    return s->top;
}

int term_index(TStack *s){
    for (int i = top_index(s); i >= 0; i--){
        if (s->data[i]->type == TERM || s->data[i]->type == EOS)
            return i;
    }    
    return -1;
}

void free_stack(TStack *s){
    if (isEmpty(s))
        return;
    free(s->data);
}