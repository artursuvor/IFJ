//
// Created by Lakluk on 26.10.2021.
//

//struktura tokenu

#ifndef IFJ_SCANNER_H
#define IFJ_SCANNER_H

#include "dynArr.h"
#include "dynStr.h"


enum tokenType {keyword, id, string, operator, integer, ddouble, exponent, left_bracket, right_bracket, t_EOF, t_EOL, equal, add, sub, mul, t_div};

typedef struct{
    int type;
    dynStr *value;
} token_t;


char Word(char x, dynArr *a); //done
char Number(char x, dynArr *a); //done
char String(char x, dynArr *a); //done
token_t * makeToken(int type, dynStr *value); //done
char Double(dynStr *number, dynArr *a); //done
char Exponent(dynStr *number, dynArr *a); //done
char Exponent2(dynStr *number, dynArr *a, char x); //done
char * esc1(char x); //done
char * esc2(char x); //done
char * esc3(char x, char y); //done
char Operator(char x, dynArr *a); //done
char Operator2(char x, char y, dynArr *a); //done
void debug(dynArr *a); //NovákDebug
void printToken(token_t tok);
void newLineToken(dynArr *a);

#endif //IFJ_SCANNER_H