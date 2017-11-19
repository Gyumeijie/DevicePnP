#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "miscellaneous.h"


//TODO 换一个准确的名字
//convert_string_data_to(dest_type, value)
void* convert_type(const char* value, const char* type)
{
   if (type == NULL || value == NULL) return NULL;

   static long int data; //只是作为4个字节长的存储空间

   if (is_inttype(type)){
       int base = parse_inttype_for_base(type);
       data = strtoul(value, NULL, base);
   } else if (is_equal(type, "char")){
       data = strtoul(value, NULL, 16);
   }else if(is_equal(type, "float")){
        *(float*)&data = strtod(value, NULL);
   }else{
        return NULL;
   }

   return (void*)&data;
}

//顺序不限 分隔符不限 有默认的值
//但是推荐写法int_b16_l16或者int_l16_b16
int parse_inttype(const char* type, const char attr)
{
  if (type == NULL || !(attr == 'b' || attr == 'l')) return 0;

  char* attr_start = strchr(type, attr); 
  if (attr_start == NULL){
      //int类型的默认长度为32，默认进制是10
    return  attr == 'l' ? 32 : 10;
  } 
  
  //只处理两位数的进制
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


void substr(char* dest, const char* src, unsigned int start, unsigned int cnt)
{
   //防止转化失败时，dest输出乱码
   dest[0] = '\0';

   if (src == NULL || dest == NULL) return;
   if (strlen(src) <= start) return; 
   
   strncpy(dest, src + start, cnt);
   dest[cnt] = '\0';
}

#if 0
void store_data
(
    const void* dest, 
    const void* src, 
    const char* dest_type,
    const char* src_type
)
{
    if (is_inttype(dest_type)){
       int len = parse_inttype_for_length(dest_type);
       (len == 32) ? store_int32type_data_from(src_type, dest, src)
                   : store_int16type_data_from(src_type, dest, src);
    }else if (is_equal(dest_type, "float")){
       store_floattype_data_from(src_type, dest, src);
    }else if (is_equal(dest_type, "char")){
       store_chartype_data_from(src_type, dest, src);
    }else{
       //不执行实际操作，这里忽略
    }
}


static void store_floattype_data_from
(
    const char* src_type, 
    const void* dest,
    const void* src
)
{   
    if (is_equal(src_type, "float")){
       TO_FLOAT(dest) = TO_FLOAT(src);
    }else if (is_inttype(src_type)){
       int len = parse_inttype_for_length(src_type);
       TO_FLOAT(dest) = (len == 32) ? TO_INT(src) : TO_SHORT_INT(src);
    }else{
       //由char转float不常见，这里先不写以后有需求的话在写
    }
}


static void store_chartype_data_from
(
    const char* src_type, 
    const void* dest,
    const void* src
)
{
    if (is_equal(src_type, "char")){
       TO_CHAR(dest) = TO_CHAR(src);
    }else if (is_inttype(src_type)){
       int len = parse_inttype_for_length(src_type);
       TO_CHAR(dest) = (len == 32) ? TO_INT(src) : TO_SHORT_INT(src);
    }else{
       //由char转float不常见，这里先不写以后有需求的话在写
    }
}


static void store_int16type_data_from
(
    const char* src_type, 
    const void* dest,
    const void* src
)
{
    if (is_inttype(src_type)){
       int len = parse_inttype_for_length(src_type);
       TO_SHORT_INT(dest) = (len == 32) ? TO_INT(src) : TO_SHORT_INT(src);
    }else if (is_equal(src_type, "float")){
       TO_SHORT_INT(dest) = TO_FLOAT(src);
    }else{
       TO_SHORT_INT(dest) = TO_CHAR(src);
    }
}


static void store_int32type_data_from
(
    const char* src_type, 
    const void* dest,
    const void* src
)
{
    if (is_inttype(src_type)){
       int len = parse_inttype_for_length(src_type);
       TO_INT(dest) = (len == 32) ? TO_INT(src) : TO_SHORT_INT(src);
    }else if (is_equal(src_type, "float")){
       TO_INT(dest) = TO_FLOAT(src);
    }else{
       TO_INT(dest) = TO_CHAR(src);
    }

}
#endif
