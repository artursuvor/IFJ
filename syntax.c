#include <stdio.h>
#include <stdlib.h>

#include "scanner.h"
#include "symtable.h"
#include "list.h"
#include "scanner.c"
#include "syntax.h"

#define WITH_BRACKET 50
#define WITHOUT_BRACKET 60 
#define END_END 70
#define END_DO 71
#define END_THEN 72
#define END_ELSE 73


// NEFUNKCNI!!! Potrebuji spravne zarazene definice stavu v teto branchi pls

symtable_node_t *table;
list *main_list;




void parser_start() {

	//  Inicializace

	token t;
	table = symtable_init();
	main_list = init_list();

	while ((t.type) != t_EOF) {
		switch (t.type)
		{
			// case keyword:

			case id:
				check_id (t);
				break;
			case string:
			case integer:
			case ddouble:
				token next_token;
				next_token = get_next_token();
				list_insert_last(main_list, t);
				if (t.type == add || t.type == sub || t.type == mul || t.type == div)
					check_arithmetic(WITHOUT_BRACKET);
				else if (t.type == new_line)
					continue;
				else
					printf(stderr,"unexpected token after item");
				break;
			// case exponent: 
			// case operator:
			// case left_bracket:
			// case right_bracket:
			default:
				printf(stderr, "Neznamy token");
				break;
		}
	}

}

/*
    Funkce bude vyvolana pokud typ tokentu bude identifikator
*/


void check_id (token tok) {
    token next_token;
	next_token = get_next_token(); // funkce scanneru ktera vrati vzdy jeden token

	list_insert_last(main_list, next_token);
	char *name;

	switch (next_token.type)
	{
	case integer:
        check_number();
		break;
	case equal: // Prirazeni
		name = malloc(sizeof(char)*(strlen(tok.value) + 1));
		strcpy(name, tok.value); // ulozime hodnotu nazvu

		check_assign(); // funkce pro kontrolu prirazeni
		break;
	case add:
	case sub:
	case mul:
	case div:
		check_arithmetic(WITHOUT_BRACKET); // Tady bude kontrola vyrazu 
		break;
	case new_line:
		break;
	default:
		return 1; // jaka tady ma byt chyba?
	}
}

/**
 * Dale nasleduji funkce pro kontrolu jednotlivych konstrukci. Kazda funkce bud nevrati nic nebo vyhodi chybu.
*/




void check_while()
{
	token t;
	check_bool(WITHOUT_BRACKET, END_DO);//checkuje i EOL

	inside_commands(END_END);
	//EOL
	t = get_next_token();
	list_insert_last(main_list, t);
	if (t.type == t_EOF)
		printf(stderr, "unexpected EOF");
	else if (t.type != new_line)
		printf(stderr, "expected EOL");
}

void check_if()
{
	token t;
	check_bool(WITHOUT_BRACKET, END_THEN);//checkuje i EOL

	inside_commands(END_ELSE);
	//EOL
	t = get_next_token();
	list_insert_last(main_list, t);
	if (t.type == t_EOF)
		printf(stderr, "unexpected EOF");
	else if (t.type != new_line)
		printf(stderr, "expected EOL after else");
	inside_commands(END_END);
	//EOL
	t = get_next_token();
	list_insert_last(main_list, t);
	if (t.type == t_EOF)
		printf(stderr, "unexpected eof");
	else if (t.type != new_line)
		printf(stderr, "expected EOL after end");
}

/**
 * Funkce na kontrolu arithmetickych vyrazu
*/

void check_arithmetic(unsigned int type)
{
	token t, u;
	switch (type)
	{
	case WITHOUT_BRACKET: // Pokud neocekavame pravou zavorku
		t = get_next_token();
		list_insert_last(main_list, t);
		if (t.type == left_bracket)
			epxr_left_bracket_checkEOL();
		else if (t.type == id || t.type == integer || t.type == string || t.type == ddouble)
		{
			u = get_next_token();
			list_insert_last(main_list, u);
			if (u.type == sub || u.type == add || u.type == mul || u.type == div)
				check_arithmetic(WITHOUT_BRACKET);
			else if (u.type == new_line)
				return;
			else
				printf(stderr, "wrong expression, expected EOL or another operator (end of expression)");

		}
		else
			printf(stderr, "wrong expression, expected '(' or id/item");
		break;
		/**
		 * Ocekavame pravou zavorku
		*/
	case WITH_BRACKET:
		t = get_next_token();
		list_insert_last(main_list, t);
		if (t.type == left_bracket)
		{
			check_aritmetic(WITH_BRACKET);
			u = get_next_token();
			list_insert_last(main_list, u);
			if (u.type == right_bracket)
				return;
			else if (u.type == add || u.type == sub || u.type == mul || u.type == div)
				check_arithmetic(WITH_BRACKET);
			else
				printf(stderr, "wrong expression, expected ')'");
		}
		else if (t.type == id || t.type == integer || t.type == string || t.type == ddouble)
		{
			u = get_next_token();
			list_insert_last(main_list, u);
			if (u.type == add || u.type == sub || u.type == mul || u.type == div)
				check_arithmetic(WITH_BRACKET);
			else if (u.type == right_bracket)
				return;
			else
				printf(stderr, "wrong expression, expected ')' or operator");
		}
		else
			printf(stderr, "wrong expression, expected '(' or id/item");
		break;
	}
}

void epxr_left_bracket_checkEOL()
{
	token u;
	check_arithmetic(WITH_BRACKET);
	u = get_next_token();
	list_insert_last(main_list, u);
	if (u.type == add || u.type == sub || u.type == mul || u.type == div)
		check_arithmetic(WITHOUT_BRACKET);
	else if (u.type == new_line)
		return;
	else
		printf(stderr, "wrong expression, expected operator or EOL");

}

void check_bool(unsigned int type, unsigned int if_or_while)
{	token t, u;
	switch (type)
	{
	case WITHOUT_BRACKET:
		t = get_next_token();
		list_insert_last(main_list, t);
		if (t.type == left_bracket)
			expr_bool_left_bracket_check_ending(if_or_while);
		else if (t.type == id || t.type == integer || t.type == string || t.type == ddouble)
		{
			u = get_next_token();
			list_insert_last(main_list, u);
			if (u.type == sub || u.type == add || u.type == mul || u.type == div || u.type == tkn_equal_2 || u.type == tkn_not_equal || u.type == tkn_less || u.type == tkn_less_or_equal || u.type == tkn_more || u.type == tkn_more_or_equal)
				expr_bool(WITHOUT_BRACKET, if_or_while);
			else
			{
				switch (if_or_while)
				{
				case END_DO://while
					if (u.type != tkn_key_do)
						printf(stderr, "wrong bool expression, expected keyword 'do' or another operator");
					break;
				case END_THEN:
					if (u.type != tkn_key_then)
						printf(stderr, "wrong bool expression, expected keyword 'then'");
					break;
				}
				u = get_next_token();
				list_insert_last(main_list, u);
				if (u.type == new_line)
					return;
				else
					printf(stderr, "wrong bool expression, expected EOL after keyword then/do");
			}
		}
		else
			printf(stderr, "wrong bool expression, expected '(' or id/item");
		break;
	case WITH_BRACKET:
		t = get_next_token();
		list_insert_last(main_list, t);
		if (t.type == left_bracket)
		{
			expr_bool(WITH_BRACKET, if_or_while);
			u = get_next_token();
			list_insert_last(main_list, u);
			if (u.type == right_bracket)
				return;
			else if (u.type == sub || u.type == add || u.type == mul || u.type == div || u.type == tkn_equal_2 || u.type == tkn_not_equal || u.type == tkn_less || u.type == tkn_less_or_equal || u.type == tkn_more || u.type == tkn_more_or_equal)
				expr_bool(WITH_BRACKET, if_or_while);
			else
				printf(stderr, "wrong expression, expected ')'");
		}
		else if (t.type == id || t.type == integer || t.type == string || t.type == ddouble)
		{
			u = get_next_token();
			list_insert_last(main_list, u);
			if (u.type == sub || u.type == add || u.type == mul || u.type == div || u.type == tkn_equal_2 || u.type == tkn_not_equal || u.type == tkn_less || u.type == tkn_less_or_equal || u.type == tkn_more || u.type == tkn_more_or_equal)
				expr_bool(WITH_BRACKET, if_or_while);
			else if (u.type == right_bracket)
				return;
			else
				printf(stderr, "wrong bool expression, expected ')' or operator");
		}
		else
			printf(stderr, "wrong bool expression, expected '(' or id/item");
		break;
	}
}

/**
 * Kontrola vyrazu u if a while
*/




void inside_commands(unsigned int type)
{
	token t;
	switch (type)
	{
	case END_END:
		do
		{
			t = get_next_token();
			list_insert_last(main_list, t);
			switch (t.type)
			{
			case id:
				id_came(t);
				break;
			case new_line:
				continue;
			case token_if:
				check_if();
				break;
			case token_while:
				check_while();
				break;
			case ddouble:
			case integer:
			case string:
				t = get_next_token();
				list_insert_last(main_list, t);
				if (t.type == t_EOF)
					printf(stderr, "unexpected EOF");
				else if (t.type == new_line)
					continue;
				else if (t.type == sub || t.type == add || t.type == mul || t.type == div)
					check_aritmetic(WITHOUT_BRACKET);
				else
					printf(stderr, "expected EOL or expression after item (inside commands)");
				break;
			case tkn_key_end:
				break;
			default:
				printf(stderr, "expected keyword 'end'");
				break;
			}

		} while (t.type != tkn_key_end);
		break;
	case END_ELSE:
		do
		{
			t = get_next_token();
			list_insert_last(main_list, t);
			switch (t.type)
			{
			case id:
				id_came(t);
				break;
			case new_line:
				continue;
			case token_if:
				check_if();
				break;
			case token_while:
				check_while();
				break;
			case ddouble:
			case integer:
			case string:
				t = get_next_token();
				list_insert_last(main_list, t);
				if (t.type == t_EOF)
					printf(stderr, "unexpected EOF");
				else if (t.type == new_line)
					continue;
				else if (t.type == sub || t.type == add || t.type == mul || t.type == div)
					check_aritmetic(WITHOUT_BRACKET);
				else
					printf(stderr, "expected EOL or expression after item (inside if)");
				break;
			case tkn_key_else:
				break;
			default:
				printf(stderr, "expected keyword 'else'");
				break;
			}

		} while (t.type != tkn_key_else);
		break;
	}
}