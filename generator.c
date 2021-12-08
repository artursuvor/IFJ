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

#include "syntax.h"
#include "generator.h"
#include "dynStr.h"  

#define buffer_size 1000

dynStr *buffer;
char tmp_buffer[1000];
   

void start(){    
    addStrToStr(buffer, ".IFJcode21\n");        
}


void defvar(token tok, bool in_function){    
    in_function ? sprintf(tmp_buffer,"DEFVAR LF@%s\n", tok.value) : sprintf(tmp_buffer,"DEFVAR GF@%s\n", tok.value);          
    addStrToStr(buffer, tmp_buffer);    
}


void call(token tok){
    addStrToStr(buffer, "CREATEFRAME\n");   
    sprintf(tmp_buffer, "CALL *%s\n", tok.value);
    addStrToStr(buffer, tmp_buffer);
    //maybe push return value to the stack
}


void clears(){
    addStrToStr(buffer, "POPFRAME\n");
    addStrToStr(buffer, "CLEARS\n");
}


//MOVE, is_const == 1 znamena ze ide o konstantu
//TODO - src a dst zmenit - bud pracovat s ast alebo tokenami
void move(token src, token dst, bool in_function, bool is_const){
    if (is_const == 1)
        in_function ? sprintf(tmp_buffer, "MOVE LF@%s %s\n", src.value, dst.value) : sprintf(tmp_buffer, "MOVE GF@%s %s\n", src.value, dst.value); 
    else    
        in_function ? sprintf(tmp_buffer, "MOVE LF@%s LF@%s\n", src.value, dst.value) : sprintf(tmp_buffer, "MOVE GF@%s GF@%s\n", src.value, dst.value);  
    addStrToStr(buffer, tmp_buffer);     
}


//TODO bud pracovat s ast alebo tokenami
void f_begin(token tok){
    sprintf(tmp_buffer, "LABEL $%s\n", tok.value);
    addStrToStr(buffer, tmp_buffer);
    addStrToStr(buffer, "PUSHFRAME\n");
}


void f_end(){
    addStrToStr(buffer, "POPFRAME\n");
    addStrToStr(buffer, "RETURN\n");
}


void ifjcode_main(){
    addStrToStr(buffer, "LABEL _main\n");
    addStrToStr(buffer, "CREATEFRAME\n");
}


void concat(token tok1, token tok2, bool in_function){
    in_function ? sprintf(tmp_buffer, "CONCAT LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value) : sprintf(tmp_buffer, "CONCAT GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
    addStrToStr(buffer, tmp_buffer);
}


void arithmetic_operation(token t_type, token tok1, token tok2, bool in_function){
    switch (t_type.type){
    // add
    case 11: 
        in_function ? sprintf(tmp_buffer, "ADD LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value) : sprintf(tmp_buffer, "ADD GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
        addStrToStr(buffer, tmp_buffer);
        break;   

    // sub
    case 12:
        in_function ? sprintf(tmp_buffer, "SUB LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value) : sprintf(tmp_buffer, "SUB GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
        addStrToStr(buffer, tmp_buffer);
        break;  
    
    // mul
    case 13:
        in_function ? sprintf(tmp_buffer, "MUL LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value) : sprintf(tmp_buffer, "MUL GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
        addStrToStr(buffer, tmp_buffer);
        break;

    //div
    case 14: 
        in_function ? sprintf(tmp_buffer, "DIV LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value) : sprintf(tmp_buffer, "DIV GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
        addStrToStr(buffer, tmp_buffer);
        break;         
      
    default:
        break;
    }
}


//Generovani relacnich operatoru
void relational_operation(token t_type, token tok1, token tok2, bool in_function){    
    char* operator;
    operator = t_type.value->str;
    
    // ==
    if (strcmp(operator, "==")){
        in_function ? sprintf(tmp_buffer, "EQ LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value) : sprintf(tmp_buffer, "EQ GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
        addStrToStr(buffer, tmp_buffer);
    }

    // != 
    else if (strcmp(operator, "!=")){
        if(in_function){          
            sprintf(tmp_buffer, "EQ  LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value);
            addStrToStr(buffer, tmp_buffer);
            sprintf(tmp_buffer, "NOT  LF@%s LF@%s\n", tok1.value, tok1.value);
            addStrToStr(buffer, tmp_buffer);
        }                     
        
        else{   
            sprintf(tmp_buffer, "EQ  GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
            addStrToStr(buffer, tmp_buffer);
            sprintf(tmp_buffer, "NOT  GF@%s GF@%s\n", tok1.value, tok1.value);   
            addStrToStr(buffer, tmp_buffer);
        }
    }              

    // <
    else if (strcmp(operator, "<")){
        in_function ? sprintf(tmp_buffer, "LT LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value) : sprintf(tmp_buffer, "LT GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
        addStrToStr(buffer, tmp_buffer);
    }      
    // >
    else if (strcmp(operator, ">")){
        in_function ? sprintf(tmp_buffer, "GT LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value) : sprintf(tmp_buffer, "GT GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
        addStrToStr(buffer, tmp_buffer);
    }

    // <=
    else if (strcmp(operator, "<=")){ 
        if(in_function){          
                sprintf(tmp_buffer, "GT  LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value);
                addStrToStr(buffer, tmp_buffer);
                sprintf(tmp_buffer, "NOT  LF@%s LF@%s\n", tok1.value, tok1.value);     
                addStrToStr(buffer, tmp_buffer);          
        }

        else{             
                sprintf(tmp_buffer, "GT  GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
                addStrToStr(buffer, tmp_buffer);
                sprintf(tmp_buffer, "NOT  GF@%s GF@%s\n", tok1.value, tok1.value); 
                addStrToStr(buffer, tmp_buffer);
        }    
    }     
        
    // >=
    else if (strcmp(operator, ">=")){ 
        if(in_function){          
                sprintf(tmp_buffer, "LT  LF@%s LF@%s LF@%s\n", tok1.value, tok1.value, tok2.value);
                addStrToStr(buffer, tmp_buffer);
                sprintf(tmp_buffer, "NOT  LF@%s LF@%s\n", tok1.value, tok1.value);               
                addStrToStr(buffer, tmp_buffer);
        }

        else{             
                sprintf(tmp_buffer, "LT  GF@%s GF@%s GF@%s\n", tok1.value, tok1.value, tok2.value);
                addStrToStr(buffer, tmp_buffer);
                sprintf(tmp_buffer, "NOT  GF@%s GF@%s\n", tok1.value, tok1.value); 
                addStrToStr(buffer, tmp_buffer);
        }                     
    }
}

// if start 
void if_begin(token label, token result, bool in_function){
    in_function ? sprintf(tmp_buffer, "JUMPIFEQ %s LF@%s bool@true\n", label.value, result.value) : sprintf(buffer, "JUMPIFEQ %s GF@%s bool@true\n", label.value, result.value); 
    addStrToStr(buffer, tmp_buffer);
}


// else
void else_label(token label){
    sprintf(tmp_buffer, "LABEL %s\n", label.value);  
    addStrToStr(buffer, tmp_buffer);
}


// if end
void if_end(token label){
    sprintf(tmp_buffer, "JUMP %s\n", label.value);
    addStrToStr(buffer, tmp_buffer);
}

//generovani print
void ifjcode_write(token t, bool in_function, bool is_const){
    if (is_const){
        if(in_function){
            sprintf(tmp_buffer,"WRITE LF@%s\n", t.value);
            addStrToStr(buffer, tmp_buffer);
        }

        else{
            sprintf(tmp_buffer,"WRITE LF@%s\n", t.value);
            addStrToStr(buffer, tmp_buffer);
        }
    }

    else{
        if(in_function){
            sprintf(tmp_buffer,"WRITE %s\n", t.value);
            addStrToStr(buffer, tmp_buffer);
        }

        else{
            sprintf(tmp_buffer,"WRITE %s\n", t.value);
            addStrToStr(buffer, tmp_buffer);
        }
    }      
}
