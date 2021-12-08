#include "header_test.h"


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
int global_dynamic_array_position = 0;

/*
	Funkce zkontroluje kod po tom co dostane identifikator.
*/

void check_identifier(char* name ) {
	token_t next_token;

	token_t current_token;
	current_token = get_next_token(incoming_list, global_dynamic_array_position);

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
			*value = get_symtable_value(table, next_token.value, value);
			int *parameters_count = value;
			//built_in_function_call_check(parameters_count);
			break;
		case equal:
			check_assign(0);
			break;
		case add:
		case sub:
		case mul:
		case t_div:
			check_aritmetic_expression(NO_BRACKET);
			break;
		case keyword:
			if(process_keyword(next_token) == FUNCTION_KEYWORD) {
				check_function_declaration(name);
			}
		default:
			exit(2);
	}

	int *prmtr = malloc(sizeof(int));
	if(!prmtr) {
		exit(99);
	}
	*prmtr = 1;
	if(symtable_search(table, current_token.value, prmtr) == false) {
		symtable_insert(&table, current_token.value, 0);
	}
}


void process_nested_commands(int option) {
	token_t t;
	int k;
	switch (option) {
		case RETURN_EXPECTING:
			while (!(t.type == keyword && strcmp(t.value->str, "return")==0));
			{
				global_dynamic_array_position+=1;
				t = get_next_token(incoming_list, global_dynamic_array_position);
				arrayInsert(main_list, t);
				token_t another_token;
				switch (t.type)
				{
					case id:
						check_identifier(t.value->str);
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
						else if (strcmp(t.value->str, "nil") == 0) {
							token_t another_token;
							global_dynamic_array_position+=1;
							another_token = get_next_token(incoming_list, global_dynamic_array_position);
							arrayInsert(main_list, another_token);

							switch(another_token.type) {
								case add:
								case sub:
								case t_div:
								case mul:
									check_aritmetic_expression(NO_BRACKET);
								case t_EOL:
									break;
								case t_EOF:
									exit(2); //Necekany EOF
									break;
								default:
									exit(2);
								break;
							}
						}
						else if (k == RETURN_KEYWORD) {
							break;
						}
						else {
							exit(2); // Neznamy keyword!
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
					// if (t.type == tkn_end_of_file)
					// 	exit(2);
					// else if (t.type == tkn_left_bracket)
					// 	call_func(RBRACKET);
					// else if (t.type == tkn_identifier || t.type == tkn_integer || t.type == tkn_key_nil || t.type == tkn_string || t.type == tkn_double)
					// 	call_func(NOBRACKET);
					// else if (t.type == tkn_new_line)
					// 	break;
					// else
					// 	exit(2);
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
								case t_div:
								case mul:
									check_aritmetic_expression(NO_BRACKET);
								case t_EOL:
									break;
								case t_EOF:
									exit(2);
									break;
								default:
									exit(2);
								break;
							}

					default:
						exit(2);
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
			token_t next_token;
	switch(option) {
		case FUNCTION_START:
			global_dynamic_array_position+=1;
			next_token = get_next_token(incoming_list, global_dynamic_array_position);
			arrayInsert(main_list, next_token);
			token_t t;
			switch(next_token.type) {
				case t_EOF:
					exit(2);
					break;
				case t_EOL:
					exit(2);
					break;
				case id:
					param_cnt = malloc(sizeof(int));
					*param_cnt = 0;
					token_t t;
					global_dynamic_array_position+=1;
					t = get_next_token(incoming_list, global_dynamic_array_position);

					arrayInsert(main_list, t);
					if (t.type != left_bracket){
					exit(2); // Ocekava se '('
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
							exit(2); //Ocekava se EOL po function header
						}
						check_function_def(RETURN_EXPECTING);
				default:
					exit(2); //Chyba Function def!"
			}
		break;
		case RETURN_EXPECTING:
			process_nested_commands(RETURN_EXPECTING);
		break;
		case END_EXPECTING:
			global_dynamic_array_position+=1;
			t = get_next_token(incoming_list, global_dynamic_array_position);
			arrayInsert(main_list, t);
			if (t.type == keyword && strcmp(t.value->str, "end") == 0) {
				global_dynamic_array_position+=1;
				t = get_next_token(incoming_list, global_dynamic_array_position);
				arrayInsert(main_list, t);
				if (t.type != t_EOL) {
					exit(2); // EOL se ocekava
				}
			}
			else {
				exit(2); //  end se ocekava
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
	token_t next_token;
	global_dynamic_array_position+=1;
	next_token = get_next_token(incoming_list, global_dynamic_array_position);
	arrayInsert(main_list, next_token);
	token_t another_token;

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
					exit(2);
			}
	}
}


/*
	Funkce zkontroluje syntaxe prikazu if.
*/

int check_if_statement(int mode) {
	
	token_t another_token;
	switch (mode)
	{
		case BASIC_IF:
			check_basic_bool_expression();

			token_t next_token; //TODO neexistuje
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
							exit(2); //Ocekava se EOL po then
						}
						else {
							return EXPECTING_ELSE_OR_END;
						}
					}
					else {
						exit(2); // Necekany keyword. Expected 'then'
					}
				case t_EOL:
					exit(2); // Necekany EOL, chybi 'then'
				default:	
					exit(2); //Necekany token_t u if statement!
					break;
			}

		case EXPECTING_ELSE_OR_END:
			// token_t next_token;
			global_dynamic_array_position+=1;
			next_token = get_next_token(incoming_list, global_dynamic_array_position);
			if (next_token.type != t_EOL) {
				exit(2); // Ocekava se EOL po else! 
			}
			return EXPECTING_END;	
			break;
		
		case EXPECTING_END:
			global_dynamic_array_position+=1;
			next_token = get_next_token(incoming_list, global_dynamic_array_position);
			if (next_token.type != t_EOL) {
				exit(2); // Ocekava se EOL po endu! 
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
int check_while_statement(int mode) {

	switch (mode) {
		case BASIC_WHILE:
			check_basic_bool_expression();
			int k =0;	
			token_t next_token;
			global_dynamic_array_position+=1;
			next_token = get_next_token(incoming_list, global_dynamic_array_position);
			arrayInsert(main_list, next_token);

			switch(next_token.type) {
				case keyword:
				k = process_keyword(next_token);
					if (k == DO_KEYWORD) {
						token_t another_token;
						global_dynamic_array_position+=1;
						another_token = get_next_token(incoming_list, global_dynamic_array_position);
						if(another_token.type != t_EOL) {
							exit(2);
						}
						else {
							return EXPECTING_END;
						}
					}
					else {
						exit(2);
					}
				case t_EOL:
					return EXPECTING_END;
				default:	
					exit(2); // Necekany token po whilu
					break;
			}
		break;
		case EXPECTING_END:
			global_dynamic_array_position+=1;
			next_token = get_next_token(incoming_list, global_dynamic_array_position);
			if (next_token.type != t_EOL) {
				exit (2); //EOL se ocekava po end!
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
	token_t next_token;
	global_dynamic_array_position+=1;
	next_token = get_next_token(incoming_list, global_dynamic_array_position);
	arrayInsert(main_list, next_token);

	if (next_token.type != right_bracket) {
		if(next_token.type == id || next_token.type == integer || next_token.type == ddouble || next_token.type == string || (next_token.type == keyword && strcmp(next_token.value, "nil") == 0)) {
			process_custom_or_built_in_function(expected_parameters_count--);
		}
		else {
			exit(2); // Necekany token po parametrech funkce
		}
	}
	else if(next_token.type == right_bracket) {
		if (expected_parameters_count <= 0) { // Protoze funkce muze byt volana s vetsim mnozstvim parametru
			token_t another_token;
			global_dynamic_array_position+=1;
			another_token = get_next_token(incoming_list, global_dynamic_array_position);
			arrayInsert(main_list, another_token);
			if(another_token.type != t_EOL) {
				exit(2); // Necekany token
			}
			return;
		} 
		else {
			exit(5); // Spatny pocet parametru u volani funkce!
		}
	}
	
}
/**
	Funkce bude vyvolana v pripade ze typ tokenu bude leva zavorka. Bude hledat pravou zavorku/
*/
void process_left_bracket() {
	
	token_t next_token;
	global_dynamic_array_position+=1;
	next_token = get_next_token(incoming_list, global_dynamic_array_position);
	arrayInsert(main_list, next_token);

	switch(next_token.type) {
		case id:
		case add:
		case sub:
		case mul:
		case t_div:
			process_left_bracket(NO_BRACKET);
		default:
			exit(2); // Wierd left bracket error!
	}

	check_aritmetic_expression(EXPECTING_RIGHT_BRACKET); // jinak pokrachujeme v hledani prave zavorky
}

int process_keyword(token_t t) {
	if(strcmp(t.value->str, "if") == 0) {
		return IF_KEYWORD;
	}
	else if(strcmp(t.value->str, "while") == 0) {
		return WHILE_KEYWORD;
	}
	else if(strcmp(t.value->str, "end") == 0) {
		return END_KEYWORD;
	}
	else if(strcmp(t.value->str, "function") == 0) {
		return FUNCTION_KEYWORD;
	}
	else if(strcmp(t.value->str, "global") == 0) {
		return GLOBAL_KEYWORD;
	}
	else if(strcmp(t.value->str, "local") == 0) {
		return LOCAL_KEYWORD;
	}
	else if(strcmp(t.value->str, "require") == 0) {
		return REQUIRE_KEYWORD;
	}
	else if(strcmp(t.value->str, "return") == 0) {
		return RETURN_KEYWORD;
	}
	else if(strcmp(t.value->str, "then") == 0) {
		return THEN_KEYWORD;
	}
	else if(strcmp(t.value->str, "do") == 0) {
		return DO_KEYWORD;
	}

}

/**
	Funkce zkontroluje prikaz prirazeni
	@param operands_count - pocet ocekavanych operandu
*/

void check_assign(int operands_count) {
	token_t t, u, current_token;
	global_dynamic_array_position--;
	current_token = get_next_token(main_list, global_dynamic_array_position);

	int *prmtr = malloc(sizeof(int));
	if(!prmtr) {
		exit(99);
	}
	*prmtr = 1;
	if(symtable_search(table, current_token.value, prmtr) == false) {
		exit(3);
	}
	global_dynamic_array_position++;
		
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
					if(strcmp(t.value->str, "function") == 0) {
						//built_in_function_call_check(0);
					}
					else if(strcmp(t.value->str, "nil") == 0){
						check_assign(operands_count--);
					}
					else {
						exit(2); //Chyba u assign keyword!
					}
				case integer:
				case ddouble:
				case string:
					check_assign(operands_count--);
					break;
				case add:
				case sub:
				case t_div:
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
						exit(5); //Spatny pocet operatoru u assign!
					}
				default:
					exit(2); //assign_printf!
		}
	}

}
/**
	Funkce pro kontrolu aritmetickych vyrazu. Ma 2 scenaria: pokud ocekava pravou zavorku nebo pokud ne.
*/


void check_aritmetic_expression(int option) {
	
	if(option == NO_BRACKET) {
		token_t next_token;
		global_dynamic_array_position+=1;
		next_token = get_next_token(incoming_list, global_dynamic_array_position);
		arrayInsert(main_list, next_token);
		switch (next_token.type) {
			case id:
			case integer:
			case ddouble:
			case string:
			case keyword:
				if(next_token.type == keyword && strcmp(next_token.value->str, "nil") != 0) {
					exit(2); // Spatny keyword
				}
				token_t another_token;
				global_dynamic_array_position+=1;
				another_token = get_next_token(incoming_list, global_dynamic_array_position);
				arrayInsert(main_list, another_token);
				switch (another_token.type) {
					case t_EOL:
						break;
					case add:
					case sub:
					case mul:
					case t_div:
						check_aritmetic_expression(NO_BRACKET);
					default:
						exit(2); // assign syntax error! 
				}
				return;
		}
	}
	else if(option == EXPECTING_RIGHT_BRACKET) {
		token_t next_token;
		global_dynamic_array_position+=1;
		next_token = get_next_token(incoming_list, global_dynamic_array_position);
		arrayInsert(main_list, next_token);

		token_t another_token;
		switch(next_token.type) {
			case right_bracket:
				break;
			case id:
				global_dynamic_array_position+=1;
				another_token = get_next_token(incoming_list, global_dynamic_array_position);
				arrayInsert(main_list, another_token);
				switch(another_token.type) {
					case t_EOL:
						exit(2); //Ocekava se right bracket syntax error!
					case add:
					case sub:
					case mul:
					case t_div:
						check_aritmetic_expression(EXPECTING_RIGHT_BRACKET);
					default:
						exit(2); //Aritmetic expression u se ocekava right bracket !
				}
				break;
			case add:
			case sub:
			case mul:
			case t_div:
			case left_bracket:
				global_dynamic_array_position+=1;
				another_token = get_next_token(incoming_list, global_dynamic_array_position);
				arrayInsert(main_list, another_token);
				if(another_token.type != id) {
					exit(2); //double operator syntax error!
				}
				check_aritmetic_expression(EXPECTING_RIGHT_BRACKET);

		}
		return;
	}
}

int check_operator(token_t t) {
	if(strcmp(t.value->str, "==") == 0) {
		return DOUBLE_EQUAL;
	}
	else if (strcmp(t.value->str, ">") == 0) {
		return GREATER;
	}
	else if (strcmp(t.value->str, ">=") == 0) {
		return GREATER_OR_EQUAL;
	}
	else if (strcmp(t.value->str, "<") == 0) {
		return LESS;
	}
	else if (strcmp(t.value->str, "<=") == 0) {
		return LESS_OR_EQUAL;
	}
	else if (strcmp(t.value->str, "!") == 0) {
		return NOT;
	}
	else {
		return 0;
	}
}

void check_function_declaration(char* name) {
	token_t next_token;
	global_dynamic_array_position+=1;
	next_token = get_next_token(incoming_list, global_dynamic_array_position);
	symtable_value_t *prmtr = malloc(sizeof(int));
	*prmtr = 0;

	if (symtable_search(table, next_token.value, *prmtr) == true) {
		exit(3); //redefinice funkce!
	}
	if(next_token.type == left_bracket) {
		token_t another_token;
		global_dynamic_array_position+=1;
		another_token = get_next_token(incoming_list, global_dynamic_array_position);
		while (another_token.type != right_bracket) {
			global_dynamic_array_position+=1;
			another_token = get_next_token(incoming_list, global_dynamic_array_position);
			*prmtr++;
		}
		symtable_insert(&table, name, *prmtr);
	} else {
		exit(2);
	}
}

/**
	Hlavni funkce parseru. Nastavuje listy a tabulky
*/
void parser_start(dynArr *list) {

	incoming_list = list;
	arrayInit(main_list);

    token_t t;
	table = symtable_init();

	while ((t.type) != t_EOF) {
		switch (t.type)
		{
            case t_EOL:
			    continue;
            case t_EOF:
			    break;
            case id:
			    check_identifier(t.value->str);
			    break;
		    case keyword:
				if(process_keyword(t) == IF_KEYWORD) {
					check_if_statement(BASIC_IF);
				}
				else if (process_keyword(t) == WHILE_KEYWORD) {
					check_while_statement(BASIC_WHILE);
				}
			    else if (strcmp(t.value->str, "nil")==0) {
					token_t t;
					global_dynamic_array_position+=1;
					 t = get_next_token(incoming_list, global_dynamic_array_position);
			    	arrayInsert(main_list, t);
			    	if (t.type == add || t.type == sub || t.type == mul || t.type == t_div)
				    	check_aritmetic_expression(NO_BRACKET);
			    	else if (t.type == t_EOL)
				    	continue;
			    	else
				    	exit(2);
					}
				else if(strcmp(t.value->str, "require") == 0) {
					global_dynamic_array_position++;
					continue;
				}
				else if(process_keyword(t) == GLOBAL_KEYWORD || process_keyword(t) == LOCAL_KEYWORD) {
					token_t t;
					global_dynamic_array_position+=1;
					t = get_next_token(incoming_list, global_dynamic_array_position);
					if (t.type == id) {
						check_identifier(t.value->str);
					}
					else {
						exit(2);
					}
				}
				else if(process_keyword(t) == FUNCTION_KEYWORD) {
					check_function_def(FUNCTION_START);
				}
				else {
					exit(2);
				}
			    break;
		    case integer:
		    case ddouble:
		    case string:
				global_dynamic_array_position+=1;
			    t = get_next_token(incoming_list, global_dynamic_array_position);
			    arrayInsert(main_list, t);
			    if (t.type == add || t.type == sub || t.type == mul || t.type == t_div)
				    check_aritmetic_expression(NO_BRACKET);
			    else if (t.type == t_EOL)
				    continue;
			    else
					exit(2);
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
			    exit(2); // Neznamy typ tokenu
			break;
		}
    }
}
