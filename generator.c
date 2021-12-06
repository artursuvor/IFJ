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

//v scanner.c prehodit enum do scanner.h aby sme neincludovali .c subor
#include "scanner.c"
#include "syntax.h"
#include "generator.h"
   

void start(){
    printf(".IFJcode21\n");    
}


void clears(){
    printf(stdout, "POPFRAME\n");
    printf(stdout, "CLEARS\n");
}


void defvar(token tok, bool in_function){
    in_function ? printf("DEFVAR LF@%s\n", tok.value) : printf("DEFVAR GF@%s\n", tok.value);         
}


void call(token tok){
    printf("CREATEFRAME\n");   
    printf("CALL *%s\n", tok.value);
    //maybe push return value to the stack
}


//MOVE, is_const == 1 znamena ze ide o konstantu
//TODO - src a dst zmenit - bud pracovat s ast alebo tokenami
void move(token src, token dst, bool in_function, bool is_const){
    if (is_const == 1)
        in_function ? printf("MOVE LF@%s %s\n", src.value, dst.value) : printf("MOVE GF@%s %s\n", src.value, dst.value); 
    else    
        in_function ? printf("MOVE LF@%s LF@%s\n", src.value, dst.value) : printf("MOVE GF@%s GF@%s\n", src.value, dst.value);    
}


//TODO bud pracovat s ast alebo tokenami
void f_begin(token tok){
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


void concat(token tok1, token tok2, bool in_function){
    in_function ? printf("CONCAT LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value) : printf("CONCAT GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
}


void arithmetic_operation(token t_type, token tok1, token tok2, bool in_function){
    switch (t_type.type){
    // add
    case 11: 
        in_function ? printf("ADD LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value) : printf("ADD GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
        break;   

    case 12:
        in_function ? printf("SUB LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value) : printf("SUB GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
        break;  

    case 13:
        in_function ? printf("MUL LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value) : printf("MUL GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
        break;

    case 14: 
        in_function ? printf("DIV LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value) : printf("DIV GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
        break;         
      
    default:
        break;
    }
}


//Generovani relacnich operatoru
void relational_operation(token t_type, token tok1, token tok2, bool in_function){
    switch(t_type.type){
        // ==
        case "TODO": 
            in_function ? printf("EQ LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value) : printf("EQ GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
            break;

        // !=    
        case "TODO":       
            if(in_function){          
                    printf("EQ  LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value);
                    printf("NOT  LF@%s LF@%s\n", tok1.value, tok1.value);
            }
            
            else{   
                    printf("EQ  GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
                    printf("NOT  GF@%s GF@%s\n", tok1.value, tok1.value);   
            }
            break;   

        // <
        case "TODO": 
            in_function ? printf("LT LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value) : printf("LT GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
            break;            
          
        // >
        case "TODO": 
            in_function ? printf("GT LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value) : printf("GT GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
            break;
            
        // <=
        case "TODO": 
            if(in_function){          
                    printf(stdout,"GT  LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value);
                    printf(stdout,"NOT  LF@%s LF@%s\n", tok1.value, tok1.value);               
            }

            else{             
                    printf(stdout,"GT  GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
                    printf(stdout,"NOT  GF@%s GF@%s\n", tok1.value, tok1.value); 
            }          
            break;

        // >=
        case "TODO": 
            if(in_function){          
                    printf(stdout,"LT  LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value);
                    printf(stdout,"NOT  LF@%s LF@%s\n", tok1.value, tok1.value);               
            }

            else{             
                    printf(stdout,"LT  GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
                    printf(stdout,"NOT  GF@%s GF@%s\n", tok1.value, tok1.value); 
            }          
            break;     

        default:
            break;
    }
}


// if start 
void if_begin(token label, token result, bool in_function){
    in_function ? printf("JUMPIFNEQ %s LF@%s bool@true\n", label.value, result.value) : printf("JUMPIFNEQ %s GF@%s bool@true\n", label.value, result.value); 
}


// else
void else_label(token label){
    printf("LABEL %s\n", label.value);  
}


// if end
void if_end(token label){
    printf("JUMP %s\n", label.value);
}


// print
// is_const == 1 znamena ze ide o konstantu
void ifjcode_write(token tok, bool in_function, bool is_const){
    if (is_const)
        in_function ? printf("WRITE %s\n", tok.value) : printf("WRITE %s\n", tok.value);   

    else
        in_function ? printf("WRITE LF@%s\n", tok.value) : printf("WRITE GF@%s\n", tok.value);
    
    printf("WRITE string@\\010\n"); 
}


//vestavena funkce inputi
void ifjcode_inputi(){

}

//vestavena funkce inputok
void ifjcode_inputok(){

}

//vestavena funkce inputs
void ifjcode_inputs(){

}

//vestavena funkce len
void ifj_len(){

}

//vestavena funkce substr
void ifjcode_substr(){
  
}

//vestavena funkce ord
void ifjcode_ord(){
    
}

// vestavena funkce chr
void ifjcode_chr(){

}