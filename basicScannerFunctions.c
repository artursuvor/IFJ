//
// Created by Lakluk on 26.10.2021.
//

#include "header_test.h"

const char *keywords[] = {
"do", "else", "end", "function", "global", "if", "integer", "local", "nil", "number", "require", "return", "string", "then", "while"
};

bool isLetterUnder(char x){
    return isalpha(x) || x == '_';
}

bool isLetterUnderNumber(char x){
    return isLetterUnder(x) || isdigit(x);
}
bool isKeyword(dynStr *x){
    for(int i = 0; i < 15; i++){
        if(!strcmp(x->str, keywords[i]))
            return true;
    }
    return false;
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
bool isOpenBracket(char x){
    return x == '[';
}
bool isCloseBracket(char x){
    return x == ']';
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
        case ',':
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

void skipLineComment(){
    char x = getchar();
    while(x != '\n'){
        x = getchar();
        }
}

void skipBlockComment(){
    char x = getchar();
    while (true){
        if(isCloseBracket(x)){
            x = getchar();
            if(isCloseBracket(x))
                break;
        }
    }
}

bool isLine(char x){
    return x == '\n';
}