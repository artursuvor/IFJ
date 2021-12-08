#ifndef HEADER_TEST
#define HEADER_TEST

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>

#define PREC_SIZE 7
#define MAX_STACK 101

enum tokenType {keyword, id, string, operator, integer, ddouble, exponent, left_bracket, right_bracket, t_EOF, t_EOL, equal, add, sub, mul, t_div};


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


typedef struct {
    char *str;
    int len;
    int all_len;
} dynStr;

typedef struct{
    int type;
    dynStr *value;
} token_t;


typedef struct
{
    token_t *array;
    int used;
    int size;
} dynArr;

//itemy vkládané na stack
typedef struct {
    token_t *token;         //zpracovávaný token
    stack_item_type type;   //typ tokenu pro PSA
} stack_item;

typedef struct{
    int top;    
    stack_item *data[MAX_STACK];
} TStack;


typedef int* symtable_value_t;

typedef struct symtable_node {
	char *key;
	symtable_value_t value;
    struct symtable_node * lptr;
	struct symtable_node * rptr;
} symtable_node_t;	

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
bool isLine(char x);


//inicializace dynamického stringu
//délka řetězce je nastavena na 1
//a ukončující znak je vložen na konec stringu
void initStr(dynStr *str);

//uvolnění z paměti
void freeStr(dynStr *str);

//přidání nového řetězce do původního a
//přepsání velikosti
void addToStr(dynStr *str, char c);

void addStrToStr(dynStr *str, char *c);

//základní inicializace dynamického pole
int arrayInit(dynArr *array);

//vložení do pole
void arrayInsert(dynArr *array, token_t token);

//uvolnění paměti po použití pole
void freeArray(dynArr *array);


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

token_t get_next_token();

void check_identifier(char* name );

void process_nested_commands(int option);

void check_function_def(int option);

void check_basic_bool_expression();

int check_if_statement(int mode);

int check_while_statement(int mode);

void process_custom_or_built_in_function(int expected_parameters_count);

void process_left_bracket();

int process_keyword(token_t t);

void check_assign(int operands_count);

void check_aritmetic_expression(int option);

int check_operator(token_t t);

void check_function_declaration(char* name);

void parser_start(dynArr *list);
                                                                                          

symtable_node_t *symtable_init();

bool symtable_search(symtable_node_t *root_pointer, char *key, symtable_value_t value);

void symtable_insert(symtable_node_t **root_pointer, char *key, symtable_value_t value);

symtable_value_t get_symtable_value(symtable_node_t *root_pointer, char *key, symtable_value_t value);

//konverze token->type na type pro precedenční analýzu
precedence_table_i token_type_to_symbol(token_t *token, TStack *stack);

//hlavní funkce precedenční analýzy
void precedence_analysis(dynArr *token_array);

void shift_operation(token_t *token, precedence_table_i *currentTokenIndex, TStack *stack);

void shift_stop_operation(token_t *token, precedence_table_i *currentTokenIndex, TStack *stack);

token_t get_next_token(dynArr *array, int *position);

void reduce_operation(token_t *token, precedence_table_i *currentTokenIndex, TStack *stack);



//basic stack functions
TStack* initStack();

int isFull(TStack *s);

int isEmpty(TStack *s);

void stack_push(TStack *s, stack_item *item);

stack_item *pop(TStack *s);

stack_item* top_item(TStack *s);

int top_index(TStack *s);

int term_index(TStack *s);

void free_stack(TStack *s);

#endif //IFJ_SCANNER_H
