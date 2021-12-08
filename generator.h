/*
*Téma:              Generovanie cieloveho kodu
*varianta:          Tym 069, varianta 1
*clenovia:          xsuvor00 - veduci
*                   xnovak2q
*                   xfuisl00                   
*                   xcicmi00
*skola:             Vysoke uceni technicke v Brne - FIT
*datum vytvorenia:  1.12.2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "scanner.h"


void start();
void clears();
void defvar();
void call(token_t tok);
void move(token_t src, token_t dst, bool in_function, bool is_const);
void f_begin(token_t tok);
void f_end();
void ifjcode_main();
void concat(token_t tok1, token_t tok2, bool in_function);
void arithmetic_operation(token_t t_type, token_t tok1, token_t tok2, bool in_function);
void relational_operation(token_t t_type, token_t tok1, token_t tok2, bool in_function);

// if start 
void if_begin(token_t label, token_t result, bool in_function);
// else
void else_label(token_t label);  
// if end
void if_end(token_t label);
// print
void ifjcode_write(token_t tok, bool in_function, bool is_const);
   
