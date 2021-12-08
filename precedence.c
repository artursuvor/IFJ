//Precedenční analýza
//Autor: Matěj Novák  - xnovak2q
//       Lukáš Fuis   - xfuisl00
//       Dušan Čičmiš - xcicmi00

#include "precedence.h"

//                      stack      enter
char precedence_table[PREC_SIZE][PREC_SIZE] =
{
//     +- | */  |  (  |  )  | log |  i  |  $
    { '>' , '<' , '<' , '>' , '>' , '<' , '>' }, // +-
    { '>' , '>' , '<' , '>' , '>' , '<' , '>' }, // */
    { '<' , '<' , '<' , '=' , '<' , '<' , 'N' }, // (
    { '>' , '>' , 'N' , '>' , '>' , 'N' , '>' }, // )
    { '<' , '<' , '<' , '>' , 'N' , '<' , '>' }, // log
    { '>' , '>' , 'N' , '>' , '>' , 'N' , '>' }, // i = operand
    { '<' , '<' , '<' , 'N' , '<' , '<' , 'E' }  // $
};

precedence_table_i token_type_to_symbol(token_t *token, TStack *stack)
{
    switch (token->type)
    {
    case id:
    case integer:
    case string:
    case ddouble:
        return OPERAND;
    case add:
    case sub:
        return PLUS_MINUS;
    case mul:
    case t_div:
        MUL_DIV;
    case left_bracket:
        return L_BRACKET;
    case right_bracket:
        return R_BRACKET;
    case operator:
        return LOGIC;
    default:
        return DOLLAR;
    }
}

void precedence_analysis(dynArr *token_array){
    //první inicializace
    token_t *token;
    int *position = 0;
    
    TStack *stack;
    stack = initStack();
    
    stack_item *dollar = malloc(sizeof(stack_item));
    if (!dollar) {
        exit(99);
    }
    dollar->type = EOS;
    token_t *dollarToken = malloc(sizeof(token_t));
    if (!dollarToken) {
        exit(99);
    }
    dollarToken->type = t_EOF;
    dollar->token = dollarToken;
    push(stack, dollarToken);

    precedence_table_i *currentTokenIndex;
    precedence_table_i topTableIndex;
    stack_item *topTableItem;
    bool done = false;
    //konec první inicializace
    
    while (!done)
    {
        *token = get_next_token(token_array, position);
        currentTokenIndex = token_type_to_symbol(token, stack);
        
        topTableItem = top_item(stack);
        topTableIndex = topTableItem->type;
        
        switch (precedence_table[topTableIndex][*currentTokenIndex])
        {
        case '>':
            reduce_operation(token, currentTokenIndex, stack);
            break;
        case '<':
            shift_stop_operation(token, currentTokenIndex, stack);
            break;
        case '=':
            shift_operation(token, currentTokenIndex, stack);
            break;
        case 'N':
            exit(2);
        case 'E':
            done = true;
            break;
        }
    }
    free_stack(&stack);
    return;
}

token_t get_next_token(dynArr *array, int position){
    token_t retVal = array->array[position];
    position++;
    return retVal;
}

void shift_operation(token_t *token, precedence_table_i *currentTokenIndex, TStack *stack){ // =
    stack_item *tmp = malloc(sizeof(stack_item));
    if (!tmp)
    {
        exit(99);
    }
    
    tmp->type = TERM;
    tmp->token = token;
    push(stack, tmp);
}

void shift_stop_operation(token_t *token, precedence_table_i *currentTokenIndex, TStack *stack){  // <
    int termIndex = term_index(stack);

    insert_start(termIndex + 1, stack);
    stack_item *tmp = malloc(sizeof(stack_item));
    if (!tmp)
    {
        exit(99);
    }
    tmp->token = token;
    tmp->type = TERM;
    push(stack, tmp);
}

void reduce_operation(token_t *token, precedence_table_i *currentTokenIndex, TStack *stack){ // <
    stack_item *popItem = pop(stack);
    stack_item *tmp;

    stack_item *stopITemp;
    stack_item *popITemp = popItem;

    if (popItem->type == TERM)
    {
        bool brackets = false;
        int firstStartIndex;
        if (token->type == R_BRACKET || popItem->type == R_BRACKET)
        {
            int topIndex = top_index(stack);
            for (int i = topIndex; i >= 0; i--)
            {
                tmp = stack->data[i];
                if (tmp->type == START)
                {
                    firstStartIndex = i;
                    break;
                }
            }
            tmp = stack->data[firstStartIndex + 1];
            if (tmp->token->type = L_BRACKET)
            {
                brackets = true;
            }
        }
        
        if (!brackets)
        {
            //TODO prostě copy+paste
            char *operand;
            char *push;

            switch (popItem->type)
            {
            case id:
                /* code */
                break;
            case string:
                /* code */
                break;
            case integer:
                /* code */
                break;
            case ddouble:
                /* code */
                break;
            default:
                break;
            }
            stopITemp = pop(stack);
            if (stopITemp)
            {
                free(stopITemp);
                stopITemp = NULL;
                popItem->type = NON_TERM;
                stack_push(stack, popItem);

                //push
                //free push
            }
            return;
        }
    }
    else
    {
        //TODO
    }
}