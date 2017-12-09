#include "config_info_collect.h"
#include "error_report.h"
#include "fill_plain_array.h"
#include "miscellaneous.h"
#include <string.h>
#include <malloc.h>
#include <stdio.h>


int fill_plain_array
(
   const char* template_data_owner_name, 
   const char* template_data_name, 
   struct plain_array* plainap
)
{ 
   // 先检测模板数据的类型
   check_template_data_type(template_data_owner_name,
                            template_data_name,
                            "plain_array");  
   void* first_para;
   int num_para;
   prepare_para(template_data_owner_name,
                template_data_name,
                &first_para,
                &num_para);
     
   return do_fill_plain_array(first_para, num_para, &plainap);
}


static int do_fill_plain_array
(
   const void* first_para, 
   int num_para, 
   struct plain_array** plaina2p
)
{
   alloc_plain_array(num_para, plaina2p);

   int i;
   void* arr = (*plaina2p)->arr;
   char* type = (*plaina2p)->type;
   const void* para = first_para;
   for (i=0; i<num_para; i++){

       check_para_data_type(para, "plain_array", type);

       const char* text_value_str = get_element_data(para, "text_value");
       check_element_data_existence("text_value", text_value_str);

       void* data = string_to_numeric_value(text_value_str, type);
       store_data_in_array(arr, i, data, type);

       para = get_next_sibling(para); 
   }

   return SUCCESS;
}


static void alloc_plain_array(int len, struct plain_array** plaina2p)
{
   void* arr = malloc(sizeof(long int)*len);  
   check_malloc(arr);

   (*plaina2p)->arr = arr;
   (*plaina2p)->len = len;
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
