#include <stdio.h>
#include <stdlib.h>

#include "scanner.h"
#include "symtable.h"
#include "list.h"

// NEFUNKCNI!!! Potrebuji spravne zarazene definice stavu v teto branchi pls

symtable_node_t *table;
list *main_list;


/*
    Funkce bude vyvolana pokud typ tokentu bude identifikator
*/

void check_id (token tok) {
    token t;
	t = get_next_token(); // funkce scanneru ktera vrati vzdy jeden token

	list_insert_last(main_list, t);
	char *name;

	switch (t.type)
	{
	case tkn_integer:
        checkNumber();
		break;
	case tkn_equal: // Prirazeni
		name = malloc(sizeof(char)*(strlen(tok.value) + 1));
		strcpy(name, tok.value); // ulozime hodnotu nazvu

		checkAssign(); // funkce pro kontrolu prirazeni
		break;
	case tkn_plus:
	case tkn_minus:
	case tkn_mul:
	case tkn_div:
		checkArithmetic(); // Tady bude kontrola vyrazu 
		break;
	case tkn_new_line:
		break;
	default:
		return 1; // jaka tady ma byt chyba?
	}
}


