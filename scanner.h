//
// Created by Lakluk on 26.10.2021.
//

#ifndef IFJ_SCANNER_H
#define IFJ_SCANNER_H
//struktura tokenu

typedef struct{
    int type;
    char *value;
} token;

#include "dynArr.h"

char Word(char x, dynArr *a); //done
char Number(char x, dynArr *a); //done
char String(char x, dynArr *a); //done
token * makeToken(int type, char *value); //done
char Double(char *number, dynArr *a); //done
char Exponent(char *number, dynArr *a); //done
char Exponent2(char *number, dynArr *a); //done
char * esc1(); //done
char * esc2(char x); //done
char * esc3(char x, char y); //done
char Operator(char x, dynArr *a); //done
char Operator2(char x, char y, dynArr *a); //done
void debug(dynArr *a); //NovákDebug
void printToken(token tok);

#endif //IFJ_SCANNER_H
