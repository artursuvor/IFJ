#include "./scanner.h"
#include "symtable.h"

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
