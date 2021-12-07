/**
* Projekt: Implementace překladače imperativního jazyka IFJ21.
* Dynamicky rostoucí pole.
*
* Novák Matěj <xnovak2q@stud.fit.vutbr.cz>
*/

#include "dynArr.h"

int arrayInit(dynArr *array){
    array->array = malloc(sizeof(token_t));
    if(!array->array){
        return 1; //ošetření mallocu
    }
    array->size = 1;
    array->used = 0;
    return 0;
}

void arrayInsert(dynArr *array, token_t token){
    if(array->used >= array->size){
        array->size *= 2;
        array->array = realloc(array->array, array->size * sizeof(token_t));
    }
    array->array[array->used++] = token;
    return;
}

void freeArray(dynArr *array){
    free(array->array);
    array->array = NULL;
    array->used = 0;
    array->size = 0;
    return;
}