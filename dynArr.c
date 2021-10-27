/**
* Projekt: Implementace překladače imperativního jazyka IFJ21.
* Dynamicky rostoucí pole.
*
* Novák Matěj <xnovak2q@stud.fit.vutbr.cz>
*/

#include "dynArr.h"

void arrayInit(dynArr *a){
    a->array = malloc(sizeof(struct Token));
    if(!a->array){
        return; //ošetření mallocu
    }
    a->size = 1;
    a->used = 0;
    return;
}

void arrayInsert(dynArr *a, struct Token token){
    if(a->used >= a->size){
        a->size *= 4;
        a->array = realloc(a->array, a->size * sizeof(struct Token));
    }
    a->array[a->used++] = token;
    return;
}

void freeArray(dynArr *a){
    free(a->array);
    a->array = NULL;
    a->used = 0;
    a->size = 0;
    return;
}