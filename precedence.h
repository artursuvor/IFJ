//Precedenční analýza
//Autor: Matěj Novák - xnovak2q


#ifndef IFJ_PSA_H
#define IFJ_PSA_H

#define PREC_SIZE 7

#include <stdio.h>
#include <stdlib.h>

#include "scanner.h"
#include "symtable.h"
#include "syntax.h"
#include "basicStackFunctions.h"

//symboly precedenční tabulky
typedef enum {
    PLUS_MINUS, // +-  (0)
    MUL_DIV,    // */  (1)
    L_BRACKET,  // (   (2)
    R_BRACKET,  // )   (3)
    LOGIC,      // log (4)
    DOLLAR,     // $   (5)
    OPERAND     // i   (6)
} precedence_table_i;

//symboly na stacku
typedef enum {
    EOS,     // konec stacku $
    START,   // začátek výrazu (exp)
    TERM,    // terminal
    NON_TERM // neterminal
} stack_item_type;

//itemy vkládané na stack
typedef struct {
    token_t *token;         //zpracovávaný token
    stack_item_type type;   //typ tokenu pro PSA
} stack_item;


//konverze token->type na type pro precedenční analýzu
precedence_table_i token_type_to_symbol(token_t *token, TStack *stack);

//hlavní funkce precedenční analýzy
void precedence_analysis(dynArr *token_array);

void shift_operation(token_t token, precedence_table_i *currentTokenIndex, TStack *stack);

void shift_stop_operation(token_t token, precedence_table_i *currentTokenIndex, TStack *stack);

token_t get_next_token(dynArr *array, int *position);

void reduce_operation(token_t token, precedence_table_i *currentTokenIndex, TStack *stack);

#endif //IFJ_PSA_H