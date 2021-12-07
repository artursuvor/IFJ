#include <stdio.h>
#include <stdlib.h>

#include "scanner.h"
#include "symtable.h"
#include "list.h"
#include "scanner.c"
#include "syntax.h"


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

symtable_node_t *table;
list *main_list;

/*
	Funkce zkontroluje kod po tom co dostane identifikator.
*/

void check_identifier() {
	token next_token;
	next_token = get_next_token(); //TODO get_next_token() jste smazali, nikde ji nevidím

	list_insert_last(main_list, next_token);

	switch (next_token.type)
	{
		case t_EOL:
			break;
		case tkn_identifier: //TODO neexistuje
		case integer:
		case string:
		case ddouble:
		case nil: //TODO neexistuje
			int parameters_count = 0; // TODO Find Function in a function table and return number of parameters!
			check_function_def();
			// built_in_function_call_check(parameters_count);
			break;
		case left_bracket:
			int parameters_count = 0; // TODO Find Function in a function table and return number of parameters!
			built_in_function_call_check(parameters_count);
			break;
		case equal:
			check_assign();
			break;
		case add:
		case sub:
		case mul:
		case div:
			check_aritmetic_expression();
			break;
		default:
			printf("Identifier check error");
	}
}

void check_function_def() {
	token_t next_token; //TODO token_t neexistuje
	next_token = get_next_token();
	list_insert_last(main_list, t); //TODO t not defined

	switch(next_token.type) {
		case t_EOF:
			printf("EOF error");
			break;
		case identifier: //TODO neexistuje
			symtable_value_t value_by_key;
			value_by_key = my_malloc(sizeof(int));
			if (symtable_search(table, next_token.value, value_by_key) == true)
				printf("Function was already defined!");
			symtable_insert(&table, t.value, param_cnt);s //TODO typo chyby
			break;
		default:
			printf("Function def error!");

	}

	t = get_next_token();
	list_insert_last(global_list, t);
	if (t.type != tkn_left_bracket) //TODO neexistuje
		syntax_error("expected '('");
	//pokud 't.type' byla '('


	params_func(param_cnt);

	inside_commands(END_END);
	//EOL
	t = get_next_token();
	list_insert_last(global_list, t);
	if (t.type == tkn_end_of_file) //TODO neexistuje
		syntax_error("unexpected eof");
	else if (t.type != tkn_new_line) //TODO neexistuje
		syntax_error("expected EOL");
}


/*
	Funkce zkontroluje syntaxe zakladniho bool vyrazu.
*/


void check_basic_bool_expression() {
	token_t next_token; //TODO neexistuje
	next_token = get_next_token();
	list_insert_last(main_list, next_token);

	switch(next_token.type) {
		case identifier: //TODO neexistuje
		case integer:
		case ddouble:
		case string:
		case nil: //TODO neexistuje
			token another_token;
			another_token = get_next_token();
			list_insert_last(main_list, another_token);

			switch(another_token.type) {
				case double_equal: //TODO neexistuje
				case greater: //TODO neexistuje
				case greater_or_equal: //TODO neexistuje
				case less: //TODO neexistuje
				case less_or_equal: //TODO neexistuje
				case not: //TODO neexistuje
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
	
	switch (mode)
	{
		case BASIC_IF:
			check_basic_bool_expression();

			token_t next_token; //TODO neexistuje
			next_token = get_next_token();
			list_insert_last(main_list, next_token);


			switch(next_token.type) {
				case keyword:
					if ((int k = process_keyword()) == THEN_KEYWORD) {
						token another_token;
						another_token = get_next_token;
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
		break;

		case EXPECTING_ELSE_OR_END:
			token next_token;
			next_token = get_next_token();
			if (next_token.type != t_EOL) {
				printf ("EOL expecting after else! \n");
			}
			return EXPECTING_END;	
		
		case EXPECTING_END:
			token next_token;
			next_token = get_next_token();
			if (next_token.type != t_EOL) {
				printf ("EOL expecting after end! \n");
			}
			return 0;	
		default:
			return 0;	
	}
	}
}


/*
	Funkce zkontroluje syntaxe prikazu while.
*/
void check_while_statement(int mode) {

	switch (mode) {
		case BASIC_WHILE:
			check_basic_bool_expression();

			token_t next_token;
			next_token = get_next_token();
			list_insert_last(main_list, next_token);


			switch(next_token.type) {
				case keyword:
					if ((int k = process_keyword()) == DO_KEYWORD) {
						token another_token;
						another_token = get_next_token;
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
		break;
		case EXPECTING_END:
			token next_token;
			next_token = get_next_token();
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
	next_token = get_next_token();
	list_insert_last(main_list, next_token);

	if (next_token.type != right_bracket) {
		if(next_token.type == identifier || next_token.type == integer || next_token.type == ddouble || next_token.type == string || next_token.type == nil) {
			process_custom_or_built_in_function(expected_parameters_count--);
		}
		else {
			printf("Unexpected token type at function parameters");
		}
	}
	else if(next_token.type == right_bracket) {
		if (expected_parameters_count <= 0) { // Protoze funkce muze byt volana s vetsim mnozstvim parametru
			token another_token;
			another_token = get_next_token();
			list_insert_last(main_list, another_token);
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
	next_token = get_next_token();
	list_insert_last(main_list, next_token);

	switch(next_token.type) {
		case identifier:
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

void process_inner_expression(int type) {
	token_t next_token;
	switch (type)
	{
	// case END_END:
	// 	do
	// 	{
			
	// 	break;
	case END_ELSE:
		do
		{
			t = get_next_token();
			list_insert_last(global_list, t);
			switch (t.type)
			{
			case identifier:
				id_came(t);
				break;
			case t_EOL:
				continue;
			case keyword:
				int keyword = process_keyword();
				switch(keyword) {
					case IF_KEYWORD:
						check_if_statement();
						break;
					case WHILE_KEYWORD:
						check_while_statement();
						break;
					case END_KEYWORD:
						break;
					default:
						printf("Unknown keyword error!");
				}
				break;
			case built_in_function:
				t = get_next_token();
				list_insert_last(global_list, t);
				if (t.type == tkn_end_of_file)
					syntax_error("unexpected EOF");
				else if (t.type == tkn_left_bracket)
					call_func(RBRACKET);
				else if (t.type == tkn_identifier || t.type == tkn_integer || t.type == tkn_key_nil || t.type == tkn_string || t.type == tkn_double)
					call_func(NOBRACKET);
				else if (t.type == tkn_new_line)
					break;
				else
					syntax_error("wrong parametrs of builtin function");
				break;
			case integer:
			case ddouble:
			case string:
			case nil:
				t = get_next_token();
				list_insert_last(global_list, t);
				if (t.type == tkn_end_of_file)
					syntax_error("unexpected EOF");
				else if (t.type == tkn_new_line)
					continue;
				else if (t.type == add || t.type == sub || t.type == mul || t.type == div)
					expr_aritmetic(NOBRACKET);
				else
					printf("expected EOL or expression after item (inside if)");
				break;
			default:
				printf("expected keyword 'else'");
				break;
			}

		} while (next_token.type != keyword); // ELSE KEYWORD
		break;
	}
}

/**
	Funkce zkontroluje prikaz prirazeni
	@param operands_count - pocet ocekavanych operandu
*/

void function check_assign(int operands_count) {
	token_t t, u;
	
	list *local_list;
	int cnt_operands = 0;
		while (operands_count != 0) {
			t = get_next_token();
			list_insert_last(main_list, t);
			switch (t.type) {
				case identifier:
					check_assign(operands_count--);
					break;
				case left_bracket:
					process_left_bracket();
				case keyword():
					if(strcmp(t.value, "function") == 0) {
						process_function_call();
					}
					else {
						printf("Chyba u assign keyword!\n");
					}
				case integer:
				case ddouble:
				case string:
				case nil:
					check_assign(operands_count--);
					break;
				case add:
				case sub:
				case ddiv:
				case mul:
					check_aritmetic_expression();
					break;
				case reads:
				case readi:
				case readn:
				case write:
				case tointeger:
				case substr:
				case ord:
				case chr:
					built_in_function_call_check();
				case t_EOL:
					if (operands_count != 0) {
						printf("Wrong count of operators at assign!");
					}
				default:
					printf("assign_syntax_error!\n");
		}
	}

}
/**
	Funkce pro kontrolu aritmetickych vyrazu. Ma 2 scenaria: pokud ocekava pravou zavorku nebo pokud ne.
*/


void check_aritmetic_expression(int option) {
	
	if(option == NO_BRACKET) {
		token next_token;
		next_token = get_next_token();
		list_insert_last(main_list, next_token);
		switch (t.type) {
			case identifier:
			case integer:
			case ddouble:
			case string:
			case nil:
				token another_token;
				another_token = get_next_token();
				list_insert_last(main_list, another_token);
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
		next_token = get_next_token();
		list_insert_last(main_list, next_token);

		switch(next_token.type) {
			case right_bracket:
				break;
			case identifier:
				token another_token;
				another_token = get_next_token();
				list_insert_last(main_list, another_token);
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
				token another_token;
				another_token = get_next_token();
				list_insert_last(main_list, another_token);
				if(another_token.type != identifier) {
					printf("double operator syntax error!\n");
				}
				check_aritmetic_expression(EXPECTING_RIGHT_BRACKET);

		}
		return;
	}
}

/**
	Hlavni funkce parseru. Nastavuje listy a tabulky
*/

void parser_start() {


    token t;
	table = symtable_init();
	list main_list = init_list();
	list function_list = init_list();

	while ((t.type) != t_EOF) {
		switch (t.type)
		{
            case t_EOL:
			    continue;
            case t_EOF:
			    break;
            case identifier:
			    check_identifier();
			    break;
            case keyword:
			    check_function_def();
			    break;
		    case if_state:
			    check_if_statement();
			    break;
		    case while_state:
			    check_while_statement();
			    break;
		    case integer:
		    case ddouble:
		    case string:
		    case nil:
			    t = get_next_token();
			    list_insert_last(main_list, t);
			    if (t.type == add || t.type == sub || t.type == mul || t.type == div)
				    check_aritmetic_expression();
			    else if (t.type == t_EOL)
				    continue;
			    else
				    printf("unexpected token after item");
			    break;
            case left_bracket:
			    process_left_bracket();
			    break;
		    case reads:
			case readi:
			case readn:
			case write:
			case tointeger:
			case substr:
			case ord:
			case chr:
				int parameters_count = 0; // TODO Find Function in a function table and return number of parameters!
			    built_in_function_call_check(parameters_count);
			    break;
		    default:
			    printf("Neznamy typ tokenu");
			break;
		    }
        }
    }
	semantic_start(main_list, symtable);
}