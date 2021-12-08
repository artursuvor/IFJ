/**
* Projekt: Implementace překladače imperativního jazyka IFJ21.
* Dynamicky rostoucí pole.
*
* Novák Matěj <xnovak2q@stud.fit.vutbr.cz>
*/

#ifndef IFJ_DYNARR_H
#define IFJ_DYNARR_H

#include "dynStr.h"
#include "scanner.h"


typedef struct
{
    token_t *array;
    int used;
    int size;
} dynArr;


//základní inicializace dynamického pole
int arrayInit(dynArr *array);

//vložení do pole
void arrayInsert(dynArr *array, token_t token);

//uvolnění paměti po použití pole
void freeArray(dynArr *array);

#endif //IFJ_DYNARR_H