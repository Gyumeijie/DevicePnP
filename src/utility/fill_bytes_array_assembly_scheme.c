#include "config_info_collect.h"
#include "fill_bytes_array_assembly_scheme.h"
#include "error_report.h"
#include <string.h>
#include <malloc.h>
#include <stdio.h>


int fill_bytes_array_assembly_scheme
( 
   char* global_or_op_name, 
   char* para_name,
   struct bytes_array_assembly_scheme* asm_schemep
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
   
   return do_fill_bytes_array_assembly_scheme(first_para,
                                              num_para, 
                                              &asm_schemep);
}


static int do_fill_bytes_array_assembly_scheme
(
   mxml_node_t* first_para,
   int num_para, 
   struct bytes_array_assembly_scheme** asm_scheme2p
)
{
    if (! alloc_bytes_array_assembly_scheme(num_para, asm_scheme2p)){
        return FAILURE;
    }
    
    int i;
    mxml_node_t* para = first_para;
    struct bytes_assembly_descriptor* descs = (*asm_scheme2p)->bytes_asm_descs;
    for (i=0; i<num_para; i++){
       //TODO 屏蔽获取属性的细节,用一个通用的接口函数替代
       const char* start = mxmlElementGetAttr(para, "start");
       const char* num_byte = mxmlElementGetAttr(para, "num_byte");
      
       descs[i].start = strtoul(start, NULL, 10);
       descs[i].num_byte = strtoul(num_byte, NULL, 10);

       para = skip_text_node(para, "num_byte");
    }
    
    //其它成员的初始化
    (*asm_scheme2p)->num_para = num_para;
    (*asm_scheme2p)->precond_func = (precondition_function)0; 

    return SUCCESS;
}


static int alloc_bytes_array_assembly_scheme
(
   int num_para, 
   struct bytes_array_assembly_scheme** asm_scheme2p
)
{
   //为字节组装描述项分配空间
   struct bytes_assembly_descriptor* bytes_asm_descs;
   int st_size = sizeof(struct bytes_assembly_descriptor);
   bytes_asm_descs = malloc(st_size * num_para);   
   (*asm_scheme2p)->bytes_asm_descs = bytes_asm_descs;

   //为字节组装后的处理函数分配空间，并初始化
   post_process_function* post_proc_funcs;
   post_proc_funcs = malloc(sizeof(post_process_function) * num_para);
   (*asm_scheme2p)->post_proc_funcs = post_proc_funcs;
   memset(post_proc_funcs, 0, sizeof((void*)0)*num_para);

   return SUCCESS;
}
