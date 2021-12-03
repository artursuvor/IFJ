//
// Created by Lakluk on 26.10.2021.
//

#ifndef IFJ_SCANNER_H
#define IFJ_SCANNER_H
//struktura tokenu
#include "dynStr.h"

typedef struct{
    int type;
    dynStr *value;
} token;

#include "dynArr.c"
#include "dynStr.c"

char Word(char x, dynArr *a); //done
char Number(char x, dynArr *a); //done
char String(char x, dynArr *a); //done
token * makeToken(int type, dynStr *value); //done
char Double(dynStr *number, dynArr *a); //done
char Exponent(dynStr *number, dynArr *a); //done
char Exponent2(dynStr *number, dynArr *a, char x); //done
char * esc1(char x); //done
char * esc2(char x); //done
char * esc3(char x, char y); //done
char Operator(char x, dynArr *a); //done
char Operator2(char x, char y, dynArr *a); //done
void debug(dynArr *a); //NovákDebug
void printToken(token tok);
void newLineToken(dynArr *a);
#endif //IFJ_SCANNER_H
