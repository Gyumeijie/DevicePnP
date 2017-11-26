#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "miscellaneous.h"

void* string_to_numeric_value(const char* value, const char* type)
{
   if (type == NULL || value == NULL) return NULL;

   // 只是作为4个字节长的存储空间
   static long int data; 

   if (is_inttype(type)){
       int base = parse_inttype_for_base(type);
       data = strtoul(value, NULL, base);
   }else if (is_equal(type, "char")){
       data = strtoul(value, NULL, 16);
   }else if (is_equal(type, "float")){
       *(float*)&data = strtod(value, NULL);
   }else{
        return NULL;
   }

   return (void*)&data;
}

// 顺序不限 分隔符不限 有默认的值(b表示base，l表示length)
// 但是推荐写法int_b16_l16或者int_l16_b16
int parse_inttype(const char* type, const char attr)
{
  if (type == NULL || !(attr == 'b' || attr == 'l')) return 0;

  char* attr_start = strchr(type, attr); 
  if (attr_start == NULL){
    // int类型的默认长度为32，默认进制是10
    return  attr == 'l' ? 32 : 10;
  } 
  
  // 只处理两位数的进制
  char* iterator = attr_start + 1;
  char attr_val[3];
  int i = 0;
  while ((*iterator) != '\0' && isdigit(*iterator) && i < 2){
     attr_val[i] = (*iterator);
     iterator += 1;
     i += 1;
  }
  
   return strtoul(attr_val, NULL, 10);
}


int parse_inttype_for_base(const char* type)
{
   return parse_inttype(type, 'b');
}


int parse_inttype_for_length(const char* type)
{
   return parse_inttype(type, 'l');
}


Boolean is_equal(const char* str1, const char* str2)
{
    return (!strcmp(str1, str2));
}


Boolean is_inttype(const char* type)
{
   return (strstr(type, "int") == NULL) ? False : True; 
}


