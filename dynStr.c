//
// Created by Novák on 01.11.2021.
//

#include "dynStr.h"

int initStr(dynStr *str){
    str->len = 1;
    str->str = (char *) malloc(sizeof (char) * (str->len+1));
    if (!str->str){
        return 1;
    }
    str->str[str->len] = '\0';
    return 0;
}

void freeStr(dynStr *str){
    free(str->str);
    str->len = 0;
}

int addToStr(dynStr *str, char *strToAdd){
    int strToAddSize = strlen(strToAdd);
    int size = str->len + strToAddSize;
    str->str = realloc(str->str, sizeof(char) * (size+1));
    if (!str->str){
        return 1;
    }
    str->len = size;
    strcat(str->str, strToAdd);
    return 0;
}