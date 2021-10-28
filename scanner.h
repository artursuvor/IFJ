//
// Created by Lakluk on 26.10.2021.
//

#ifndef IFJ_SCANNER_H
#define IFJ_SCANNER_H
//struktura tokenu

struct Token {
    int type;
    char *value;
} *tokenPtr;

#include "dynArr.h"

char Word(char x, dynArr *a); //done
char Number(char x, dynArr *a); //done
char String(char x, dynArr *a); //done
struct Token * makeToken(int type, char *value);
char Double(char *number, dynArr *a); //done
char Exponent(char *number, dynArr *a); //work in progress
char Exponent2(char *number, dynArr *a);
char * esc1(); //done
char * esc2(char x); //done
char * esc3(char x, char y); //done
char Operator(char x, dynArr *a); //done
char Operator2(char x, char y, dynArr *a); //done
void debug(); //NovákDebug

#endif //IFJ_SCANNER_H
