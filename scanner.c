//
// Created by Lakluk on 22.10.2021.
//

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include <ctype.h>
#include "basicScannerFunctions.c"
#include "scanner.h"

enum tokenType{keyword, id, string, operator, integer, ddouble, exponent};

int Error = 0;
//tělo hlavní funkce Scanner
int main(){
    dynArr *array = malloc(sizeof(dynArr));
    int err = arrayInit(array);
    char vstup = getchar();
    char tmp1;
    char tmp2;
    char tmp3;
    bool konec = false;
    while(!konec){
        if(isLetterUnder(vstup))
            vstup = Word(vstup, array);
        else
            if(isdigit(vstup))
                vstup = Number(vstup, array);
            else
                if(isQuot(vstup))
                    vstup = String(vstup, array);
                else
                    if(isMinus(vstup)){ //přeskakování komentářů
                        tmp1 = getchar();
                            if(isMinus(tmp1)) {
                                tmp2 = getchar();
                                if (isOpenBracket(tmp2)) {
                                    tmp3 = getchar();
                                    if (isOpenBracket(tmp3)){
                                        skipBlockComment();
                                    }
                                    else{
                                        skipLineComment();
                                    }
                                }
                                else{
                                    skipLineComment();
                                }
                            }
                            else
                                vstup = tmp1;
                    }
                    else {
                        if (isOperator(vstup))
                            vstup = Operator(vstup, array);
                        else if (isEOF(vstup))
                            konec = true;
                        else if (isspace(vstup))
                            vstup = getchar();
                        else {
                            freeArray(array);
                            Error++;
                            if (Error >= 1)
                                return 1;
                        }
                    }
    }
    debug(array);
    freeArray(array);
    if (Error>=1)
        return 1;
    return 0;
}

//Samotné funkce potřebné pro scanner

char Word(char x,dynArr *a){
    token * send;
    dynStr *slovo = malloc(sizeof (dynStr));
    initStr(slovo);
    addToStr(slovo, &x);
    x = getchar();
    while (isLetterUnderNumber(x)){
        addToStr(slovo,&x);
        x = getchar();
    }
    if(isKeyword(slovo)) {
        send = makeToken(keyword, slovo);
    }
    else
        send = makeToken(id,slovo);
    arrayInsert(a, *send);
    freeStr(slovo);
    return x;
}

char Number(char x,dynArr *a){
    token * send;
    dynStr *number = malloc(sizeof (dynStr));
    initStr(number);
    addToStr(number, &x);
    x = getchar();
    while(isdigit(x)){
        addToStr(number,&x);
        x = getchar();
    }
    if(isDot(x)) {
        return Double(number, a);
    }
    else
        if (isE(x))
            return Exponent(number,a);
        else{
            send = makeToken(integer, number);
            arrayInsert(a, *send);
        }
    freeStr(number);
    return x;
}

char Double(dynStr *number, dynArr *a){
    addToStr(number, ".");
    char x = getchar();
    while(isdigit(x)){
        addToStr(number,&x);
        x = getchar();
    }
    if(isE(x))
        return Exponent(number, a);
    else{
        token * send = makeToken(ddouble, number);
        arrayInsert(a, *send);
    }
    freeStr(number);
    return x;
}

char Exponent(dynStr *number, dynArr *a){
    addToStr(number,"e");
    char x = getchar();
    if(isMinusPlus(x)){
        addToStr(number,&x);
        return Exponent2(number, a, x);
    }
    else{
        while (isdigit(x)){
            addToStr(number,&x);
            x = getchar();
        }
    }
    token * send = makeToken(exponent, number);
    arrayInsert(a, *send);
    freeStr(number);
    return x;
}

char Exponent2(dynStr *number, dynArr *a,char x){
    addToStr(number,&x);
    x = getchar();
    while(isdigit(x)){
        addToStr(number,&x);
        x = getchar();
    }
    token * send = makeToken(exponent, number);
    arrayInsert(a, *send);
    freeStr(number);
    return x;
}

char String(char x, dynArr *a){
    dynStr *slovo = malloc(sizeof (dynStr));
    initStr(slovo);
    x = getchar();
    while (!isQuot(x)){
        if(isBackslash(x)){
            addToStr(slovo,&x);
            char *sekv = esc1(x);
            addToStr(slovo, sekv);
        }
        else
            addToStr(slovo,&x);
        x = getchar();
    }
    token * send = makeToken(string,slovo);
    arrayInsert(a, *send);
    freeStr(slovo);
    return getchar();
}

char * esc1(char x){
    x = getchar();
    char *xptr;
    if(x == 'n' || x == 't'){
        xptr = &x;
        return xptr;
    }
    if(x>'2' && x<'9') {
        Error++;
        xptr = &x;
        return xptr;
    }
    else
        return esc2(x);
}

char * esc2(char x){
    char y = getchar();
    if(x == '2') {
        if (y > 5) {
            Error++;
            char *xptr[2] = {&x, &y};
            return *xptr;
        }
    }
    return esc3(x,y);
}

char * esc3(char x, char y){
    char z = getchar();
    if(x == '2' && y == '5')
        if(z>5)
            Error++;
    char *xptr[3] = {&x,&y,&z};
    return *xptr;
}

char Operator(char x, dynArr *a){
    char tmp = x;
    x = getchar();
    if(isEqual(x) && tmp == '=' || isSlash(x) && tmp == '/'){
        return Operator2(tmp,x,a);
    }
    dynStr *operator1 = malloc(sizeof (dynStr));
    initStr(operator1);
    addToStr(operator1, &tmp);
    token * send = makeToken(operator, operator1);
    arrayInsert(a, *send);
    freeStr(operator1);
    return x;
}

char Operator2(char x, char y, dynArr *a){
    printf("calling operator2\n");
    dynStr *sekvence = malloc(sizeof (dynStr));
    initStr(sekvence);
    addToStr(sekvence, &x);
    addToStr(sekvence, &y);
    token * send = makeToken(operator, sekvence);
    arrayInsert(a, *send);
    freeStr(sekvence);
    return getchar();
}

token * makeToken(int type, dynStr *value){
    token *send = malloc(sizeof (token));
    if(!send){
        printf("Error\n");
        return NULL;
    }
    send->type = type;
    send->value = value;
    printToken(*send);
    return send;
}
//debug
void debug(dynArr *a){
    for (size_t i = 0; i < sizeof(a->array) - 1; i++)
    {
        printf("Token type: %i\t", a->array->type);
        printf("Token value: %s\n", a->array[i].value->str);
    }
}
void printToken(token tok){
    printf("Token: %i, value %s\n", tok.type, tok.value->str);
}