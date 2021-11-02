/**
* Projekt: Implementace překladače imperativního jazyka IFJ21.
* Dynamicky rostoucí pole.
*
* Novák Matěj <xnovak2q@stud.fit.vutbr.cz>
*/

#include "dynArr.h"

int arrayInit(dynArr *a){
    a->array = malloc(sizeof(token));
    if(!a->array){
        return 1; //ošetření mallocu
    }
    a->size = 1;
    a->used = 0;
    return 0;
}

void arrayInsert(dynArr *a, token tok){
    if(a->used >= a->size){
        a->size *= 2;
        a->array = realloc(a->array, a->size * sizeof(token));
    }
    a->array[a->used++] = tok;
    return;
}

void freeArray(dynArr *a){
    free(a->array);
    a->array = NULL;
    a->used = 0;
    a->size = 0;
    return;
}