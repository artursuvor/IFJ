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

    void *stopITemp;
    void *popITemp = popItem;

    if (popItem->type == TERM)
    {
        bool brackets = false;
        int firstStartIndex;
        if (token->type == right_bracket || popItem->token->type == right_bracket)
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
            switch (popItem->type)
            {
            case id:
                //operandCode = code gen pro id + malloc
                break;
            case string:
                //operandCode = gen pro string + malloc
                break;
            case integer:
                //operandCode = gen pro integer + malloc
                break;
            case ddouble:
                //operandCode = gen pro ddouble + malloc
                break;
            default:
                exit(2);
                break;
            }
            stopITemp = pop(stack);
            if (stopITemp)
            {
                free(stopITemp);
                stopITemp = NULL;
            }
            popItem->type = NON_TERM;
            stack_push(stack, popItem);
            //gen pushs + malloc + operandCode
        }
        else
        {
            if (popItem->token->type == right_bracket)
            {
                if (!popITemp)
                {
                    free(popITemp);
                    popITemp = NULL;
                }
                popItem = pop(stack);
                popITemp = pop(stack);
                if (!popITemp)
                {
                    free(popITemp);
                    popITemp = NULL;
                }
                stopITemp = pop(stack);
                if (!stopITemp)
                {
                    free(stopITemp);
                    stopITemp = NULL;
                }
                stack_push(stack, popItem);
            }
            else
            {
                if (!popITemp)
                {
                    free(popITemp);
                    popITemp = NULL;
                }
                popITemp = pop(stack);
                if (!popITemp)
                {
                    free(popITemp);
                    popITemp = NULL;
                }
                stopITemp = pop(stack);
                if (!stopITemp)
                {
                    free(stopITemp);
                    stopITemp = NULL;
                }
                stack_push(stack, popItem);
            }
            
        }
        return;
    }
    else
    {
        bool same_types = false;

        stack_item *right_operand = popItem;
        popItem = pop(stack);
        stack_item *s_operator = popItem;
        int operator_type = s_operator->token->type;
        popItem = pop(stack);
        stack_item *left_operand = popItem;
    
        int operand_type = right_operand->token->type;

        void *tmp_left = left_operand;
        void *tmp_right = right_operand;
        void *tmp_operator = s_operator;
    
        if (left_operand->token->value == right_operand->token->type)
        {
            same_types = true;
        }
        if (!same_types)
        {
            exit(5); //semantic type error
        }
        
        switch (operator_type)
        {
        //E -> E+E
        case add:
            if (operand_type == integer || operand_type == ddouble)
            {
                //aritmethic + gen - typ operátoru, operand, operand
            }
            else if (operand_type == string){
                //concat gen
            }
            else
            {
                exit(5); //semantic type error
            }
            break;

        //E -> E-E
        case sub:
            if (operand_type == integer || operand_type == ddouble)
            {
                //aritmethic - gen - typ operátoru, operand, operand
            }
            else {
                exit(5); //semantic type error
            }
            break;
        
        //E -> E*E
        case mul:
            if (operand_type == integer || operand_type == ddouble)
            {
                //aritmethic * gen - typ operátoru, operand, operand
            }
            else
            {
                exit(5); //semantic type error
            }
            break;
            
        //E -> E/E
        case t_div:
            if (operand_type == integer || operand_type == ddouble)
            {
                //aritmethic / gen - typ operátoru, operand, operand
            }
            else
            {
                exit(5); //semantic type error
            }
            break;

        //E -> E log E
        case operator:
            char* logical = token->value->str;

            if (logical == "==")
            {
                //logical == gen
            }
            else if (logical == '~=')
            {
                //logical ~= gen
            }
            else if (logical == ">")
            {
                //logical > gen
            }
            else if (logical == "<")
            {
                //logical < gen
            }
            else if (logical == "")
            {
                //todo
            }
            break;
        default:
            exit(2);
        }
        stopITemp = pop(stack);
        if (!popITemp)
        {
            free(popITemp);
            popITemp = NULL;
        }

        stack_item *value = malloc(sizeof(stack_item));
        value->token = right_operand->token;
        value->type = NON_TERM;

        stack_push(stack, value);
        return;
    }
}