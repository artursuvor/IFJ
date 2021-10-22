//
// Created by Lakluk on 22.10.2021.
//

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>

//struktura tokenu
struct Token {
    int type;
    char value[];
} token;

//fronta tokenů
struct Fronta{
    token rada[];
} fronta;

enum tokenType{keyword, id, string, operator, integer, ddouble, exponent};

//globální proměnné
bool konec = false;
struct Fronta queue;

//definice funkcí potřebných pro scanner
bool isLetterUnder(char x);
bool isLetterUnderNumber(char x);
bool isKeyword(char x[]);
bool isQuot(char x);
bool isBackslash(char x);
bool isNumber(char x);
bool isDot(char x);
bool isE(char x);
bool isMinus(char x);
bool isOperator(char x);
bool isEqualSlash(char x);
bool isWhitespace(char x);
bool isEOF(char x);
void Word(char x); //done
void Number(char x); //done
void String(char x); //done
void Operator(char x); //done
void makeToken(int type, char value[]);
void addToQueue(struct Token send);
void Double(char number[]); //done
void Exponent(char number[]); //work in progress
void Exponent2(char x, char number[]);
char * esc1(); //done
char * esc2(char x); //done
char * esc3(char x, char y); //done
void Operator2(char x, char y); //done

//tělo hlavní funkce Scanner
int Scanner(){
    char vstup = getchar();
    konec = false;
    while(!konec){
        if(isLetterUnder(vstup))
            Word(vstup);
        else
            if(isNumber(vstup))
                Number(vstup);
            else
                if(isQuot(vstup))
                    String(vstup);
                else
                    if(isOperator(vstup))
                        Operator(vstup);
                    else
                        if(isEOF(vstup))
                            konec = true;
                        else
                            if(isWhitespace(vstup))
                                vstup = getchar();
                            else
                                return 1;
    }
    return 0;
}

//Samotné funkce potřebné pro scanner

void Word(char x){
    char slovo[] = x;
    x = getchar();
    while (isLetterUnderNumber(x)){
        strncat(slovo, &x, 1);
        x = getchar();
    }
    if(isKeyword(slovo))
        struct token send = makeToken(keyword,slovo);
    else
        struct token send = makeToken(id,slovo);
    addToQueue(send);
}

void Number(char x){
    struct token send;
    char number[] = x;
    x = getchar();
    while(isNumber(x)){
        strncat(number, &x, 1);
        x = getchar();
    }
    if(isDot(x)) {
        Double(number);
    }
    else
        if (isE(x))
            Exponent(number);
        else{
            send = makeToken(integer, number);
            addToQueue(send);
        }
    return;
}

void Double(char  number[]){
    char x = getchar();
    while(isNumber(x)){
        strncat(number, &x, 1);
        x = getchar();
    }
    if(isE(x))
        Exponent(number);
    else{
        struct Token send = makeToken(ddouble, number);
        addToQueue(send);
    }
    return;
}

void Exponent(char number[]){
    char x =
}

void String(char x){
    char slovo[];
    x = getchar();
    while (!isQuot(x)){
        if(isBackslash(x)){
            strcat(slovo, &x,1);
            char sekvence[3] = esc1();
            strcat(slovo, &sekvence, 3);
        }
        else
            strcat(slovo, &x, 1);
        x = getchar();
    }
    struct Token send = makeToken(string,slovo);
    addToQueue(send);
}

char * esc1(){
    char x = getchar();
    if(x>2)
        //error
    else
        return esc2(x);
}

char * esc2(char x){
    char y = getchar();
    if(x>2)
        if(y>5)
            //error
    return esc3(x,y);
}

char * esc3(char x, char y){
    char z = getchar();
    if(&x == "2")
        if(z>5)
            //error
    char sekvence[3] = {x,y,z};
    return sekvence;
}

void Operator(char x){
    char operator1 = x;
    x = getchar();
    if(isEqualSlash(x)){
        Operator2(operator1,x);
    }
    struct Token send = makeToken(operator, &operator1);
    addToQueue(send);
}

void Operator2(char x, char y){
    char sekvence[2] = {x,y};
    struct Token send = makeToken(operator, sekvence);
    addToQueue(operator, send);
}

