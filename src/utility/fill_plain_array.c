#include "config_info_collect.h"
#include "error_report.h"
#include "fill_plain_array.h"
#include "miscellaneous.h"
#include <string.h>
#include <malloc.h>
#include <stdio.h>


int fill_plain_array
(
   const char* dts_owner_name, 
   const char* para_list_name, 
   struct plain_array* plainap
)
{ 
   void* para_list = find_para_list(dts_owner_name, para_list_name);
   if (para_list == NULL)  return UNMATCH;

   int num_para = get_para_list_length(para_list);
   if (num_para == -1)  return UNMATCH;

   void* first_para = get_first_para(para_list);
  
   return do_fill_plain_array(first_para, num_para, &plainap);
}


static int do_fill_plain_array
(
   const void* first_para, 
   int num_para, 
   struct plain_array** plaina2p
)
{
   // 分配存储空间，如果分配失败则返回错误
   if (! alloc_plain_array(num_para, plaina2p)) return FAILURE;
   void* arr = (*plaina2p)->arr;
   char* type = (*plaina2p)->type;

   int i;
   const void* para = first_para;
   for (i=0; i<num_para; i++){
       // 检查type是否一致，如果不是则表示不匹配
       if(! check_para_data_type(para, "plain_array", type)) return FAILURE;

       const char* value_str = get_element_data(para, "text_value");
       if (! check_null(__FILE__, __func__, "arr", arr)) return FAILURE;

       void* data = string_to_numeric_value(value_str, type);
       store_data_in_array(arr, i, data, type);

       para = get_next_sibling(para); 
   }

   return SUCCESS;
}


static int alloc_plain_array(int len, struct plain_array** plaina2p)
{
   void* arr = malloc(sizeof(long int)*len);  
   if (! check_null(__FILE__, __func__, "arr", arr)) return FAILURE;

   (*plaina2p)->arr = arr;
   (*plaina2p)->len = len;
   
   return SUCCESS;
}


static void store_data_in_array
(
    void* array, 
    int idx, 
    void* elem, 
    const char* elem_type
)
{  
    if (is_equal(elem_type, "char")){
        ((char*)array)[idx] = *(char*)elem;
    }else if(is_equal(elem_type, "int")){
        ((int*)array)[idx] = *(int*)elem;
    }else if(is_equal(elem_type, "float")){
        ((float*)array)[idx] = *(float*)elem;
    }else{
       // TODO
    }
}
