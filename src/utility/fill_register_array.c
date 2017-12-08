#include "config_info_collect.h"
#include "error_report.h"
#include "fill_register_array.h"
#include "miscellaneous.h"
#include <string.h>
#include <malloc.h>
#include <stdio.h>


int fill_register_array
(
   const char* template_data_owner_name, 
   const char* template_data_name, 
   struct register_array* regap
)
{
   void* para_list;
   para_list = find_para_list(template_data_owner_name, template_data_name);
   if (para_list == NULL)  return UNMATCH;

   int num_para = get_para_list_length(para_list);
   if (num_para == -1)  return UNMATCH;

   void* first_para = get_first_para(para_list);
   
   return do_fill_register_array(first_para, num_para, &regap);
}



static int do_fill_register_array
(
   const void* first_para, 
   int len, 
   struct register_array** rega2p
)
{
   // 分配存储空间，如果分配失败则返回错误
   if(! alloc_register_array(len, rega2p)) return FAILURE;
   struct reg* regp = (*rega2p)->regp;

   int i;
   const void* para = first_para;
   for (i=0; i<len; i++){
       const char* address_str = get_element_data(para, "register_address");
       if (! check_null(__FILE__, __func__, "register_address", address_str)){
           return FAILURE;
       }

       const char* value_str = get_element_data(para, "text_value");
       if (! check_null(__FILE__, __func__, "value", value_str)) return FAILURE;

       regp[i].addr = strtol(address_str, NULL, 16);
       regp[i].val = strtol(value_str, NULL, 16);

       para = get_next_sibling(para);
    }

    // 其它字段的初始化
    (*rega2p)->len = len;

    return SUCCESS;
}


static int alloc_register_array(int len, struct register_array** rega2p)
{

   struct reg* regp = (struct reg*)malloc(sizeof(struct reg) * len);  
   if (! check_null(__FILE__, __func__, "regp", regp)) return FAILURE;
   (*rega2p)->regp = regp;

    return SUCCESS;
}