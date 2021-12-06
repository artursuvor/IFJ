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
void call(token tok);
void move(token src, token dst, bool in_function, bool is_const);
void f_begin(token tok);
void f_end();
void ifjcode_main();
void concat(token tok1, token tok2, bool in_function);
void arithmetic_operation(token t_type, token tok1, token tok2, bool in_function);
void relational_operation(token t_type, token tok1, token tok2, bool in_function);

// if start 
void if_begin(token label, token result, bool in_function);
// else
void else_label(token label);  
// if end
void if_end(token label);
// print
void ifjcode_write(token tok, bool in_function, bool is_const);
   
