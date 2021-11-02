/**
* Projekt: Implementace překladače imperativního jazyka IFJ21.
* Dynamicky rostoucí pole.
*
* Novák Matěj <xnovak2q@stud.fit.vutbr.cz>
*/
#ifndef IFJ_DYNARR_H
#define IFJ_DYNARR_H

typedef struct
{
    token *array;
    int used;
    int size;
} dynArr;

#include "scanner.h"


//základní inicializace dynamického pole
int arrayInit(dynArr *a);

//vložení do pole
void arrayInsert(dynArr *a, token tok);

//uvolnění paměti po použití pole
void freeArray(dynArr *a);

#endif