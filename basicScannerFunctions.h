//
// Created by Lakluk on 26.10.2021.
//

#ifndef IFJ_BASICFUNCTIONS_H
#define IFJ_BASICFUNCTIONS_H
#include "dynStr.h"

bool isLetterUnder(char x);
bool isLetterUnderNumber(char x);
bool isKeyword(dynStr *x);
bool isQuot(char x);
bool isBackSlash(char x);
bool isDot(char x);
bool isE(char x);
bool isMinus(char x);
bool isOpenBracket(char x);
bool isCloseBracket(char x);
bool isMinusPlus(char x);
bool isOperator(char x);
bool isEqual(char x);
bool isSlash(char x);
bool isEOF(char x);
void skipLineComment();
void skipBlockComment();

#endif //IFJ_BASICFUNCTIONS_H
