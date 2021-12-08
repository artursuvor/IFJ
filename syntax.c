#include <stdio.h>
#include <stdlib.h>

#include "scanner.h"
#include "symtable.h"
// #include "list.h"
#include "scanner.c"
#include "syntax.h"
#include "dynArr.h"


#define IF_KEYWORD 201
#define WHILE_KEYWORD 202
#define END_KEYWORD 203
#define DO_KEYWORD 204
#define ELSE_KEYWORD 205
#define FUNCTION_KEYWORD 206
#define GLOBAL_KEYWORD 207
#define LOCAL_KEYWORD 208
#define REQUIRE_KEYWORD 209
#define RETURN_KEYWORD 210
#define THEN_KEYWORD 211


#define EXPECTING_RIGHT_BRACKET 301
#define NO_BRACKET 302

#define EXPECTING_ELSE_OR_END 401
#define EXPECTING_END 402
#define BASIC_IF 403
#define BASIC_WHILE 404

#define DECLARATION 501
#define WITH_BRACKET 502

#define DOUBLE_EQUAL 601
#define GREATER 602
#define GREATER_OR_EQUAL 603
#define LESS 604
#define LESS_OR_EQUAL 605
#define NOT 606

#define FUNCTION_START 701
#define RETURN_EXPECTING 702
#define END_EXPECTING 703

symtable_node_t *table;

dynArr *incoming_list;

dynArr *main_list;
arrayInit(main_list);
int global_dynamic_array_position = 0;

/*
	Funkce zkontroluje kod po tom co dostane identifikator.
*/

void check_identifier(dynStr name ) {
	token next_token;
	global_dynamic_array_position+=1;
	next_token = get_next_token(incoming_list, global_dynamic_array_position);

	arrayInsert(main_list, next_token);

	symtable_value_t value;
	switch (next_token.type)
	{
		case t_EOL:
			break;
		case id:
		case integer:
		case string:
		case ddouble:
			check_function_def(FUNCTION_START);
			break;
		case left_bracket:
			value = malloc(sizeof(int));
			value = get_symtable_value(table, next_token.value, value);
			int *parameters_count = *value;
			built_in_function_call_check(parameters_count);
			break;
		case equal:
			check_assign(0);
			break;
		case add:
		case sub:
		case mul:
		case ddiv:
			check_aritmetic_expression(NO_BRACKET);
			break;
		case keyword:
			if(process_keyword(next_token) == FUNCTION_KEYWORD) {
				check_function_declaration(name);
			}
		default:
			printf("id check error");
	}
}


void process_nested_commands(int option) {
	token t;
	int k;
	switch (option) {
		case RETURN_EXPECTING:
			while (!(t.type == keyword && strcmp(t.value, "return")==0));
			{
				global_dynamic_array_position+=1;
				t = get_next_token(incoming_list, global_dynamic_array_position);
				arrayInsert(main_list, t);
				token another_token;
				switch (t.type)
				{
					case id:
						check_identifier(*t.value);
						break;
					case t_EOL:
						break;
					case keyword:
						k = process_keyword(t);
						if(k == IF_KEYWORD) {
							check_if_statement(BASIC_IF);
						}
						else if (k == WHILE_KEYWORD) {
							check_while_statement(BASIC_WHILE);
						}
						else if (strcmp(t.value, "nil") == 0) {
							token another_token;
							global_dynamic_array_position+=1;
							another_token = get_next_token(incoming_list, global_dynamic_array_position);
							arrayInsert(main_list, another_token);

							switch(another_token.type) {
								case add:
								case sub:
								case ddiv:
								case mul:
									check_aritmetic_expression(NO_BRACKET);
								case t_EOL:
									break;
								case t_EOF:
									printf("unexpected EOF");
									break;
								default:
									printf("SYNtax error!");
								break;
							}
						}
						else if (k == RETURN_KEYWORD) {
							break;
						}
						else {
							printf("Syntax error unknown keyword!");
						}
						break;
					
				
					// case tkn_key_inputf:
					// case tkn_key_inputi:
					// case tkn_key_inputs:
					// case tkn_key_print:
					// case tkn_key_length:
					// case tkn_key_substr:
					// case tkn_key_ord:
					// case tkn_key_chr:
					// t = get_next_token();
					// list_insert_last(global_list, t);
					// if (t.type == tkn_end_of_file)
					// 	syntax_error("unexpected EOF");
					// else if (t.type == tkn_left_bracket)
					// 	call_func(RBRACKET);
					// else if (t.type == tkn_identifier || t.type == tkn_integer || t.type == tkn_key_nil || t.type == tkn_string || t.type == tkn_double)
					// 	call_func(NOBRACKET);
					// else if (t.type == tkn_new_line)
					// 	break;
					// else
					// 	syntax_error("wrong parametrs of builtin function");
						// break;
					case integer:
					case ddouble:
					case string:
							global_dynamic_array_position+=1;
							another_token = get_next_token(incoming_list, global_dynamic_array_position);
							arrayInsert(main_list, another_token);

							switch(another_token.type) {
								case add:
								case sub:
								case ddiv:
								case mul:
									check_aritmetic_expression(NO_BRACKET);
								case t_EOL:
									break;
								case t_EOF:
									printf("unexpected EOF");
									break;
								default:
									printf("SYNtax error!");
								break;
							}

					default:
						syntax_error("expected return keyword");
						break;
					}
		}
			break;
		default:
			break;
	}
}

void check_function_def(int option) {
		symtable_value_t param_cnt;
			token next_token;
	switch(option) {
		case FUNCTION_START:
			global_dynamic_array_position+=1;
			next_token = get_next_token(incoming_list, global_dynamic_array_position);
			arrayInsert(main_list, next_token);
			token t;
			switch(next_token.type) {
				case t_EOF:
					printf("EOF error");
					break;
				case t_EOL:
					printf("EOL error");
					break;
				case id:
					param_cnt = my_malloc(sizeof(int));
					*param_cnt = 0;
					token t;
					global_dynamic_array_position+=1;
					t = get_next_token(incoming_list, global_dynamic_array_position);

					arrayInsert(main_list, t);
					if (t.type != left_bracket){
					printf("expected '('");
					}
					global_dynamic_array_position+=1;
					t = get_next_token(incoming_list, global_dynamic_array_position);
					arrayInsert(main_list, t);
					while (t.type != right_bracket){
						global_dynamic_array_position+=1;
						t = get_next_token(incoming_list, global_dynamic_array_position);
						arrayInsert(main_list, t);
						*param_cnt++;
					}
					symtable_insert(&table, next_token.value, param_cnt);
					check_function_def(FUNCTION_START);
					break;
					case integer:
					case ddouble:
					case string:
						global_dynamic_array_position+=1;
						t = get_next_token(incoming_list, global_dynamic_array_position);
						arrayInsert(main_list, t);
						if (t.type != t_EOL) {
							printf("Expecting EOL after function header");
						}
						check_function_def(RETURN_EXPECTING);
				default:
					printf("Function def error!");
			}
		break;
		case RETURN_EXPECTING:
			process_nested_commands(RETURN_EXPECTING);
		break;
		case END_EXPECTING:
			global_dynamic_array_position+=1;
			t = get_next_token(incoming_list, global_dynamic_array_position);
			arrayInsert(main_list, t);
			if (t.type == keyword && strcmp(t.value, "end") == 0) {
				global_dynamic_array_position+=1;
				t = get_next_token(incoming_list, global_dynamic_array_position);
				arrayInsert(main_list, t);
				if (t.type != t_EOL) {
					printf("Syntax error! EOL expecting!");
				}
			}
			else {
				printf("Syntax error, end expecting");
			}
			break;
		default:
			break;
	}
}


/*
	Funkce zkontroluje syntaxe zakladniho bool vyrazu.
*/


void check_basic_bool_expression() {
	token next_token;
	global_dynamic_array_position+=1;
	next_token = get_next_token(incoming_list, global_dynamic_array_position);
	arrayInsert(main_list, next_token);
	token another_token;

	switch(next_token.type) {
		case id:
		case integer:
		case ddouble:
		case string:
			global_dynamic_array_position+=1;
			another_token = get_next_token(incoming_list, global_dynamic_array_position);
			arrayInsert(main_list, another_token);

			switch(another_token.type) {
				case operator:
					check_basic_bool_expression();
				default:
					printf("Basic bool expression error! \n");
			}
	}
}


/*
	Funkce zkontroluje syntaxe prikazu if.
*/

int check_if_statement(int mode) {
	
						token another_token;
	switch (mode)
	{
		case BASIC_IF:
			check_basic_bool_expression();

			token next_token; //TODO neexistuje
			global_dynamic_array_position+=1;
			next_token = get_next_token(incoming_list, global_dynamic_array_position);
			arrayInsert(main_list, next_token);
			int k = 0;

			switch(next_token.type) {
				case keyword:
				k  = process_keyword(next_token);
					if (k == THEN_KEYWORD) {
						global_dynamic_array_position+=1;
						another_token = get_next_token(incoming_list, global_dynamic_array_position);
						if(another_token.type != t_EOL) {
							printf("Expecting EOL after then");
						}
						else {
							return EXPECTING_ELSE_OR_END;
						}
					}
					else {
						printf ("Unexpected keyword. Expected 'then'\n");
					}
				case t_EOL:
					printf("Unexpected EOL, missing 'then'\n");
				default:	
					printf("Unexpected token at if statement!\n");
					break;
			}

		case EXPECTING_ELSE_OR_END:
			// token next_token;
			global_dynamic_array_position+=1;
			next_token = get_next_token(incoming_list, global_dynamic_array_position);
			if (next_token.type != t_EOL) {
				printf ("EOL expecting after else! \n");
			}
			return EXPECTING_END;	
			break;
		
		case EXPECTING_END:
			global_dynamic_array_position+=1;
			next_token = get_next_token(incoming_list, global_dynamic_array_position);
			if (next_token.type != t_EOL) {
				printf ("EOL expecting after end! \n");
			}
			return 0;	
			break;
		default:
			return 0;	
	}
	
}


/*
	Funkce zkontroluje syntaxe prikazu while.
*/
void check_while_statement(int mode) {

	switch (mode) {
		case BASIC_WHILE:
			check_basic_bool_expression();
			int k =0;	
			token next_token;
			global_dynamic_array_position+=1;
			next_token = get_next_token(incoming_list, global_dynamic_array_position);
			arrayInsert(main_list, next_token);

			switch(next_token.type) {
				case keyword:
				k = process_keyword(next_token);
					if (k == DO_KEYWORD) {
						token another_token;
						global_dynamic_array_position+=1;
						another_token = get_next_token(incoming_list, global_dynamic_array_position);
						if(another_token.type != t_EOL) {
							printf("Expecting EOL after do");
						}
						else {
							return EXPECTING_END;
						}
					}
					else {
						printf ("Unexpected keyword. Expected 'end'\n");
					}
				case t_EOL:
					return EXPECTING_END;;
				default:	
					printf("Unexpected token at while statement!\n");
					break;
			}
		break;
		case EXPECTING_END:
			global_dynamic_array_position+=1;
			next_token = get_next_token(incoming_list, global_dynamic_array_position);
			if (next_token.type != t_EOL) {
				printf ("EOL expecting after end! \n");
			}
			return 0;	
		default:
			return 0;
	}
}

/**
	Funkce zkontroluje spravnost volani vestavenych a uzivatelem definovanych funkci.
*/

void process_custom_or_built_in_function(int expected_parameters_count) {
	token next_token;
	global_dynamic_array_position+=1;
	next_token = get_next_token(incoming_list, global_dynamic_array_position);
	arrayInsert(main_list, next_token);

	if (next_token.type != right_bracket) {
		if(next_token.type == id || next_token.type == integer || next_token.type == ddouble || next_token.type == string || (next_token.type == keyword && strcmp(next_token.value, "nil") == 0)) {
			process_custom_or_built_in_function(expected_parameters_count--);
		}
		else {
			printf("Unexpected token type at function parameters");
		}
	}
	else if(next_token.type == right_bracket) {
		if (expected_parameters_count <= 0) { // Protoze funkce muze byt volana s vetsim mnozstvim parametru
			token another_token;
			global_dynamic_array_position+=1;
			another_token = get_next_token(incoming_list, global_dynamic_array_position);
			arrayInsert(main_list, another_token);
			if(another_token.type != t_EOL) {
				printf("Unexpected token after right bracket!");
			}
			return;
		} 
		else {
			printf("Spatny pocet parametru u volani funkce!"); // Chyba 5
		}
	}
	
}
/**
	Funkce bude vyvolana v pripade ze typ tokenu bude leva zavorka. Bude hledat pravou zavorku/
*/
void process_left_bracket() {
	
	token next_token;
	global_dynamic_array_position+=1;
	next_token = get_next_token(incoming_list, global_dynamic_array_position);
	arrayInsert(main_list, next_token);

	switch(next_token.type) {
		case id:
		case add:
		case sub:
		case mul:
		case ddiv:
			process_left_bracket(NO_BRACKET);
		default:
			printf("Wierd left bracket error! \n");
	}

	check_aritmetic_expression(EXPECTING_RIGHT_BRACKET); // jinak pokrachujeme v hledani prave zavorky
}

int process_keyword(token t) {
	if(strcmp(t.value, "if") == 0) {
		return IF_KEYWORD;
	}
	else if(strcmp(t.value, "while") == 0) {
		return WHILE_KEYWORD;
	}
	else if(strcmp(t.value, "end") == 0) {
		return END_KEYWORD;
	}
	else if(strcmp(t.value, "function") == 0) {
		return FUNCTION_KEYWORD;
	}
	else if(strcmp(t.value, "global") == 0) {
		return GLOBAL_KEYWORD;
	}
	else if(strcmp(t.value, "local") == 0) {
		return LOCAL_KEYWORD;
	}
	else if(strcmp(t.value, "require") == 0) {
		return REQUIRE_KEYWORD;
	}
	else if(strcmp(t.value, "return") == 0) {
		return RETURN_KEYWORD;
	}
	else if(strcmp(t.value, "then") == 0) {
		return THEN_KEYWORD;
	}
	else if(strcmp(t.value, "do") == 0) {
		return DO_KEYWORD;
	}

}

/**
	Funkce zkontroluje prikaz prirazeni
	@param operands_count - pocet ocekavanych operandu
*/

void check_assign(int operands_count) {
	token t, u;
	
	list *local_list;
	int cnt_operands = 0;
		while (operands_count != 0) {
			global_dynamic_array_position+=1;
			t = get_next_token(incoming_list, global_dynamic_array_position);
			arrayInsert(main_list, t);
			switch (t.type) {
				case id:
					check_assign(operands_count--);
					break;
				case left_bracket:
					process_left_bracket();
				case keyword:
					if(strcmp(t.value, "function") == 0) {
						process_function_call();
					}
					else if(strcmp(t.value, "nil") == 0){
						check_assign(operands_count--);
					}
					else {
						printf("Chyba u assign keyword!\n");
					}
				case integer:
				case ddouble:
				case string:
					check_assign(operands_count--);
					break;
				case add:
				case sub:
				case ddiv:
				case mul:
					check_aritmetic_expression(NO_BRACKET);
					break;
				// case reads:
				// case readi:
				// case readn:
				// case write:
				// case tointeger:
				// case substr:
				// case ord:
				// case chr:
				// 	built_in_function_call_check();
				case t_EOL:
					if (operands_count != 0) {
						printf("Wrong count of operators at assign!");
					}
				default:
					printf("assign_printf!\n");
		}
	}

}
/**
	Funkce pro kontrolu aritmetickych vyrazu. Ma 2 scenaria: pokud ocekava pravou zavorku nebo pokud ne.
*/


void check_aritmetic_expression(int option) {
	
	if(option == NO_BRACKET) {
		token next_token;
		global_dynamic_array_position+=1;
		next_token = get_next_token(incoming_list, global_dynamic_array_position);
		arrayInsert(main_list, next_token);
		switch (next_token.type) {
			case id:
			case integer:
			case ddouble:
			case string:
			case keyword:
				if(next_token.type == keyword && strcmp(next_token.value, "nil") != 0) {
					printf("Spatny keyword\n");
				}
				token another_token;
				global_dynamic_array_position+=1;
				another_token = get_next_token(incoming_list, global_dynamic_array_position);
				arrayInsert(main_list, another_token);
				switch (another_token.type) {
					case t_EOL:
						break;
					case add:
					case sub:
					case mul:
					case ddiv:
						check_aritmetic_expression(NO_BRACKET);
					default:
						printf("assign syntax error! \n");
				}
				return;
		}
	}
	else if(option == EXPECTING_RIGHT_BRACKET) {
		token next_token;
		global_dynamic_array_position+=1;
		next_token = get_next_token(incoming_list, global_dynamic_array_position);
		arrayInsert(main_list, next_token);

		token another_token;
		switch(next_token.type) {
			case right_bracket:
				break;
			case id:
				global_dynamic_array_position+=1;
				another_token = get_next_token(incoming_list, global_dynamic_array_position);
				arrayInsert(main_list, another_token);
				switch(another_token.type) {
					case t_EOL:
						printf("Expecting right bracket syntax error! \n");
					case add:
					case sub:
					case mul:
					case ddiv:
						check_aritmetic_expression(EXPECTING_RIGHT_BRACKET);
					default:
						printf("Aritmetic expression at expecting right bracket 1!");
				}
				break;
			case add:
			case sub:
			case mul:
			case ddiv:
			case left_bracket:
				global_dynamic_array_position+=1;
				another_token = get_next_token(incoming_list, global_dynamic_array_position);
				arrayInsert(main_list, another_token);
				if(another_token.type != id) {
					printf("double operator syntax error!\n");
				}
				check_aritmetic_expression(EXPECTING_RIGHT_BRACKET);

		}
		return;
	}
}

int check_operator(token t) {
	if(strcmp(t.value, "==") == 0) {
		return DOUBLE_EQUAL;
	}
	else if (strcmp(t.value, ">") == 0) {
		return GREATER;
	}
	else if (strcmp(t.value, ">=") == 0) {
		return GREATER_OR_EQUAL;
	}
	else if (strcmp(t.value, "<") == 0) {
		return LESS;
	}
	else if (strcmp(t.value, "<=") == 0) {
		return LESS_OR_EQUAL;
	}
	else if (strcmp(t.value, "!") == 0) {
		return NOT;
	}
	else {
		return 0;
	}
}

void check_function_declaration(dynStr name) {
	token next_token;
	global_dynamic_array_position+=1;
	next_token = get_next_token(incoming_list, global_dynamic_array_position);
	symtable_value_t prmtr = my_malloc(sizeof(int));
	*prmtr = 0;

	if (symtable_search(table, next_token.value, 1) == true) {
		printf("SEMANTIC ERROR redefinition of function!");
	}
	if(next_token.type == left_bracket) {
		token another_token;
		global_dynamic_array_position+=1;
		another_token = get_next_token(incoming_list, global_dynamic_array_position);
		while (another_token.type != right_bracket) {
			global_dynamic_array_position+=1;
			another_token = get_next_token(incoming_list, global_dynamic_array_position);
			*prmtr++;
		}
		symtable_insert(table, name.str, prmtr);
	} else {
		printf("SYNTAX ERROR");
	}
}

/**
	Hlavni funkce parseru. Nastavuje listy a tabulky
*/
void parser_start(dynArr *list) {

	incoming_list = list;

    token t;
	table = symtable_init();

	while ((t.type) != t_EOF) {
		switch (t.type)
		{
            case t_EOL:
			    continue;
            case t_EOF:
			    break;
            case id:
			    check_identifier(*t.value);
			    break;
		    case keyword:
				if(process_keyword(t) == IF_KEYWORD) {
					check_if_statement(BASIC_IF);
				}
				else if (process_keyword(t) == WHILE_KEYWORD) {
					check_while_statement(BASIC_WHILE);
				}
			    else if (strcmp(t.value, "nil")==0) {
					token t;
					global_dynamic_array_position+=1;
					 t = get_next_token(incoming_list, global_dynamic_array_position);
			    	arrayInsert(main_list, t);
			    	if (t.type == add || t.type == sub || t.type == mul || t.type == ddiv)
				    	check_aritmetic_expression(NO_BRACKET);
			    	else if (t.type == t_EOL)
				    	continue;
			    	else
				    	printf("unexpected token after item");
					}
				else if(strcmp(t.value, "require") == 0) {
					global_dynamic_array_position++;
					continue;
				}
				else if(process_keyword(t) == GLOBAL_KEYWORD || process_keyword(t) == LOCAL_KEYWORD) {
					token t;
					global_dynamic_array_position+=1;
					t = get_next_token(incoming_list, global_dynamic_array_position);
					if (t.type == id) {
						check_identifier(*t.value);
					}
					else {
						printf("SYNTAX ERROR!");
					}
				}
				else if(process_keyword(t) == FUNCTION_KEYWORD) {
					check_function_def(FUNCTION_START);
				}
				else {
					printf("SYNTAX ERROR!");
				}
			    break;
		    case integer:
		    case ddouble:
		    case string:
				global_dynamic_array_position+=1;
			    t = get_next_token(incoming_list, global_dynamic_array_position);
			    arrayInsert(main_list, t);
			    if (t.type == add || t.type == sub || t.type == mul || t.type == ddiv)
				    check_aritmetic_expression(NO_BRACKET);
			    else if (t.type == t_EOL)
				    continue;
			    else
				    printf("unexpected token after item");
			    break;
            case left_bracket:
			    process_left_bracket();
			    break;
		    // case reads:
			// case readi:
			// case readn:
			// case write:
			// case tointeger:
			// case substr:
			// case ord:
			// case chr:
			// 	int parameters_count = 0; // TODO Find Function in a function table and return number of parameters!
			//     built_in_function_call_check(parameters_count);
			//     break;
		    default:
			    printf("Neznamy typ tokenu");
			break;
		}
    }
}
