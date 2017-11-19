#include "config_info_collect.h"
#include "error_report.h"
#include "fill_reg_array.h"
#include "miscellaneous.h"
#include <string.h>
#include <malloc.h>
#include <stdio.h>


int fill_reg_array
(
   char* global_or_op_name, 
   char* para_name,
   struct reg_array* regap
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

   return do_fill_reg_array(first_para, num_para, &regap);
}



static int do_fill_reg_array
(
   mxml_node_t* para, 
   int len, 
   struct reg_array** rega2p
)
{
   struct reg *regp;
   const char *value, *address;

   //分配存储空间，如果分配失败则返回错误
   if(!alloc_reg_array(len, rega2p)) return FAILURE;
   regp = (*rega2p)->regp;

   int i;
   for (i=0; i<len; i++){
       address  = mxmlElementGetAttr(para, "address");
       if (! check_null(__FILE__, __func__, "address", address)) return FAILURE;

       value = mxmlGetText(para, NULL);
       if (! check_null(__FILE__, __func__, "value", value)) return FAILURE;

       regp[i].addr = strtol(address, NULL, 16);
       regp[i].val = strtol(value, NULL, 16);

       para = skip_text_node(para, "address");
    }

    //其它字段的初始化
    (*rega2p)->len = len;

    return SUCCESS;
}


static int alloc_reg_array(int len, struct reg_array** rega2p)
{
   struct reg *regp;

   regp = (struct reg*)malloc(sizeof(struct reg)*len);  
   if (! check_null(__FILE__, __func__, "regp", regp)) return FAILURE;
   (*rega2p)->regp = regp;

    return SUCCESS;
}
