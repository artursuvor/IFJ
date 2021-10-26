//
// Created by Lakluk on 26.10.2021.
//
#include <string.h>
#include <ctype.h>
#include "basicScannerFunctions.h"
bool isLetterUnder(char x){
    return isalpha(x) || x == '_';
}

bool isLetterUnderNumber(char x){
    return isLetterUnder(x) || isdigit(x);
}
bool isKeyword(char *x){
    return strcmp(x,"do"); // || strcmp()
}
bool isQuot(char x){
    return x =='"';
}
bool isBackslash(char x){
    return x == '\\';
}
bool isDot(char x){
    return x == '.';
}
bool isE(char x){
    return x == 'E' || x == 'e';
}
bool isMinus(char x){
    return x == '-';
}
bool isMinusPlus(char x){
    return isMinus(x) || x == '+';
}
bool isOperator(char x){
    switch (x) {
        case '#':
        case '*':
        case '(':
        case ')':
        case '>':
        case '<':
        case '~':
        case ':':
            return true;
        default:
            return isMinusPlus(x) || isEqual(x) || isSlash(x);
    }
}
bool isEqual(char x){
    return x == '=';
}
bool isSlash(char x){
    return x == '/';
}
bool isEOF(char x){
    return x == EOF;
}