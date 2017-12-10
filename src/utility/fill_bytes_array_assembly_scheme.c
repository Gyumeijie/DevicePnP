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
   struct bytes_array_assembly_scheme* asm_schemep,
   int* need_to_collect_code_block,
   struct code_block_ids_designated* postprocess_ids_record
)
{  
   // 先检测模板数据的类型
   check_template_data_type(template_data_owner_name,
                            template_data_name,
                            "bytes_array_assembly");  
   void* first_para;
   int num_para;
   prepare_para(template_data_owner_name,
                template_data_name,
                &first_para,
                &num_para);

   return do_fill_bytes_array_assembly_scheme(first_para,
                                              num_para, 
                                              &asm_schemep,
                                              need_to_collect_code_block,
                                              postprocess_ids_record);
}


static int do_fill_bytes_array_assembly_scheme
(
   const void* first_para,
   int num_para, 
   struct bytes_array_assembly_scheme** asm_scheme2p,
   int* need_to_collect_code_block,
   struct code_block_ids_designated* postprocess_ids_record
)
{
   alloc_bytes_array_assembly_scheme(num_para, asm_scheme2p);
   
   // 由于事先不知道有多少个参数会指定compute_id，所以先分配num_para
   // 大小的空间
   postprocess_ids_record->id_array = malloc(sizeof(int)*num_para);   

   int i;
   const void* para = first_para;
   struct bytes_assembly_descriptor* descs = (*asm_scheme2p)->bytes_asm_descs;
   int num_para_need_postprocess = 0;
   int* id_array = postprocess_ids_record->id_array;
   for (i=0; i<num_para; i++){

      // 依次获取para的配置信息
      const char* start_str = get_element_data(para, "start");
      check_element_data_existence("start", start_str);
      descs[i].start = strtoul(start_str, NULL, 10);

      const char* num_byte_str = get_element_data(para, "num_byte");
      check_element_data_existence("num_byte", num_byte_str);
      descs[i].num_byte = strtoul(num_byte_str, NULL, 10);

      const char* postprocess_id_str = get_element_data(para, "postprocess_id"); 
      check_element_data_existence("postprocess_id", postprocess_id_str);
      int postprocess_id = strtoul(postprocess_id_str, NULL, 10);
      descs[i].postprocess_id = postprocess_id; 

      // 如果postprocess_ids_record是有效的，那么就需要收集代码块，
      // 而且只需要设置一次
      if (!(*need_to_collect_code_block) && 
           (postprocess_id >= 0))
      {
          *need_to_collect_code_block = 1; 
      }

      // 记录postprocess_ids_record
      id_array[num_para_need_postprocess] = postprocess_id; 
      num_para_need_postprocess++;
      
      para = get_next_sibling(para);
   }
   
   postprocess_ids_record->len = num_para_need_postprocess;

   return SUCCESS;
}


static void alloc_bytes_array_assembly_scheme
(
   int num_para, 
   struct bytes_array_assembly_scheme** asm_scheme2p
)
{
   int size = sizeof(struct bytes_assembly_descriptor);

   (*asm_scheme2p)->num_para = num_para;

   // 为字节组装描述项分配空间
   struct bytes_assembly_descriptor* bytes_asm_descs;
   bytes_asm_descs = malloc(size*num_para);   
   check_malloc(bytes_asm_descs);
   (*asm_scheme2p)->bytes_asm_descs = bytes_asm_descs;

   // 代码块是可选的，这里先不用为其分配空间
   (*asm_scheme2p)->precondition = NULL;
   (*asm_scheme2p)->postprocess_funcs = NULL;
}
