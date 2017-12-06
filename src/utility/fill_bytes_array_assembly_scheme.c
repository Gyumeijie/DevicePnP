#include "config_info_collect.h"
#include "fill_bytes_array_assembly_scheme.h"
#include "error_report.h"
#include "collect_code_block.h"
#include <string.h>
#include <malloc.h>
#include <stdio.h>


int fill_bytes_array_assembly_scheme
( 
   const char* template_data_owner_name, 
   const char* template_data_name, 
   struct bytes_array_assembly_scheme* asm_schemep
)
{  
   void* para_list;
   para_list = find_para_list(template_data_owner_name, template_data_name);
   if (para_list == NULL)  return UNMATCH;

   int num_para = get_para_list_length(para_list);
   if (num_para == -1)  return UNMATCH;

   void* first_para = get_first_para(para_list);
    
   return do_fill_bytes_array_assembly_scheme(first_para,
                                              num_para, 
                                              &asm_schemep);
}


static int do_fill_bytes_array_assembly_scheme
(
   const void* first_para,
   int num_para, 
   struct bytes_array_assembly_scheme** asm_scheme2p
)
{
    if (! alloc_bytes_array_assembly_scheme(num_para, asm_scheme2p)){
        return FAILURE;
    }
    
    int i;
    const void* para = first_para;
    struct bytes_assembly_descriptor* descs = (*asm_scheme2p)->bytes_asm_descs;
    for (i=0; i<num_para; i++){
       const char* start_str = get_element_data(para, "start");
       const char* num_byte_str = get_element_data(para, "num_byte");
       const char* process_id_str = get_element_data(para, "postprocess_id"); 
       if (start_str==NULL || num_byte_str==NULL || process_id_str==NULL){
           return FAILURE;
       }
           
       descs[i].start = strtoul(start_str, NULL, 10);
       descs[i].num_byte = strtoul(num_byte_str, NULL, 10);
       descs[i].process_id = strtoul(process_id_str, NULL, 10);

       para = get_next_sibling(para);
    }
    
    // 其它成员的初始化
    (*asm_scheme2p)->num_para = num_para;

    return SUCCESS;
}


static int alloc_bytes_array_assembly_scheme
(
   int num_para, 
   struct bytes_array_assembly_scheme** asm_scheme2p
)
{
   // 为字节组装描述项分配空间
   struct bytes_assembly_descriptor* bytes_asm_descs;

   int size = sizeof(struct bytes_assembly_descriptor);
   bytes_asm_descs = malloc(size * num_para);   
   
   (*asm_scheme2p)->bytes_asm_descs = bytes_asm_descs;
   (*asm_scheme2p)->precondition = malloc(sizeof(struct single_code_block));
   (*asm_scheme2p)->postprocess_funcs = malloc(sizeof(struct group_code_blocks));
   
   return SUCCESS;
}
