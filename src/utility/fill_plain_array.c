#include "config_info_collect.h"
#include "error_report.h"
#include "fill_plain_array.h"
#include "miscellaneous.h"
#include <string.h>
#include <malloc.h>
#include <stdio.h>


int fill_plain_array
(
   char* global_or_op_name, 
   char* para_name,
   struct plain_array* plainap
)
{
   int num_para;
   mxml_node_t  *first_para;
   if (! get_first_para_and_num_para(global_or_op_name, 
                                     para_name, 
                                     &num_para,
                                     &first_para)){
       return UNMATCH;
    }
   
   return do_fill_plain_array(first_para, num_para, &plainap);
}


static int do_fill_plain_array
(
   mxml_node_t* first_para, 
   int num_para, 
   struct plain_array** plaina2p
)
{
   //分配存储空间，如果分配失败则返回错误
   if (! alloc_plain_array(num_para, plaina2p)) return FAILURE;
   void* arr = (*plaina2p)->arr;
   char* type = (*plaina2p)->type;

   int i;
   mxml_node_t* para = first_para;
   for (i=0; i<num_para; i++){
       //检查type是否一致，如果不是则表示不匹配
       if(! check_data_type(para, "plain_array", type)) return FAILURE;

       //TODO 检测value是否为空
       const char* value = mxmlGetText(para, NULL);
       void* data = convert_type(value, type);
       store_data_in_array(arr, i, data, type);

       para = skip_text_node(para, "type");
   }

   return SUCCESS;
}


static int alloc_plain_array(int len, struct plain_array** plaina2p)
{
   void* arr = malloc(sizeof(long int)*len);  
   if (!check_null(__FILE__, __func__, "arr", arr)) return FAILURE;

   (*plaina2p)->arr = arr;
   (*plaina2p)->len = len;
   
   return SUCCESS;
}
