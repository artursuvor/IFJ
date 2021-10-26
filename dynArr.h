/**
* Projekt: Implementace překladače imperativního jazyka IFJ21.
* Dynamicky rostoucí pole.
*
* Novák Matěj <xnovak2q@stud.fit.vutbr.cz>
*/
#ifndef IFJ_DYNARR_H
#define IFJ_DYNARR_H
#include "scanner.h"

typedef struct
{
    int *array;
    int used;
    int size;
} dynArr;

//základní inicializace dynamického pole
void arrayInit(dynArr *a);

//vložení do pole
void arrayInsert(dynArr *a, tokenPtr token);

//uvolnění paměti po použití pole
void freeArray(dynArr *a);

#endif