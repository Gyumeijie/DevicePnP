#include "type_converter.h"
#include "symbol.h"
#include "miscellaneous.h"
#include <string.h>
#include <stdio.h>


void numtype_to_strtype(int num_type, char* repr)
{
    int type = num_type;
    int pointer_level = 0;
    while (type >= PTR){
       pointer_level++;
       type -= PTR;
    }

    char* base_type = type == CHAR ?  "char" :
                      type == INT  ?  "int"  :
                      type == FLOAT ? "float" : "double";

    strcpy(repr, base_type);
    int start_index = strlen(base_type);
    while (pointer_level){
        repr[start_index++] = '*';
        pointer_level--;
    }
    
    repr[start_index] = '\0';
}


int strtype_to_numtype(const char* type, Boolean is_pointer)
{
    int base_type;
    if (is_equal(type, "char")){
       base_type =  CHAR; 
    }else if (is_equal(type, "int")){
       base_type =  INT;
    }else if (is_equal(type, "float")){
       base_type = FLOAT;
    }else if (is_equal(type, "double")){
       base_type =  DOUBLE;
    }else{
       printf("strtype_to_numtype unknown type %s\n", type);
       base_type = -1;
    }

    return base_type + (is_pointer ? PTR : 0);
}

