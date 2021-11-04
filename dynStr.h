//
// Created by Novák on 01.11.2021.
//

#ifndef IFJ_DYNSTR_H
#define IFJ_DYNSTR_H

typedef struct {
    char *str;
    int len;
    int all_len;
} dynStr;

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "scanner.h"



//inicializace dynamického stringu
//délka řetězce je nastavena na 1
//a ukončující znak je vložen na konec stringu
void initStr(dynStr *str);

//uvolnění z paměti
void freeStr(dynStr *str);

//přidání nového řetězce do původního a
//přepsání velikosti
void addToStr(dynStr *str, char c);

#endif //IFJ_DYNSTR_H
