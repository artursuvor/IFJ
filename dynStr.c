//
// Created by Novák on 01.11.2021.
//

#include "dynStr.h"

void initStr(dynStr *str){
    str->len = 1;
    str->str = (char *) malloc(sizeof (char) * (str->len+1));
    if (!str->str){
        exit(99);
    }
    str->str[str->len] = '\0';
    return;
}

void freeStr(dynStr *str){
    free(str->str);
    str->len = 0;
}

void addToStr(dynStr *str, char *strToAdd){
    int strToAddSize = strlen(strToAdd);
    int size = str->len + strToAddSize;
    str->str = realloc(str->str, sizeof(char) * (size+1));
    if (!str->str){
        exit(99);
    }
    str->len = size;
    strcat(str->str, strToAdd);
    return;
}