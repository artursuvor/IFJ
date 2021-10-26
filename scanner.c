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
#include "dynArr.c"

enum tokenType{keyword, id, string, operator, integer, ddouble, exponent};

int Error = 0;
//tělo hlavní funkce Scanner
int main(){
    dynArr *array;
    arrayInit(array);
    char vstup = getchar();
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
                    if(isOperator(vstup))
                        vstup = Operator(vstup, array);
                    else
                        if(isEOF(vstup))
                            konec = true;
                        else
                            if(isspace(vstup))
                                vstup = getchar();
                            else{
                                freeArray(array);
                                Error++;
                                if(Error>=1)
                                return 1;
                            }
    }
    freeArray(array);
    if (Error>=1)
        return 1;
    return 0;
}

//Samotné funkce potřebné pro scanner

char Word(char x,dynArr *a){
    struct Token * send;
    char slovo[] = {x};
    x = getchar();
    while (isLetterUnderNumber(x)){
        strcat(slovo, &x);
        x = getchar();
    }
    if(isKeyword(slovo)) {
        send = makeToken(keyword, slovo);
    }
    else
        send = makeToken(id,slovo);
    arrayInsert(a,send);
    return x;
}

char Number(char x,dynArr *a){
    struct Token * send;
    char number[] = {x};
    x = getchar();
    while(isdigit(x)){
        strncat(number, &x, 1);
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
            arrayInsert(a,send);
        }
    return x;
}

char Double(char *number, dynArr *a){
    strcat(number, ".");
    char x = getchar();
    while(isdigit(x)){
        strncat(number, &x, 1);
        x = getchar();
    }
    if(isE(x))
        return Exponent(number, a);
    else{
        struct Token * send = makeToken(ddouble, number);
        arrayInsert(a,send);
    }
    return x;
}

char Exponent(char *number, dynArr *a){
    strcat(number, "e");
    char x = getchar();
    if(isMinusPlus(x)){
        strcat(number,&x);
        return Exponent2(number, a);
    }
    else{
        while (isdigit(x)){
            strcat(number, &x);
            x = getchar();
        }
    }
    struct Token * send = makeToken(exponent, number);
    arrayInsert(a, send);
    return x;
}

char Exponent2(char *number, dynArr *a){
    char x = getchar();
    while(isdigit(x)){
        strcat(number,&x);
        x = getchar();
    }
    struct Token * send = makeToken(exponent, number);
    arrayInsert(a, send);
    return x;
}

char String(char x, dynArr *a){
    char *slovo;
    x = getchar();
    while (!isQuot(x)){
        if(isBackslash(x)){
            strcat(slovo, &x);
            char *sekvence = esc1();
            strcat(slovo, sekvence);
        }
        else
            strcat(slovo, &x);
        x = getchar();
    }
    struct Token * send = makeToken(string,slovo);
    arrayInsert(a, send);
    return getchar();
}

char * esc1(){
    char x = getchar();
    if(x>2) {
        Error++;
        return esc2(x);
    }
    else
        return esc2(x);
}

char * esc2(char x){
    char y = getchar();
    if(x>2)
        if(y>5)
            Error++;
    return esc3(x,y);
}

char * esc3(char x, char y){
    char z = getchar();
    if(x == '2')
        if(z>5)
            Error++;
    char *sekvence;
    strcat(sekvence, &x);
    strcat(sekvence, &y);
    strcat(sekvence, &z);
    return sekvence;
}

char Operator(char x, dynArr *a){
    char operator1 = x;
    x = getchar();
    if(isEqual(x) && operator1 == '=' || isSlash(x) && operator1 == '/'){
        return Operator2(operator1,x,a);
    }
    struct Token * send = makeToken(operator, &operator1);
    arrayInsert(a,send);
    return x;
}

char Operator2(char x, char y, dynArr *a){
    char sekvence[2] = {x,y};
    struct Token * send = makeToken(operator, sekvence);
    arrayInsert(a, send);
    return getchar();
}

struct Token * makeToken(int type, char *value){
    struct Token *send = malloc(sizeof (struct Token));
    send->type = type;
    send->value = value;
    return send;
}