#include "config_info_collect.h"
#include "error_report.h"
#include "fill_plain_struct.h"
#include "miscellaneous.h"
#include <string.h>
#include <malloc.h>
#include <stdio.h>


/**
 *　输入：操作名op_name，模板参数para_list的名字para_name，包含驱动模板中待收集
 *        的类型为struct的模板参数的每个成员信息结构体数组st以及执行具体填充工作
 *        的函数do_fill
 *　输出：填充类型为struct的模板参数是否成功
 *　功能：为给定操作名填充类型为struct的模板参数
 */
int fill_plain_struct
(
   char* global_or_op_name, 
   char* para_name, 
   struct struct_member st[], 
   struct_fill_func_ptr do_fill
)
{
   int num_para;
   mxml_node_t* first_para;
   if (! get_first_para_and_num_para(global_or_op_name, 
                                     para_name,
                                     &num_para,
                                     &first_para)){
       return UNMATCH;
    }

   return do_fill_plain_struct(first_para, num_para, st, do_fill);
}


static int do_fill_plain_struct
(
   mxml_node_t* first_para,
   int num_para,
   struct struct_member st[],
   struct_fill_func_ptr do_fill
)
{

   void* data;
   const char *name, *value;
   mxml_node_t* para = first_para;

   //依次处理st中的成员
   int i;
   for (i=0; i<num_para; i++){
       //检查是否有对应的结构体成员，如果没有则表示不匹配
       name = st[i].name;
       if (! is_equal(name, mxmlElementGetAttr(para, "name"))) return FAILURE;

       //检查type是否一致，如果不是则表示不匹配
       if (! check_data_type(para, name, st[i].type)) return FAILURE;

       //将成员的数据写入到相应的结构体中
       value = mxmlGetText(para, NULL);
       data = convert_type(value, st[i].type);
       do_fill(st[i].index, data);
       
       //获取下一个para项
       para = skip_text_node(para, "name");
   }

    return SUCCESS;
}
