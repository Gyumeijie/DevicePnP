#include "config_info_collect.h"
#include "error_report.h"
#include "config_info_collect.h"
#include "fill_plain_struct.h"
#include "miscellaneous.h"
#include <string.h>
#include <malloc.h>
#include <stdio.h>

// 为给定操作名填充类型为struct的模板参数
int fill_plain_struct
(
   const char* template_data_owner_name, 
   const char* template_data_name, 
   struct struct_member st[], 
   fill_struct_function do_fill
)
{
   // 先检测模板数据的类型
   check_template_data_type(template_data_owner_name,
                            template_data_name,
                            "plain_struct");  
   void* first_para;
   int num_para;
   prepare_para(template_data_owner_name,
                template_data_name,
                &first_para,
                &num_para);
   
   return do_fill_plain_struct(first_para, num_para, st, do_fill);
}


static int do_fill_plain_struct
(
   const void* first_para,
   int num_para,
   struct struct_member st[],
   fill_struct_function do_fill
)
{
   int i;
   const void* para = first_para;
   for (i=0; i<num_para; i++){
       const char* name = st[i].name;
       const char* name_str = get_element_data(para, "name");
       check_element_data_existence("name", name_str);
       if (is_not_equal(name, name_str)) return FAILURE;

       check_para_data_type(para, name, st[i].type);

       // 将成员的数据写入到相应的结构体中
       const char* text_value_str = get_element_data(para, "text_value");
       check_element_data_existence("text_value", text_value_str);
       void* data = string_to_numeric_value(text_value_str, st[i].type);

       do_fill(st[i].index, data);
       
       para = get_next_sibling(para);
   }

    return SUCCESS;
}
