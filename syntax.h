#include "scanner.h"
#include "symtable.h"
#include "list.h"

token get_next_token();

void check_id (token tok);

void check_number();

void check_assign();

void check_arithmetic(unsigned int type);

void while_came();

void if_came();

void inside_commands(unsigned int type);