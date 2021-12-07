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

struct TStack* initStack(){
    struct TStack* stack = (struct Stack*)malloc(sizeof(struct Stack));   
    stack->top = -1;
    stack->array = (int*)malloc(MAX_STACK * sizeof(int));
    return stack;
}

int isFull(TStack *s){
    return s->top == s->capacity - 1;
}

int isEmpty(TStack *s){
    return s->top == -1;
}

void push(TStack *s, stack_item item){
    if (isFull(s))
        return;
    s->array[++s->top] = item;
}

void insert_start(TStack *s, int term_index){
    push(s, NULL);

    //array shift    
    for (int i = (top_index(s) -1); i >= term_index; i--)
        s->data[i+1] = s=>data[i];

    stack_item *start_item = malloc(sizeof(stack_item));
    start_item->token_t = NULL;
    start_item->stack_item_type = START;

    s->data[term_index] = start_item;    
}

stack_item* pop(TStack *s){
    if (isEmpty(s))
        return;
    return s->data[s->top--];
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
        if (s->data[i]->stack_item_type == TERM || s->data[i]->stack_item_type == EOS)
            return i;
    }    
    return -1;
}

void free_stack(TStack *s){
    if (isEmpty(s))
        return;
    free(s->data)
}