#include <stdio.h>
#include <stdlib.h>

#include "scanner.h"
#include "symtable.h"
#include "list.h"
#include "scanner.c"
#include "syntax.h"


int semantic_start(list function_list, symtable) {
    token t;
    while ((t.type) != t_EOF) {
		switch (t.type)
		{
			
			case id:
				process_identifier(t);
				break;
			default:
				printf(stderr, "Neznamy token");
				break;
		}
	}
 return 0;
}

void process_identifier() {
    token next_token;
    next_token = get_next_token();
    switch (next_token.type)
	{
        case id:
            int arguments_count = 0; //TODO Get arguments count!
            check_function_call(arguments_count);
            break;
        case equal:
             check_assign();
             break;
        default:
        printf(stderr, "Nevhodny typ tokenu!");
            break;
    }
    
}

void check_function_call(int arguments_count) {
    token next_token;
    next_token = get_next_token();
    switch (next_token.type)
	{
        case id:
            if (symtable_search(*symtable, next_token.value, 1) == false)
				printf(stderr, "Neznamy token!");
			break;
            break;
        case reads:
		case readi:
		case readn:
		case write:
		case tointeger:
		case substr:
		case ord:
		case chr:
            int arguments_count = 0; //TODO get arguments count and pass to checker!
            token next_token;
            next_token = get_next_token();
            for (int i = 0; i < sizeof(types_array); i++) {
                // Kontrola typu argumentu
            }
        default:
            printf(stderr, "Nevhodny typ tokenu!");
            break;

    }
}