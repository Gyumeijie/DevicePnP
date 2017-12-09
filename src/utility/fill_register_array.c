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
   // 先检测模板数据的类型
   check_template_data_type(template_data_owner_name,
                            template_data_name,
                            "register_array");  
   void* first_para;
   int num_para;
   prepare_para(template_data_owner_name,
                template_data_name,
                &first_para,
                &num_para);
      
   return do_fill_register_array(first_para, num_para, &regap);
}



static int do_fill_register_array
(
   const void* first_para, 
   int len, 
   struct register_array** rega2p
)
{
   alloc_register_array(len, rega2p);

   int i;
   struct reg* regp = (*rega2p)->regp;
   const void* para = first_para;
   for (i=0; i<len; i++){
       const char* reg_addr_str = get_element_data(para, "register_address");
       check_element_data_existence("register_address", reg_addr_str);
       regp[i].addr = strtol(reg_addr_str, NULL, 16);

       const char* text_value_str = get_element_data(para, "text_value");
       check_element_data_existence("text_value", text_value_str);
       regp[i].val = strtol(text_value_str, NULL, 16);

       para = get_next_sibling(para);
    }

    // 其它字段的初始化
    (*rega2p)->len = len;

    return SUCCESS;
}


static void alloc_register_array(int len, struct register_array** rega2p)
{
   struct reg* regp = malloc(sizeof(struct reg) * len);  
   check_malloc(regp); 
   (*rega2p)->regp = regp;
}
