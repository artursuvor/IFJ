/*
*Téma:              Generovanie cieloveho kodu
*varianta:          Tym 069, varianta 1
*clenovia:          xsuvor00 - veduci
*                   xnovak2q
*                   xfuisl00                   
*                   xcicmi00
*skola:             Vysoke uceni technicke v Brne - FIT
*datum vytvorenia:  1.12.2021
*/

#include "header_test.h"
   

void start(){
    printf(".IFJcode21\n");    
}


void defvar(token_t  tok, bool in_function){
    in_function ? printf("DEFVAR LF@%s\n", tok.value) : printf("DEFVAR GF@%s\n", tok.value);         
}


void call(token_t  tok){
    printf("CREATEFRAME\n");   
    printf("CALL *%s\n", tok.value);
    //maybe push return value to the stack
}


void clears(){
    printf(stdout, "POPFRAME\n");
    printf(stdout, "CLEARS\n");
}


//MOVE, is_const == 1 znamena ze ide o konstantu
//TODO - src a dst zmenit - bud pracovat s ast alebo tokenami
void move(token_t src, token_t dst, bool in_function, bool is_const){
    if (is_const == 1)
        in_function ? printf("MOVE LF@%s %s\n", src.value, dst.value) : printf("MOVE GF@%s %s\n", src.value, dst.value); 
    else    
        in_function ? printf("MOVE LF@%s LF@%s\n", src.value, dst.value) : printf("MOVE GF@%s GF@%s\n", src.value, dst.value);    
}


//TODO bud pracovat s ast alebo tokenami
void f_begin(token_t tok){
    printf("LABEL $%s\n", tok.value);
    printf("PUSHFRAME\n");
}


void f_end(){
    printf("POPFRAME\n");
    printf("RETURN\n");
}


void ifjcode_main(){
    printf("LABEL _main\n");
    printf("CREATEFRAME\n");
}


void concat(token_t tok1, token_t tok2, bool in_function){
    in_function ? printf("CONCAT LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value) : printf("CONCAT GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
}


void arithmetic_operation(token_t t_type, token_t tok1, token_t tok2, bool in_function){
    switch (t_type.type){
    // add
    case 11: 
        in_function ? printf("ADD LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value) : printf("ADD GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
        break;   

    // sub
    case 12:
        in_function ? printf("SUB LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value) : printf("SUB GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
        break;  
    
    // mul
    case 13:
        in_function ? printf("MUL LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value) : printf("MUL GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
        break;

    //div
    case 14: 
        in_function ? printf("DIV LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value) : printf("DIV GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
        break;         
      
    default:
        break;
    }
}


//Generovani relacnich operatoru
void relational_operation(token_t t_type, token_t tok1, token_t tok2, bool in_function){    
    char* operator;
    operator = t_type.value->str;
    
    // ==
    if (strcmp(operator, "=="))
        in_function ? printf("EQ LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value) : printf("EQ GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);

    // != 
    else if (strcmp(operator, "!=")){
        if(in_function){          
            printf("EQ  LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value);
            printf("NOT  LF@%s LF@%s\n", tok1.value, tok1.value);
        }                     
        
        else{   
            printf("EQ  GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
            printf("NOT  GF@%s GF@%s\n", tok1.value, tok1.value);   
        }
    }              

    // <
    else if (strcmp(operator, "<"))
        in_function ? printf("LT LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value) : printf("LT GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
            
    // >
    else if (strcmp(operator, ">"))
        in_function ? printf("GT LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value) : printf("GT GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
                    
    // <=
    else if (strcmp(operator, "<=")){ 
        if(in_function){          
                printf(stdout,"GT  LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value);
                printf(stdout,"NOT  LF@%s LF@%s\n", tok1.value, tok1.value);               
        }

        else{             
                printf(stdout,"GT  GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
                printf(stdout,"NOT  GF@%s GF@%s\n", tok1.value, tok1.value); 
        }    
    }     
        
    // >=
    else if (strcmp(operator, ">=")){ 
        if(in_function){          
                printf(stdout,"LT  LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value);
                printf(stdout,"NOT  LF@%s LF@%s\n", tok1.value, tok1.value);               
        }

        else{             
                printf(stdout,"LT  GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
                printf(stdout,"NOT  GF@%s GF@%s\n", tok1.value, tok1.value); 
        }                     
    }
}


// if start 
void if_begin(token_t label, token_t result, bool in_function){
    in_function ? printf("JUMPIFEQ %s LF@%s bool@true\n", label.value, result.value) : printf("JUMPIFEQ %s GF@%s bool@true\n", label.value, result.value); 
}


// else
void else_label(token_t label){
    printf("LABEL %s\n", label.value);  
}


// if end
void if_end(token_t label){
    printf("JUMP %s\n", label.value);
}