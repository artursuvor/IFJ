//
// Created by Novák on 01.11.2021.
//


#include "header_test.h"

#define DYNSTR_LEN 8

void initStr(dynStr *str){
    str->str = (char *) malloc(DYNSTR_LEN);
    if (!str->str) {
        exit(99);
    }
    str->all_len = DYNSTR_LEN;
    str->len = 0;
    str->str[str->len] = '\0';
    return;
}

void freeStr(dynStr *str){
    free(str->str);
    str->len = 0;
}

void addToStr(dynStr *str, char c){
    if ((str->len + 1) >= (str->all_len)){
        int size = str->len + DYNSTR_LEN;
        str->str = (char *)realloc(str->str, size);
        if (!str->str) {
            exit(99);
        }
        str->all_len = size;
    }
    str->str[str->len++] = c;
    str->str[str->len] = '\0';
    return;
}